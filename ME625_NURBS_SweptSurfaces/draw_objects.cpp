#include "draw_objects.h"

void draw_solid_cube(vector3D v, GLfloat color[])
{
    // enable Light0 for this cube
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    // create the matrix stack
    glPushMatrix();
    glTranslatef( v.x, v.y, v.z );


    // create a material for this cube
    //GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

    // draw a solid gube
    glutSolidCube(0.15f);

    // Remove matrix from stack
    glPopMatrix();


    // Disable the light
    glDisable(GL_LIGHT0);


}

void draw_solid_sphere(void)
{
    // enable Light0 for this sphere
    glEnable(GL_LIGHT1);
    glEnable(GL_DEPTH_TEST);

    // Switch to model view matrix
    glMatrixMode(GL_MODELVIEW);

    // create the matrix stack
    glPushMatrix();
    glTranslatef(0.3, 0.0, 2.0 );

    // create a material for this cube
    GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, red);

    // draw a solid sphere
    glutSolidSphere(1.0f, 100, 100);

    // Remove matrix from stack
    glPopMatrix();

    // Disable the light
    glDisable(GL_LIGHT1);
}

void draw_coordinates(void)
{
	//draw x-axis using cylinder
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

	//x-axis
	// create the matrix stack
    glPushMatrix();
	// create a material for this cube
    GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};
	GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
	GLfloat blue[]  = {0.0, 0.0, 1.0, 1.0};
	GLfloat r=0.02;

 	// draw a cylinder
	glMaterialfv(GL_FRONT, GL_DIFFUSE, red);
    GLUquadricObj *quadratic2;
    quadratic2 = gluNewQuadric();
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    gluCylinder(quadratic2,r,r,100,32,32);
	// Remove matrix from stack
    glPopMatrix();

	//y-axis
	// create the matrix stack
    glPushMatrix();
	// create a material for this cube

    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
	// draw a cylinder
    quadratic2 = gluNewQuadric();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadratic2,r,r,100,32,32);
	// Remove matrix from stack
    glPopMatrix();

	//z-axis
	// create the matrix stack
    glPushMatrix();
	// create a material for this cube

    glMaterialfv(GL_FRONT, GL_DIFFUSE, blue);
	// draw a cylinder
    quadratic2 = gluNewQuadric();
    gluCylinder(quadratic2,r,r,100,32,32);
	// Remove matrix from stack
    glPopMatrix();
	// Disable the light

	glDisable(GL_LIGHT0);
	//glDisable(GL_LIGHTING);
}

void drawCurve3D(vector<Point3D> ctrl_pts, int p_degree, vector<double> knot_vec)
{
	glDisable(GL_LIGHTING);

	double TOL =1e-6;

	int numberOfPts = 300; // specify the number of points to represent the curve
	GLfloat Color3f[] = {0,0,0};
	vector<Point3D> pts;
	pts.resize(numberOfPts);


	double uMin = knot_vec.front();
	double uMax = knot_vec.back();
	double span = uMax - uMin;
	double interval = span / (numberOfPts - 1);
	double u = uMin;

	// populate pts
	for (int i = 0; i < numberOfPts; i++)
	{
		pts[i] = curvePoint(ctrl_pts.size() - 1, p_degree, knot_vec, ctrl_pts, u);
		u = u + interval;
		if(u>1 && u-1<TOL) u = 1;
	}

	// draw the curve
	glLineWidth(2.0);
	glColor3f( Color3f[0], Color3f[1], Color3f[2]);
	glBegin(GL_LINES);
	for (int i = 0; i < numberOfPts - 1; i++)
	{
		glVertex3f(pts[i].getX(),	pts[i].getY()  ,pts[i].getZ());
		glVertex3f(pts[i+1].getX(), pts[i+1].getY(),pts[i+1].getZ());
	}
	glEnd();

	glEnable(GL_LIGHTING);
}

void draw_control_polygon_ofCurve(vector<Point2D> ctrl_pts)
{
	vector<Point2D> pts = ctrl_pts; // pts is used to draw

	// scale the pts for drawing purpose
	// coordinate value is restricted to [0,1]
	// scalePointSet(ctrl_pts, pts);

    // draw a closed loop
	glLineWidth(2.0);
	glColor3f(0,0,0);
    glBegin(GL_LINES);
	for (int i = 0; i < pts.size() - 1; i++)
	{
		glVertex2f(pts[i].getX(), pts[i].getY() );
		glVertex2f(pts[i + 1].getX(), pts[i + 1].getY());
	}
	glEnd();

	//draw the control points
	glPointSize(10);
	glBegin(GL_POINTS);
	for (int i = 0; i < pts.size(); i++)
		glVertex2f(pts[i].getX(), pts[i].getY());
	glEnd();


}

