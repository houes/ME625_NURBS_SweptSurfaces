
class vector3D;
class Point3D;

class Matrix33{

private:
		double m[3][3];
public:
	Matrix33(){}
	Matrix33(double m_[3][3]);
	Matrix33(vector3D v1,vector3D v2,vector3D v3);

	Matrix33 operator-(const Matrix33& other) const;
	Matrix33 operator*(double d) const;
	vector3D operator*(const vector3D& other) const;
	Point3D  operator*(const Point3D& other) const;
	
	Matrix33 getInverse()const;
	void   setElement(int i,int j, double v);
	double getElement(int i,int j);
	Matrix33 getTranspose()const;
	void print();

	static Matrix33 getIdentityMatrix();
};