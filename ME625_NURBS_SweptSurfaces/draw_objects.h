/**
 Objects_Example
 draw_object.c/.cpp

 This code is an example of ME/CprE/ComS 557
 It keeps a set of example objects for the code
 examples of the course.

 Rafael Radkowski
 Iowa State University
 rafael@iastate.edu

**/
#pragma once
#include <iostream>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else
    #include <windows.h>
    #include <gl/gl.h>
    #include <gl/glu.h>
    #include "freeglut\include\GL\freeglut.h"
#endif


#include "Point.h"
#include "BSplineCurve.h"
#include "BSplineSurface.h"
#include "sweptSurface.h"
#include <vector>

using namespace std;

void draw_solid_cube(vector3D v, GLfloat color[] );

void draw_solid_sphere(void);

void draw_coordinates(void);

void drawCurve3D(vector<Point3D> ctrl_pts, int p_degree, vector<double> knot_vec);

void draw_control_polygon_ofCurve(vector<Point2D> ctrl_pts);

void draw_control_polygon_ofCurve(vector<Point3D> ctrl_pts);

void drawControlPolygonOfSurface( const vector<vector<Point3D>> &controlNet);

void drawBSplineSurface(int p, vector<double> U, int q, vector<double> V, vector<vector<Point3D>> P);