#pragma once
#include <math.h>

class vector3D
{
public:
	double x,y,z;
	vector3D(){ x= y= z= 0;}
	vector3D(double x_,double y_,double z_):x(x_),y(y_),z(z_){}
	vector3D(double p[3]):x(p[0]),y(p[1]),z(p[2]){}

	vector3D normalize(){double norm = sqrt(x*x+y*y+z*z); x=x/norm; y=y/norm; z=z/norm; return *this;}
	vector3D operator*(const double d){return vector3D(x*d,y*d,z*d);}

	double getx()const {return x;} 
	double gety()const {return y;} 
	double getz()const {return z;} 

	vector3D crossp(const vector3D &v) const;
};