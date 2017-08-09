/**
  Iowa State University
  ME625 Final Project: Swept Surface Implementation
  Guangyu Hou
  May 2016
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

#include "draw_objects.h"
#include "trackball.h"
#include "testcases.h"

using namespace std;
// for curve
vector<vector<Point3D>> controlPts;
vector<vector<double>>  knot_vec;
vector<int>             p_degree;
// for surface
vector<vector<Point3D>> controlNet;
vector<double>          knotU;
vector<double>          knotV;
int                     p;
int                     q;

// The camera eye point position
double g_eye[3] = {0.0, 0.0, 15.0};

// The orientation of the camera
float g_quat[4] = {0.0, 0.0, 0.0, 0.0};
float g_last[4] = {0.0, 0.0, 0.0, 0.0};

// The previous mouse position
float g_previousMouseX = 0.0f;
float g_previousMouseY = 0.0f;

// The size of the window.
float window_width = 800;
float window_height = 800;


int g_sequence = 0;


/**
 * @brief draw_solid_cube
 * This draws a solid cube
 */
void camera_MotionFunc(int x, int y)
{
     // This scales the mouse coordinates to a range of [-1, 1]
    float px1 = (window_width -x)/(window_width/2.0) - 1.0;
    float py1 = y/(window_height/2.0) - 1.0;

     // Call the trackball function to get the new quaternion
    trackball(g_last, px1, py1, g_previousMouseX, g_previousMouseY);
    
    // Add the new quaternion to the current orientation.
    add_quats(g_last, g_quat,  g_quat);

    // Save the mouse position for the next step.
    g_previousMouseX = px1;
    g_previousMouseY = py1;
      
    // update the display and the objects in the scene
    glutPostRedisplay();
}

void camera_MouseButtonFunc(int button, int state, int x, int y)
{
    switch(state)
    {
        case GLUT_DOWN:
        {
            // This scales the mouse coordinates to a range of [-1, 1]
            float px1 = (window_width -x)/(window_width/2.0) - 1.0;
            float py1 = y/(window_height/2.0) - 1.0;

            // Store the mouse position as previous position.
            g_previousMouseX = px1;
            g_previousMouseY = py1;
            break;
        }
        case GLUT_UP:

            break;
    }

}


/**
 * @brief this initializes the camera.
 *  The code creates a perspective view frustum and
 *  move the camera.
 */
void init_camera(void)
{
    // Switch to the projection matrix mode
    glMatrixMode(GL_PROJECTION);

    // load an identity matrix
    glLoadIdentity();

    // Set the perspective
    gluPerspective(45.0, 1.0, 0.1, 10000.0);

    // change the matrix mode
    glMatrixMode(GL_MODELVIEW);

    // load an identity matrix
    glLoadIdentity();

    // Change your camera location and view vector
   // gluLookAt(300.0, 200.0, 300.00,
   //           0.0, 0.0, -150.0,
   //           0.0, 1.0, 0.0);
    gluLookAt(10.0, 10.0, -10.00,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);
}

/**
 * @brief init_light
 * This inits three light sources.
 * One direct light, one diffuse spot light, and
 * one diffuse and specular spot light.
 * The light sources are not enabled at this time.
 */
void init_light(void)
{
     // Enable the lighting unit
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);

    // Set the shading model
    glShadeModel(GL_SMOOTH);

    // Enable the depht test
    // The depth test has not been discussed in class
    // Keep it activate. We will discuss it later.
    glEnable(GL_DEPTH_TEST);


    /***********************************************************
     * Setup a direct light
    */
    GLfloat ligth_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {1.0, 3.0, -4.0, 0.0};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, ligth_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    /************************************************************
     * Setup a spot light
     */
    GLfloat light_position_spot[] = {1.0, 3.0, -4.0, 1.0};
    GLfloat light_dir[] = {0.2, -1.0, 2.0, 1.0};

    glLightfv(GL_LIGHT1, GL_DIFFUSE, ligth_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position_spot);

    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light_dir);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 15.0f);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0f);



    /************************************************************
     * Setup a spot light
     */
    GLfloat ligth_specular_spot[] = {1.0, 1.0, 1.0, 1.0};

    glLightfv(GL_LIGHT2, GL_DIFFUSE, ligth_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, ligth_specular_spot);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position_spot);

    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light_dir);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 15.0f);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 30.0f);


}



void updateCamera(void)
{
    /* update the camera */
    glMatrixMode(GL_MODELVIEW);
    // Clears all the previously loaded values in the modelview matrix
    glLoadIdentity();

    // Translate the camera eye point
    glTranslatef(-g_eye[0], -g_eye[1], -g_eye[2]);

    // Create a transformation matrix
    GLfloat m[4][4];
    build_rotmatrix(m, g_quat);

    // Apply the transformation matrix
    glMultMatrixf(&m[0][0]);

}




