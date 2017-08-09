#include "BSplineSurface.h"

class SweptSurface
{
private:
	int p;
	int q;
	vector<double> knotU;
	vector<double> knotV;
	vector<vector<Point3D>> controlNet;
public:
	SweptSurface(){p=0;q=0;}
	SweptSurface(int p_,int q_, vector<double> knotU_, vector<double> knotV_, vector<vector<Point3D>> controlNet_);
		
	void outputSweptSur(int &p_,int &q_, vector<double> &knotU_, vector<double> &knotV_, vector<vector<Point3D>> &controlNet_);
	void clearup(){ p=q=0; knotU.clear(); knotV.clear(); controlNet.clear(); };
	void insertKnots(BSplineCurve& T, int insertTimes);
	double getMiddlePointOfLongestVSpan(vector<double> KnotVec);

	void getTranslationalSweep(int p_, vector<double> knotU_, int q_,vector<double> V_, vector<Point3D> Unet, vector<Point3D> Vnet);
	void getSweepSurface1(BSplineCurve T, BSplineCurve C, vector3D Bv, Matrix33 Sv, int K);
};