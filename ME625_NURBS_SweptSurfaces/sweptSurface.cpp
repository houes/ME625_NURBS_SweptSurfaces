#include "sweptSurface.h"

SweptSurface::SweptSurface(int p_,int q_, vector<double> knotU_, vector<double> knotV_, vector<vector<Point3D>> controlNet_)
{
	p = p_;
	q = q_;
	knotU = knotU_;
	knotV = knotV_;
	controlNet =controlNet_;
}

void SweptSurface::getTranslationalSweep(int p_, vector<double> knotU_, int q_,vector<double> knotV_, vector<Point3D> Unet, vector<Point3D> Vnet)
{
	p = p_;
	q = q_;
	knotU = knotU_;
	knotV = knotV_;

	/* 
	   U: r = n + p + 1 
	   V: s = m + q + 1
	*/
	int r = knotU.size() -1 ;
	int s = knotV.size() -1 ;
	int n = r - p - 1;
	int m = s - q - 1;
	int N = n + 1; // number of control points
	int M = m + 1; // number of control points

	controlNet.resize(N);
	for(int i=0;i<N;i++)
		controlNet[i].resize(M);

	for(int i=0; i < N; i++)
		for(int j=0; j < M; j++)
			controlNet[i][j] = Unet[i] + Vnet[j];
}

void SweptSurface::outputSweptSur(int &p_,int &q_, vector<double> &knotU_, vector<double> &knotV_, vector<vector<Point3D>> &controlNet_)
{
	p_= p;
	q_= q;
	knotU_ = knotU;
	knotV_ = knotV;
	controlNet_ = controlNet;
}

void SweptSurface::getSweepSurface1(BSplineCurve T, BSplineCurve C, vector3D Bv, Matrix33 Sv, int K)
{
	p       = C.getDegree();
	knotU   = C.getKnotVec();
	q       = T.getDegree();
	int ktv = T.getKnotVec().size();
	int nsect = K+1;

	if( ktv <= nsect+q )
	{ // must refine T(v)'s knot vector
		int m = nsect + q- ktv+1;
		// insert kont in T for m times
		insertKnots(T,m);
		knotV = T.getKnotVec();
	}
	else
	{
		knotV = T.getKnotVec();
		if( ktv > nsect+q+1 ) // must increase number of instance of C(u)
			nsect = ktv-q-1;
	}

	// get section v-s
	vector<double> vSections(nsect);
	vSections[0]       = 0;
	vSections[nsect-1] = 1;
    for(int k=1;k<nsect-1;k++)
	{   
		vSections[k] = 0;
		for(int j=1;j<=q;j++)
			vSections[k]+= knotV[k+j];
		vSections[k] = vSections[k]/q;
	}

	// create transformed control points for each Section
	vector<vector<Point3D>> QTotalvFixed;  // vFixed for each row
	for(int k=0;k<nsect;k++)
	{
		vector<Point3D> Q = C.getControlPts();
		for(int i=0; i<Q.size(); i++)
			Q[i] = Sv*Q[i]; // scale every control point

		// for planar trajection curve, section curve facing y axis
		vector3D yv = T.getFirstDerivative(vSections[k]).normalize();
		vector3D xv = Bv.normalize();
		vector3D zv = xv.crossp(yv);

		// for 3D trajectotion curve: use Frenet frame
		//vector3D td1 = T.getFirstDerivative(vSections[k]).normalize();
		//vector3D td2 = T.getDeriBSplineC().getFirstDerivative(vSections[k]).normalize();
		//vector3D yv = td1*(-1);
		//vector3D xv = td1.crossp(td2); xv.normalize();
		//vector3D zv = xv.crossp(yv);

		Point3D pTv = T.getPointAt(vSections[k]);
		Matrix33 Av(xv,yv,zv);
		
		for(int i=0; i<Q.size(); i++)
			Q[i] = Av*Q[i] + pTv; // transform every control point

		
		QTotalvFixed.push_back(Q);
	}

	// get the tranverse of QTotalvFixed
	int rows = QTotalvFixed.size();
	int cols = QTotalvFixed[0].size();
	vector<vector<Point3D>> QTotaluFixed;  // uFixed for each row
	QTotaluFixed.resize(cols);
	for(int j=0;j<cols;j++)
	{
		QTotaluFixed[j].resize(rows);
		for(int i=0;i<rows;i++)
		{		   
		   QTotaluFixed[j][i] = QTotalvFixed[i][j];
		}
	}

	int n = C.getControlPts().size();
	for(int i=0;i<n;i++)
	{
	  // TODO: interpolate across Q[0]....Q[nsect-1]
	}

	controlNet = QTotaluFixed;

}

void SweptSurface::insertKnots(BSplineCurve& T, int insertTimes)
{
	// insesrt on T curve
	for(int i=0;i<insertTimes;i++)
	{
		double insertu = getMiddlePointOfLongestVSpan( T.getKnotVec() );
		T = curvePointKnontInsertion(T.getn(),T.getDegree(),T.getKnotVec(),T.getControlPts(),insertu,0,1);
	}
}

double SweptSurface::getMiddlePointOfLongestVSpan(vector<double> KnotVec)
{
	int indLongSpan = 0;

	double MaxSpan = 0;
	for(int i=0; i< KnotVec.size()-1;i++)
	{
		double currentSpan = KnotVec[i+1] - KnotVec[i];
		if(currentSpan > MaxSpan)
		{
			indLongSpan = i;
			MaxSpan = currentSpan;
		}
	}

	return (KnotVec[indLongSpan+1] + KnotVec[indLongSpan])/2.0;
}