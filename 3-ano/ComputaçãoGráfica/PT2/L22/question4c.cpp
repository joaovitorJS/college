
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;
// Globals.
static float t = 6.0;                                                 // Animation parameter.
// static float angle = 0.0, Xangle = 55.0, Yangle = 0.0, Zangle = 45.0; // Angles to rotate scene.
static float angle = 0.0, Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static int isAnimate = 0;                                             // Animated?
static int animationPeriod = 100;                                     // Time interval between frames.
static float transX = 6, transY = 2.5;
static bool flag = false, sobe = false;

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -15.0);
    // Rotate scene.
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);

    glutWireCube(3.0);

    glPushMatrix();
        glTranslatef(-6.0, 0.0, 0.0);
        glutWireCube(3.0);
    glPopMatrix();

    //cubo mais a direita
    glPushMatrix();
        glTranslatef(6.0, 0.0, 0.0);
        glutWireCube(3.0);
    glPopMatrix();

    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
        
        if (!flag) {
            glRotatef(angle, 0.0, 0.0, 1.0);
        } else {  
            glTranslatef(0.0, t, 0.0);   
        }
        glTranslatef(transX, transY, 0.0);
        
        glTranslatef(0.0, 0.0, 0.0);

        glutWireSphere(1.0, 20, 18);
    glPopMatrix();

    glFlush();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}
void animate(int value)
{
    if (isAnimate)
    {
        if (flag) {
            if (t >= 2.5 && !sobe) {
                t -= 0.05;  

            } else {
                sobe = true;
                t += 0.05;
                if (t >= 6) {
                    flag = false;
                    transX = 6.0;
                    transY = 2.5;
                }
            }

        } else {
       
            angle += 1;
            if (angle == 67) {
                flag = true;
                transX = 0;
                transY = 0;
            }

            if (angle >= 135)
                isAnimate = 0;
        }
        
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
    glFrustum(-5.0, 5.0, -5.0, 5.0, 5.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
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
    case 127:
        if (isAnimate)
            isAnimate = 0;
        t = 0.0;
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
    cout << "Press space to toggle between animation on and off." << endl
         << "Press delete to reset." << endl
         << "Press the x, X, y, Y, z, Z keys to rotate the scene." << endl;
}
// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("box.cpp");
    setup();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(5, animate, 1);
    glutMainLoop();

    return 0;
}