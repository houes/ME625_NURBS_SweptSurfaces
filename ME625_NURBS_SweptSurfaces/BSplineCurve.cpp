#include "BSplineCurve.h"
#include"Point.h"
#include<assert.h>
#include<algorithm>
using namespace std;


vector3D BSplineCurve::getFirstDerivative(double u)
{
	return getDeriOfBSplineCurve(p,U,controlPts,u);
}

Point3D  BSplineCurve::getPointAt(double u)
{
	return curvePoint(n,p,U,controlPts,u);

}

BSplineCurve BSplineCurve::getDeriBSplineC()
{
	return getDeriBSplineCurve(p,U,controlPts);
}
/* The Nurbs book page 68
Algorithm A2.1
*/
int findSpan(int n, int p, double u, vector<double> U)
{
	if (u == U[n + 1])
		return n;

	int low = p;
	int high = n + 1;
	int mid = (low + high) / 2;

	while (u < U[mid] || u >= U[mid + 1])
	{
		if (u < U[mid])
			high = mid;
		else
			low = mid;
		mid = (low + high) / 2;
	}

	return mid;
}

/* The Nurbs book page 70
Algorithm A2.2
*/

void basisFuns(int i, double u, int p, vector<double> U, vector<double> &N )
{
	assert( N.size() > 0 );

	N[0] = 1.0;
	vector<double> left(p+1);   // only the last p elements are used
	vector<double> right(p+1);

	for (int j = 1; j <= p; j++)
	{
		left[j] = u - U[i + 1 - j];
		right[j] = U[i + j] - u;
		double saved = 0;

		for (int r = 0; r < j; r++)
		{
			double temp = N[r] / (right[r + 1] + left[j - r]);
			N[r] = saved + right[r + 1] * temp;
			saved = left[j - r] * temp;
		}
		N[j] = saved;
	}
}

/* The Nurbs book page 82
Algorithm A3.1
*/
Point3D curvePoint(int n, int p, vector<double> U, vector<Point3D> ctrl_pts, double u)
{
	int span = findSpan(n, p, u, U);

	vector<double> N(p+1);
	basisFuns(span, u, p, U, N);
	
	Point3D C;
	for (int i = 0; i <= p; i++)
	{
		C = C + ctrl_pts[span - p + i] * N[i] ;
	}

	return C;
}

vector3D getDeriOfBSplineCurve(int p, vector<double> U, vector<Point3D> ctrl_pts, double u)
{
	int n = ctrl_pts.size() - 1;

	int pd = p-1;
	int nd = n-1;

	vector<double> Ud( U.size()-2 );
	copy( U.begin()+1, U.end()-1 , Ud.begin() );

	vector<Point3D> ctlptsD;

	for(int i=0; i<n; i++)
		ctlptsD.push_back( (ctrl_pts[i+1] - ctrl_pts[i])*p*(U[i+p+1] - U[i+1]) );

	Point3D deri = curvePoint(nd,pd,Ud,ctlptsD,u);

	vector3D deriv(deri.getX(),deri.getY(),deri.getZ());

	return deriv;
}

BSplineCurve getDeriBSplineCurve(int p, vector<double> U, vector<Point3D> ctrl_pts)
{
	int n = ctrl_pts.size() - 1;

	int pd = p-1;
	int nd = n-1;

	vector<double> Ud( U.size()-2 );
	copy( U.begin()+1, U.end()-1 , Ud.begin() );

	vector<Point3D> ctlptsD;

	for(int i=0; i<n; i++)
		ctlptsD.push_back( (ctrl_pts[i+1] - ctrl_pts[i])*p*(U[i+p+1] - U[i+1]) );

	BSplineCurve curve(pd,nd,Ud,ctlptsD);

	return curve;
}

/* The Nurbs book page 151
Algorithm A5.1
Input:  np,p,UP,Pw,u,k,s,r
Output: nq,UQ,Qw
*/

void CurveKnotIns(int np, int p, vector<double> UP, vector<Point3D> Pw, double u, int s, int r, int &nq, vector<double> &UQ, vector<Point3D> &Qw)
{
	int mp = np + p + 1;
	nq = np + r;
	int k = findSpan(np, p, u, UP);  /* insert u span */

	vector<Point3D> Rw(p + 1);

	/*Load new knot vector*/
	for (int i = 0; i <= k; i++) UQ[i] = UP[i];
	for (int i = 1; i <= r; i++) UQ[k + i] = u;
	for (int i = k + 1; i <= mp; i++) UQ[i + r] = UP[i];

	/* Save unaltered control points*/
	for (int i = 0; i <= k - p; i++) Qw[i] = Pw[i];
	for (int i = k - s; i <= np; i++) Qw[i + r] = Pw[i];
	for (int i = 0; i <= p - s; i++) Rw[i] = Pw[k - p + i];
	
	/* Insert the knot r times*/
	int L;
	for (int j = 1; j <= r; j++)
	{
		L = k - p + j;
		for (int i = 0; i <= p - j - s; i++)
		{
			double alpha = (u - UP[L + i]) / (UP[i + k + 1] - UP[L + i]);
			Rw[i] = Rw[i + 1] * alpha + Rw[i] * (1 - alpha);
		}
		Qw[L] = Rw[0];
		Qw[k + r - j - s] = Rw[p - j - s];
	}

	/* Load remaining control points */
	for (int i = L + 1; i < k - s; i++)
		Qw[i] = Rw[i - L];
}

BSplineCurve curvePointKnontInsertion(int n, int p, vector<double> U, vector<Point3D> ctrl_pts, double insertu, int s, int insertTimes)
{
	int nq;
	vector<double>  UQ( U.size() + insertTimes );
	vector<Point3D> Qw(n + 1 + insertTimes);
	CurveKnotIns(n, p, U, ctrl_pts, insertu, s, insertTimes, nq, UQ, Qw);
	vector<Point3D> newControlPts = Qw;
	
	BSplineCurve curve(p,nq,UQ,Qw);

	return curve;
}