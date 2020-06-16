#include <cstdlib>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

#define PI 3.14159265358979324

using namespace std;

// Globals.
static int numVertices = 5; // Number of vertices on circle.

// Drawing routine.
void drawScene(void)
{  
   double t = -2*PI; // Intervalo
   int i;
   glClear(GL_COLOR_BUFFER_BIT);

   glColor3f(0.0, 0.0, 0.0);

   // Draw a line loop with vertices at equal angles apart on a circle
   // with center at (X, Y) and radius R, The vertices are colored randomly.
   glBegin(GL_LINE_STRIP);  // usa o LINE_LOOP quando quer fechar.
      for(i = 0; i <= numVertices; ++i)
	  {
         glColor3ub(rand()%256, rand()%256, rand()%256); 
   
         glVertex3f(t, sin(t), 0.0 );
         
       
         t += 4*PI/numVertices;
        
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
   glOrtho(-10.0, 10.0, -10.0, 10.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
      case 27:
         exit(0);
         break;
      case '+':
         numVertices++;
         glutPostRedisplay();
         break;
      case '-':
         if (numVertices > 3) numVertices--;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}

// Routine to output interaction instructions to the C++ window.
void printInteraction(void)
{
   cout << "Interaction:" << endl;
   cout << "Press +/- to increase/decrease the number of vertices on the circle." << endl;  
}

// Main routine.
int main(int argc, char **argv) 
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100); 
   glutCreateWindow("exercicio1.cpp");
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMainLoop(); 

   return 0;  
}