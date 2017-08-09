#include"Matrix33.h"
#include <iostream>
#include <iomanip>
#include "vector3D.h"
#include "Point.h"

using namespace std;

Matrix33::Matrix33(double m_[3][3]){

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			m[i][j] = m_[i][j];
}

Matrix33::Matrix33(vector3D v1,vector3D v2,vector3D v3)
{
	m[0][0] = v1.x;
	m[1][0] = v1.y;
	m[2][0] = v1.z;

	m[0][1] = v2.x;
	m[1][1] = v2.y;
	m[2][1] = v2.z;

	m[0][2] = v3.x;
	m[1][2] = v3.y;
	m[2][2] = v3.z;
}

void Matrix33::print()
{
	const char separator    = ' ';
	cout.precision(3);
	cout<<"Matrix:"<<endl;
	for(int i=0;i<3;i++)
		cout<<setw(6)<<m[i][0]
	        <<setw(6)<<m[i][1]
			<<setw(6)<<m[i][2]
			<<endl;
}

Matrix33 Matrix33::operator-(const Matrix33& other) const
{
	double t[3][3];

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			t[i][j]= m[i][j] - other.m[i][j];
	
	return Matrix33(t);
}

Matrix33 Matrix33::operator*(double d) const
{
	double t[3][3];

	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			t[i][j]= m[i][j]*d;
	
	return Matrix33(t);
}

vector3D Matrix33::operator*(const vector3D& other) const
{
	double p[3] = {other.getx(),
		           other.gety(),
		           other.getz()};
	double res[3] ={0};
	
	for(int i=0;i<3;i++)
	for(int j=0;j<3;j++)
		 res[i]+= m[i][j] * p[j];

	return vector3D(res);
}

Point3D Matrix33::operator*(const Point3D& other) const
{
	vector3D v( other.getX(), other.getY(), other.getZ());

	vector3D res = this->operator*(v);

	return Point3D(res.x, res.y, res.z);
}

void Matrix33::setElement(int i,int j, double v){
	m[i][j] = v;
}

double Matrix33::getElement(int i,int j){
	return m[i][j];
}

Matrix33 Matrix33::getTranspose()const{

	double t[3][3]={
		{m[0][0],m[1][0],m[2][0]},
	    {m[0][1],m[1][1],m[2][1]},
		{m[0][2],m[1][2],m[2][2]}
	};

	return Matrix33(t);
}

Matrix33 Matrix33::getInverse() const
{
	//1.Calculate Matrix of Minors. 
	int index[3][2] ={{1,2},{0,2},{0,1}};
	double tm[3][3]; //temporary matrix
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
		{ int r1 = index[i][0]; int r2 = index[i][1];
		  int c1 = index[j][0]; int c2 = index[j][1]; 
		  double det22 = m[r1][c1]*m[r2][c2] - m[r1][c2]*m[r2][c1];
		  tm[i][j] = det22;
		}
	Matrix33 minors(tm);
	//2.Calculate Matrix of Cofactors.
	Matrix33 cf = minors; // matrix of cofactors
	cf.setElement(0,1,-cf.getElement(0,1));
	cf.setElement(1,0,-cf.getElement(1,0));
	cf.setElement(1,2,-cf.getElement(1,2));
	cf.setElement(2,1,-cf.getElement(2,1));
	//3.Calculate Adjugate
	Matrix33 adj;
	adj = cf.getTranspose();
	//4.Multiply by determinant
	double det33 = m[0][0]* minors.m[0][0] - m[0][1]*minors.m[0][1] + m[0][2]*minors.m[0][2];

	return adj*(1.0/det33);
}

Matrix33 Matrix33::getIdentityMatrix()
{
	double identity[3][3]={
		{1,0,0},
		{0,1,0},
		{0,0,1},
	};
	return Matrix33(identity);
}