#pragma once
#include "Point.h"
#include<vector>

// for curves
extern vector<vector<Point3D>> controlPts;
extern vector<vector<double>>  knot_vec;
extern vector<int>             p_degree;
// for surface
extern vector<vector<Point3D>> controlNet;
extern vector<double>          knotU;
extern vector<double>          knotV;
extern int                     p;
extern int                     q;

void runTestCases(int caseID)
{
	// test case 1 
	Point3D array1[] = { Point3D(0,0,0),    Point3D(1,0,0),  Point3D(0.9,1,0), Point3D(2.5,1,0),Point3D(3,-0.5,0), Point3D(2,-1,0), Point3D(1,-0.7,0) };
	double  array2[] = { 0,0,0,0, 0.25,0.5,0.75,1,1,1,1 };
	vector<Point3D> ctrPts1(array1,array1+7);
	vector<double>  kvInit1(array2,array2+11);
	int p_1 = 3;

	// test case 2 - section curve-1 
	Point3D array3[] = { Point3D(0,-0.5,0.5), Point3D(0,-0.5,1),  Point3D(0,1,1), Point3D(0,1,0.7),Point3D(0,0,0.5), 
		                 Point3D(0,1,0.3), Point3D(0,1,0) , Point3D(0,-0.5,0), Point3D(0,-0.5,0.5)};
	double  array4[] = { 0,0,0,0.15,0.3,0.4,0.6,0.7,0.85,1,1,1 };
	vector<Point3D> ctrPts2(array3,array3 + 9);
	vector<double>  kvInit2(array4,array4 + 12);
	int p_2 = 2;
	// test case 3 - trajectory curve-1 
	Point3D array5[] = { Point3D(2,3,4), Point3D(0,3,4),  Point3D(0,3,0), Point3D(3,3,0),Point3D(3,0,0), 
		                 Point3D(3,0,2), Point3D(5,0,2) };
	double  array6[] = { 0,0,0,0.2,0.4,0.6,0.8,1,1,1 };
	vector<Point3D> ctrPts3(array5,array5 + 7);
	vector<double>  kvInit3(array6,array6 + 10);
	int p_3 = 2;

	// test case 4 - section curve-2
	Point3D array7[] = { Point3D(3.5,3,2), Point3D(3,3,2.5),  Point3D(2.5,3,2), 
		                 Point3D(1.5,3,2), Point3D(1,3,2.5), Point3D(0.5,3,2)};
	double  array8[] = { 0,0,0,0.25,0.5,0.75,1,1,1 };
	vector<Point3D> ctrPts4(array7,array7 + 6);
	vector<double>  kvInit4(array8,array8 + 9);
	int p_4 = 2;
	// test case 5 - trajectory curve-2
	Point3D array9[] = { Point3D(3,0,4), Point3D(3,0.5,4),  Point3D(3,2,3.5), Point3D(3,3,2),
		                 Point3D(3,3.5,0.5), Point3D(3,4,0), Point3D(3,5.5,0) };
	double  array10[] = { 0,0,0,0.2,0.4,0.6,0.8,1,1,1 };
	vector<Point3D> ctrPts5(array9,array9 + 7);
	vector<double>  kvInit5(array10,array10 + 10);
	int p_5 = 2;

	// test case 6 - 3D surface
	Point3D u1[] = {Point3D(3,-1.5,2), Point3D(1,-1,1.8),  Point3D(0.5,-1,3),  Point3D(-1,-1,2.8)};
	Point3D u2[] = {Point3D(3,0.7,2),   Point3D(1,0.8,1.8), Point3D(0.5,0.8,3),   Point3D(-1,0.8,2.8)};
	Point3D u3[] = {Point3D(3,1,0),    Point3D(1,1,0),	   Point3D(0.5,1,2),   Point3D(-1,1,2)};
	Point3D u4[] = {Point3D(3,2,0),    Point3D(1,2,0),     Point3D(0.5,2,2),   Point3D(-1,2,2)};
	Point3D u5[] = {Point3D(3,3.5,0),  Point3D(1,3,0),     Point3D(0.5,2.5,2), Point3D(-1,2.5,2)};

	vector<Point3D> u1_(u1,u1+4); 
	vector<Point3D> u2_(u2,u2+4); 
	vector<Point3D> u3_(u3,u3+4); 
	vector<Point3D> u4_(u4,u4+4); 
	vector<Point3D> u5_(u5,u5+4); 

	vector<vector<Point3D>> controlNetTemp;
	controlNetTemp.push_back(u1_);
	controlNetTemp.push_back(u2_);
	controlNetTemp.push_back(u3_);
	controlNetTemp.push_back(u4_);
	controlNetTemp.push_back(u5_);
		
	int pTemp = 2;
	int qTemp = 2;

	double knotV_[] = {0,0,0,0.5,1,1,1};          vector<double> knotVTemp = vector<double>(knotV_,knotV_+7);
	double knotU_[] = {0,0,0,0.333,0.667,1,1,1};  vector<double> knotUTemp = vector<double>(knotU_,knotU_+8);
	

	switch (caseID)
	{
	case 1:
		/* case 1*/
		controlPts.push_back(ctrPts1);
		knot_vec.push_back(kvInit1);
		p_degree.push_back(p_1); break;

	case 2:
		/* case 2 - section curve-1 */ 
		controlPts.push_back(ctrPts2);
		knot_vec.push_back(kvInit2);
		p_degree.push_back(p_2); break;
	case 3:
		/* case 3 - trajectory curve-1 */
		controlPts.push_back(ctrPts3);
		knot_vec.push_back(kvInit3);
		p_degree.push_back(p_3); break;

	case 4:
		/* case 4 - section curve-2 */ 
		controlPts.push_back(ctrPts4);
		knot_vec.push_back(kvInit4);
		p_degree.push_back(p_4); break;
	case 5:
		/* case 5 - trajectory curve-2 */
		controlPts.push_back(ctrPts5);
		knot_vec.push_back(kvInit5);
		p_degree.push_back(p_5); break;

	case 6:
		/* case 6 - example surface */
		controlNet = controlNetTemp;
		p = pTemp;
		q = qTemp;
		knotV = knotVTemp;
		knotU = knotUTemp;
		break;
		default:
			break;
	}
}