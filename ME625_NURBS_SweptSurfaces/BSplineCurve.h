#pragma once
#include"Point.h"
#include"vector3D.h"
#include"Matrix33.h"
#include<vector>

class BSplineCurve
{
private:
	int p;
	int n;
	vector<double> U;
	vector<Point3D> controlPts;
public:
	BSplineCurve(){p=0;n=0;}
	BSplineCurve(int p_, int n_, vector<double> U_,vector<Point3D> controlPts_):p(p_),n(n_),U(U_),controlPts(controlPts_){}

	int getDegree(){return p;}
	int getn(){return n;}
	vector<double> getKnotVec(){return U;}
	vector<Point3D> getControlPts(){return controlPts;}

	vector3D getFirstDerivative(double u);
	Point3D  getPointAt(double u);
	BSplineCurve getDeriBSplineC();
};


/* The Nurbs book page 68
Algorithm A2.1
*/
int findSpan(int n, int p, double u, vector<double> U);

/* The Nurbs book page 70
Algorithm A2.2
*/

void basisFuns(int i, double u, int p, vector<double> U, vector<double> &N);

/* The Nurbs book page 82
Algorithm A3.1
*/
Point3D curvePoint(int n, int p, vector<double> U, vector<Point3D> ctrl_pts, double u);

/* The Nurbs book page 94
   formulation 3.4 -3.6
*/
vector3D getDeriOfBSplineCurve(int p, vector<double> U, vector<Point3D> ctrl_pts, double u);

/* The Nurbs book page 151
Algorithm A5.1
Input:  np,p,UP,Pw,u,k,s,r
Output: nq,UQ,Qw
*/
void CurveKnotIns(int np, int p, vector<double> UP, vector<Point3D> Pw, double u, int s, int r, int &nq, vector<double> &UQ, vector<Point3D> &Qw);

BSplineCurve curvePointKnontInsertion(int n, int p, vector<double> U, vector<Point3D> ctrl_pts, double insertu, int s, int insertTimes);

BSplineCurve getDeriBSplineCurve(int p, vector<double> U, vector<Point3D> ctrl_pts);