#include "BSplineSurface.h"


/*
The NURBS book
Algorithm A3.5
*/
Point3D getSurfacePoint(int n, int p, vector<double> U, int m, int q, vector<double> V, vector<vector<Point3D>> P, double u, double v)
{
	vector<double> Nu(p+1);
	vector<double> Nv(q+1);

	int uSpan = findSpan(n,p,u,U);
	basisFuns(uSpan,u,p,U,Nu);
	int vSpan = findSpan(m,q,v,V);
	basisFuns(vSpan,v,q,V,Nv);

	int uInd = uSpan - p;
	Point3D S;

	for(int l=0;l<=q;l++)
	{
	 Point3D temp;
	 int vInd = vSpan -q +l;
	 for(int k=0;k<=p;k++)
		temp = temp + P[uInd+k][vInd]*Nu[k];
	 S = S + temp*Nv[l];
	}

	return S;
}