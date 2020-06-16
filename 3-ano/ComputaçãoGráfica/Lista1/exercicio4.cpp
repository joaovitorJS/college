///////////////////////////////////////////////////////////////////////////////////////////        
// circularAnnuluses.cpp
//
// This program draws three identical-looking circular annuluses in three different ways - 
// see comments below.
//
// Interaction:
// Press the space bar to toggle between wirefrime and filled for the lower annulus.
// 
// Sumanta Guha.
/////////////////////////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265
#define N 30.0 // Number of vertices on the boundary of the disc.

using namespace std;

// Globals.
static int isWire = 0; // Is wireframe?


// Function to draw a disc with center at (X, Y, Z), radius R, parallel to the
// xy-plane.
void drawDisc(float R, float X, float Y, float Z)
{
   float t;
   int i;

   glBegin(GL_TRIANGLE_FAN);
      glVertex3f( X, Y, Z);
      for(i = 0; i <= N; ++i)
	  {
         t = 2 * PI * i / N; 
         glVertex3f(X + cos(t) * R, Y + sin(t) * R, Z);
	  }
   glEnd();
}

// Drawing routine.
void drawScene(void)
{  
   float angle;
   int i;

   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the buffers including 
                                                       // the depth buffer.

   glPolygonMode(GL_FRONT, GL_FILL);

   // Upper right circular annulus: the white disc is in front of the red disc blocking it.
   glEnable(GL_DEPTH_TEST); // Enable depth testing. 
   glColor3f(1.0, 1.0, 1.0);
   drawDisc(10.0, 25.0, 75.0, 0.5); // Compare this z-value with that of the red disc.
   glColor3f(1.0, 0.0, 0.0);
   drawDisc(20.0, 25.0, 75.0, 0.0);

   glColor3f(1.0, 1.0, 1.0);
   drawDisc(10.0, 25.0, 45.0, 0.5); // Compare this z-value with that of the red disc.
   glColor3f(1.0, 0.0, 0.0);
   drawDisc(20.0, 25.0, 45.0, 0.0);
   glDisable(GL_DEPTH_TEST); // Disable depth testing.

   // Lower circular annulus: with a true hole.
   if (isWire) glPolygonMode(GL_FRONT, GL_LINE);else glPolygonMode(GL_FRONT, GL_FILL);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= N; ++i)
	  {
         angle = 2 * PI * i / N; 
         glVertex3f(75 + cos(angle) * 10.0, 75 + sin(angle) * 10.0, 0.0);
         glVertex3f(75 + cos(angle) * 20.0, 75 + sin(angle) * 20.0, 0.0);
	  }
   glEnd();

    glBegin(GL_TRIANGLE_STRIP);
      for(i = 0; i <= N; ++i)
	  {
         angle = 2 * PI * i / N; 
         glVertex3f(75 + cos(angle) * 10.0, 45 + sin(angle) * 10.0, 0.0);
         glVertex3f(75 + cos(angle) * 20.0, 45 + sin(angle) * 20.0, 0.0);
	  }
   glEnd();

   glFlush();
}

// Initialization routine.
void setup(void) 
{
   glClearColor(1.0, 1.0, 1.0, 0.0);  
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case ' ':
         if (isWire == 0) isWire = 1;
         else isWire = 0;
         glutPostRedisplay();
         break;	  
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press the space bar to toggle between wirefrime and filled for the lower annulus." << endl;  
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH); // Initialize the buffers 
                                                             // including the depth buffer.
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("exercicio4.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}