/**
 * @brief draw_scene
 * This function draws the scene.
 * It is called every frame and renders the object that
 * populate the virtual scene
 */
void draw_scene(void)
{
    // Enable the depth test
    glEnable(GL_DEPTH_TEST);

	GLfloat yellow[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat red[]    = {1.0, 0.0, 0.0, 1.0};
	GLfloat green[]  = {0.0, 1.0, 0.0, 1.0};
	GLfloat blue[]   = {0.0, 0.0, 1.0, 1.0};

    // draws the solid cube
    draw_solid_cube(vector3D(0,0,0),yellow);
	draw_solid_cube(vector3D(1,0,0),red);
	draw_solid_cube(vector3D(0,1,0),green);
	draw_solid_cube(vector3D(0,0,1),blue);
	draw_coordinates();
	

	// draw the section curve and trajectory curve
	for(int i=0;i<controlPts.size();i++)
	{
		//drawCurve3D(controlPts[i], p_degree[i], knot_vec[i]);
		//draw_control_polygon_ofCurve(controlPts[i]);
	}

	SweptSurface sweptSurf;
	// 1. get the translational swept surface
	 //sweptSurf.getTranslationalSweep(p_degree[0],knot_vec[0],p_degree[1],knot_vec[1],controlPts[0],controlPts[1]);
	
	// 2. get the trajectory interpolated surface
	BSplineCurve C(p_degree[0],controlPts[0].size()-1,knot_vec[0],controlPts[0]);
	BSplineCurve T(p_degree[1],controlPts[1].size()-1,knot_vec[1],controlPts[1]);
	vector3D Bv(1,0,0);
	Matrix33 identity = Matrix33::getIdentityMatrix();
	sweptSurf.getSweepSurface1(T,C,Bv,identity,10);

	sweptSurf.outputSweptSur(p,q,knotU,knotV,controlNet);

	// draw the swept surface
	if( controlNet.size()>0 )
	{
	 drawBSplineSurface(p,knotU,q,knotV,controlNet);
	 drawControlPolygonOfSurface(controlNet);
	}
}


/**
 * @brief display
 * This is the main display function.
 * It is automatilcally called every frame by the glutMainLoop.
 * It in
 */
void display(void)
{
    /*  clear all pixels  */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*************************************************************************/
    // If you would like to change camera and light parameters during
    // application runtime: do it at this location

    /*************************************************************************/
    // update the camera
    updateCamera();

    /* create a scene */
    draw_scene();

    /*  Wait until renderer is ready and
    *  swap the buffers
    */
    glutSwapBuffers();
}



/**
 * @brief init
 * This function inits the canera and the light.
 * It calls the related functions
 */
void init (void)
{
    /*  select clearing (background) color       */
    glClearColor (1.0, 1.0, 1.0, 0.0);

    
    trackball(g_quat, 0.0, 0.0, 0.0, 0.0);

    /* setup the camera location and viewing direction */
    init_camera();

    /* Setup the light */
    init_light();
	
    // Enable the depht test
    glEnable(GL_DEPTH_TEST);

	// curves tests begins
	controlPts.clear();
	knot_vec.clear();
	p_degree.clear();

	//runTestCases(1);
	runTestCases(4);
	runTestCases(5);
	//runTestCases(4);

	// move the section curve to origin
	Point3D translation(controlPts[0][0]);
	for(int i=0;i<controlPts[0].size();i++)
	{
	  controlPts[0][i] = controlPts[0][i] - translation;
	}

	// test the derivative algorithm
	//vector<vector3D> ds;
	//double u=0; double interv = 1.0/10;double TOL =1e-6;
	//for(int i=0;i<11;i++)
	//{
	//	ds.push_back( getDeriOfBSplineCurve(p_degree[1], knot_vec[1], controlPts[1],u) );
	//	u= u+ interv;
	//	if(u>1 && u-1 < TOL) u=1; 
	//}


}


void keyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case '1':
            g_sequence = 0;

            break;
        case '2':
            g_sequence = 1;

            break;
        case 't':


        break;

        default:
        break;
    }

    /* this redraws the scene without
        waiting for the display callback so that any changes appear
    instantly */
    glutPostRedisplay();

}



int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Swept Surface");
    init ();

    // specify the mouse click events to opengl
    glutMouseFunc(camera_MouseButtonFunc);

    // specify the mouse drag events
    glutMotionFunc(camera_MotionFunc);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;   /* ISO C requires main to return int. */
}
