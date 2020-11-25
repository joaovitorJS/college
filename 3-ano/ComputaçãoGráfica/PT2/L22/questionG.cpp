/////////////////////////////////
// box.cpp
//
// This program draws a wire box.
//
// Sumanta Guha.
/////////////////////////////////

#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

using namespace std;

static float X = 0.0;
static float Y = 0.0;
static int auxY = 0, auxX = 0;

static float angle = 0.0;
static float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0; // Angles to rotate scene.
static bool isAnimate = false;
static int animationPeriod = 50;
int size, sizetotal;
int numInt = 0;
float velocidade = 0.023;
int sentido = 2;

// Drawing routine.
void drawScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, -11.0);
    // Rotate scene.
    glRotatef(Zangle, 0.0, 0.0, 1.0);
    glRotatef(Yangle, 0.0, 1.0, 0.0);
    glRotatef(Xangle, 1.0, 0.0, 0.0);
    
    glPushMatrix();

        glColor3f(0.066, 0.470, 0.443);
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(0.0, 1.0, 0.0, 0.0);
        glScalef(5.0, 4.0, 0.5);
        glutWireCube(2.5);

        glPushMatrix();
            glColor3f(0.0, 0.0, 1.0);
            if (sentido == 2) {
                glTranslatef(X, Y, 0.1);
            } else {
                glTranslatef(-X, Y, 0.1);
            }
            glRotatef(angle, 1.0, 0.0, 0.0);
            glTranslatef(0.0, 0.0, 0.0);
            glColor3f(1.0, 0.0, 0.0);
            glutWireSphere(0.17, 20, 18);
        glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

// Initialization routine.
void setup(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
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
     case 'r':
        if (isAnimate)
            isAnimate = 0;
        numInt = 0;
        X = Y = 0.0;
        auxY = 0, auxX = 0;
        glutPostRedisplay();
        break;
    default:
        break;
    }
}


// Routine to increase the rotation angle.
void increaseAngle(void)
{
    if (isAnimate)
    {
        if (numInt <= 3 ) {
            if (auxX == 0) {
                if (X <= 1.0) {
                    X += velocidade;
                } else {
                    X -= velocidade;
                    auxX = 1;
                    numInt++;
                }
            } else {
                if (X >= -1.0) {
                    X -= velocidade;
                } else {
                    X += velocidade;
                    auxX = 0;
                    numInt++;
                }
            }

            if (auxY == 0) {
                if (Y <= 1.0) {
                    Y += velocidade+0.007;
                } else {
                    Y -= velocidade+0.007; 
                    auxY = 1;
                    numInt++;
                }       
            } else {
                if (Y >= -1.0) {
                    Y -= velocidade+0.007; 
                } else {
                    Y += velocidade+0.007;
                    auxY = 0;
                    numInt++;
                }
            }

            angle += 5.0;
            if (angle > 360.0)
                angle -= 360.0;

        } else {
            isAnimate = 0;
        }
    }

    glutPostRedisplay();
}

// Timer function for glutTimerFunc().
// The parameter someValue(=1) is passed to animate by glutTimerFunc(),
// but is not used.
void animate(int someValue)
{
    //if (isAnimate)
    increaseAngle();

    // Note that glutTimerFunc() calls animate() *once* after the
    // specified msecs. Therefore, to make repeated calls, animate()
    // must call itself again with glutTimerFunc() as below.
    glutTimerFunc(animationPeriod, animate, 1);
}

void rightMenu(int id) {
   if (id==2) exit(0);
}

void velocidade_config(int id) {
    if (id == 1) velocidade = 0.008;
    if (id == 2) velocidade = 0.023;
    if (id == 3) velocidade = 0.053;
}

void sentido_config(int id) {
    if (id == 1) {
        sentido = 1;
    }

    if (id == 2) {
        sentido = 2;
    }
}

void makeMenu() {
    int sub_menu_velocity, sub_menu_sentido;

    sub_menu_velocity = glutCreateMenu(velocidade_config);
    glutAddMenuEntry("0.008", 1);
    glutAddMenuEntry("0.023", 2);
    glutAddMenuEntry("0.053", 3);

    sub_menu_sentido = glutCreateMenu(sentido_config);
    glutAddMenuEntry("direita", 1);
    glutAddMenuEntry("esquerda", 2);

    glutCreateMenu(rightMenu);
    glutAddSubMenu("Velocidade", sub_menu_velocity);
    glutAddSubMenu("Sentido", sub_menu_sentido);
    glutAddMenuEntry("Quit", 1);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Main routine.
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutTimerFunc(5, animate, 1);

    makeMenu(); // Cria menu.

    glutMainLoop();
    return 0;
}
