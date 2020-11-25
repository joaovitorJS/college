#include <cstdlib>
#include <cmath>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define PI 3.14159265

using namespace std;

// Globals.

static int width, height;                     // Size of the OpenGL window.
static float angle = 0.0;                     // Angle of the spacecraft.
static float zVal = -5.0;              // Co-ordinates of the spacecraft.  
static int animationPeriod = 100;  
static bool isAnimate = false;  
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;

// Initialization routine.
void setup(void)
{
   glClearColor(1.0, 1.0, 1.0, 1.0);
}

// Drawing routine.
void drawScene(void)
{
   int i, j;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Begin left viewport.
   glViewport(0, 0, width / 2.0, height);
   glLoadIdentity();
   glTranslatef(0.0, 0.0, -13.0);

   glRotatef(Xangle, 1.0, 0.0, 0.0);
   glRotatef(Yangle, 0.0, 1.0, 0.0);
   glRotatef(Zangle, 0.0, 0.0, 1.0);

   glPushMatrix();
      //rotaciona o plano e a bola
      glTranslatef(0.0, 2.0, 0.0);
      glRotatef(45.0, 1.0, 0.0, 0.0);
      glTranslatef(0.0, 0.0, 0.0);

      /*desenha o plano*/
      glPushMatrix();
         glScalef(0.25, 0.01, 1);
         glutWireCube(10.0);
      glPopMatrix();

      /*desanha a bola e faz sua movimentação*/
      glPushMatrix();
         glTranslatef(0.0, 1.0, zVal);
         glRotatef(angle, 1.0, 0.0, 0.0);
         glTranslatef(0.0, 0.0, 0.0);
         glutWireSphere(1.0, 15, 13);
      glPopMatrix();
   glPopMatrix();
   /*desenha o cubo que ficara depois do plano*/
   glPushMatrix();
      glTranslatef(0.0, -0.25, 4.75);
      glScalef(0.25, 0.25, 0.25);
      glutWireCube(10.0);
   glPopMatrix();


   // Begin right viewport.
   glViewport(width / 2.0, 0, width / 2.0, height);
   glLoadIdentity();

   /*desenha a linha que separa as duas janelas de vizualização*/
   glColor3f(0.0, 0.0, 0.0);
   glLineWidth(2.0);
   glBegin(GL_LINES);
      glVertex3f(-5.0, -5.0, -5.0);
      glVertex3f(-5.0, 5.0, -5.0);
   glEnd();
   glLineWidth(1.0);

   /*posiciona a camera na "cabeça da bola"*/
   gluLookAt(0.0, 3.0, zVal,
             0.0, -0.25, 4.75,
             0.0, 1.0, 0.0
   );
  
   /*desenha o cubo que ficara depois do plano*/
   glPushMatrix();
      glTranslatef(0.0, -0.25, 4.75);
      glScalef(0.25, 0.25, 0.25);
      glutWireCube(10.0);
   glPopMatrix();

   glutSwapBuffers();
}

void animate(int value)
{
    if (isAnimate)
    {
        zVal += 0.1;
        angle += 5;
        if (zVal > 2.5)
            isAnimate = false;
    }
    glutTimerFunc(animationPeriod, animate, 1);
    glutPostRedisplay();
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 250.0);
   glMatrixMode(GL_MODELVIEW);

   // Pass the size of the OpenGL window.
   width = w;
   height = h;
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch (key)
   {
   case 27:
      exit(0);
      break;
   case ' ':
      if (isAnimate)
         isAnimate = 0;
      else
         isAnimate = 1;
      glutPostRedisplay();
      break;
   case 'r':
      if (isAnimate)
         isAnimate = 0;
      zVal = -5.0;
      glutPostRedisplay();
      break;
   case 'x':
        Xangle += 5.0;
        if (Xangle > 360.0)
            Xangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'X':
        Xangle -= 5.0;
        if (Xangle < 0.0)
            Xangle += 360.0;
        glutPostRedisplay();
        break;
    case 'y':
        Yangle += 5.0;
        if (Yangle > 360.0)
            Yangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Y':
        Yangle -= 5.0;
        if (Yangle < 0.0)
            Yangle += 360.0;
        glutPostRedisplay();
        break;
    case 'z':
        Zangle += 5.0;
        if (Zangle > 360.0)
            Zangle -= 360.0;
        glutPostRedisplay();
        break;
    case 'Z':
        Zangle -= 5.0;
        if (Zangle < 0.0)
            Zangle += 360.0;
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
   cout << "Press the left/right arrow keys to turn the craft." << endl
        << "Press the up/down arrow keys to move the craft." << endl;
}

// Main routine.
int main(int argc, char **argv)
{
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize(800, 400);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("spaceTravel.cpp");
   setup();
   glutDisplayFunc(drawScene);
   glutReshapeFunc(resize);
   glutKeyboardFunc(keyInput);
   glutTimerFunc(5, animate, 1);
   glutMainLoop();

   return 0;
}