void draw_control_polygon_ofCurve(vector<Point3D> ctrl_pts)
{
	glDisable(GL_LIGHTING);

	vector<Point3D> pts = ctrl_pts; // pts is used to draw

	// scale the pts for drawing purpose
	// coordinate value is restricted to [0,1]
	// scalePointSet(ctrl_pts, pts);

    // draw a closed loop
	glLineWidth(2.0);
	GLfloat purple[3] = {0.63,0.13,0.94};
	glColor3fv(purple);
    glBegin(GL_LINES);
	for (int i = 0; i < pts.size() - 1; i++)
	{
		glVertex3f(pts[i].getX(), pts[i].getY(),   pts[i].getZ() );
		glVertex3f(pts[i + 1].getX(), pts[i + 1].getY(), pts[i+1].getZ());
	}
	glEnd();

	//draw the control points
	glPointSize(8);
	glBegin(GL_POINTS);
	for (int i = 0; i < pts.size(); i++)
		glVertex3f(pts[i].getX(), pts[i].getY(), pts[i].getZ() );
	glEnd();

	glEnable(GL_LIGHTING);
}

void drawBSplineSurface(int p, vector<double> U, int q, vector<double> V, vector<vector<Point3D>> P)
{	
	glDisable(GL_LIGHTING);

	double TOL =1e-6;
	// the row of P,    fixed u, v varies
	// the column of P, fixed v, u varies

	int n = P.size()   -1;
	int m = P[0].size()-1;

	int numberOfPtsU = 50; // specify the number of points to represent the U curve
	int numberOfPtsV = 30;  // specify the number of points to represent the V curve

	vector<vector<Point3D>> vCurves; // v-fixed curves
	vCurves.resize(numberOfPtsV);
	for(int i=0;i<vCurves.size();i++)
		vCurves[i].resize(numberOfPtsU);
	
	double intervalU = 1.0 / (numberOfPtsU - 1);
	double intervalV = 1.0 / (numberOfPtsV - 1);
	double u = 0;
	double v = 0;

	for(int i=0; i < numberOfPtsV; i++)
	{ 
		// populate a v-isoparametric curve
		for(int j=0; j< numberOfPtsU; j++)
		{
			vCurves[i][j] = getSurfacePoint(n,p,U,m,q,V,P,u,v);
			u = u+ intervalU;
			if( u>1 && u-1<TOL) u =1;
		}

		v = v+ intervalV;
		if( v>1 && v-1<TOL) v =1;
		u = 0;
	}

	// draw the v-iso curves
	glLineWidth(2.0);
	glColor3f(0,0,1);
	for (int j = 0;j < numberOfPtsV; j++)
	{
		glBegin(GL_LINES);
		for (int i = 0; i < numberOfPtsU - 1; i++)
		{
			glVertex3f(vCurves[j][i].getX(),	vCurves[j][i].getY()  , vCurves[j][i].getZ());
			glVertex3f(vCurves[j][i+1].getX(),  vCurves[j][i+1].getY(), vCurves[j][i+1].getZ());
		}
		glEnd();
	}

	// draw the u-iso curves
	glLineWidth(2.0);
	glColor3f(0,0,1);
	for (int j = 0;j < numberOfPtsU; j++)
	{
		glBegin(GL_LINES);
		for (int i = 0; i < numberOfPtsV - 1; i++)
		{
			glVertex3f(vCurves[i][j].getX(),	vCurves[i][j].getY()  , vCurves[i][j].getZ());
			glVertex3f(vCurves[i+1][j].getX(),  vCurves[i+1][j].getY(), vCurves[i+1][j].getZ());
		}
		glEnd();
	}

	glEnable(GL_LIGHTING);
}

void drawControlPolygonOfSurface( const vector<vector<Point3D>> &controlNet)
{
	int n = controlNet.size() ;   // number of u-iso curves
	int m = controlNet[0].size(); // number of v-iso curves

	// v - direction
	for(int i =0; i< n; i++)
		draw_control_polygon_ofCurve(controlNet[i]);

	// u - direction
	for(int j=0; j<m; j++) // column j
	{
	    vector<Point3D> pts;
		for(int i=0; i < n; i++ ) // row i
			pts.push_back(controlNet[i][j]);

		draw_control_polygon_ofCurve(pts);
	}

}