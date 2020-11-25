#include <GL/glut.h>
#include <stdlib.h>

static int rotatedX = 0;
static int rotatedY = 0;
static int rotatedZ = 0;

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glRotatef(rotatedX, 1.0, 0.0, 0.0);
    glRotatef(rotatedY, 0.0, 1.0, 0.0);
    glRotatef(rotatedZ, 0.0, 0.0, 1.0);

    /*Tampa da mesa*/
    glPushMatrix();
        glScalef(1.5, 0.1, 1.5);
        glutWireCube(1.0);
    glPopMatrix();


    /*Pernas*/
    
    //perna superior-esquerda, vista por cima
    glPushMatrix();
        glTranslatef(-0.70, -0.55, -0.70);
        glScalef(0.1, 1.0, 0.1);
        glutWireCube(1.0);
    glPopMatrix();

    //perna inferior-esquerda, vista por cima
    glPushMatrix();
        glTranslatef(-0.70, -0.55, 0.70);
        glScalef(0.1, 1.0, 0.1);
        glutWireCube(1.0);
    glPopMatrix();

    //perna superior-direita, vista por cima
    glPushMatrix();
        glTranslatef(0.70, -0.55, -0.70);
        glScalef(0.1, 1.0, 0.1);
        glutWireCube(1.0);
    glPopMatrix();

    //perna inferior-direita, vista por cima
    glPushMatrix();
        glTranslatef(0.70, -0.55, 0.70);
        glScalef(0.1, 1.0, 0.1);
        glutWireCube(1.0);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -5.0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
        rotatedX = (rotatedX + 3) % 360;
        glutPostRedisplay();
        break;

    case 'y':
        rotatedY = (rotatedY + 3) % 360;
        glutPostRedisplay();
        break;

    case 'z':
        rotatedZ = (rotatedZ + 3) % 360;
        glutPostRedisplay();
        break;

    case 27:
        exit(0);
        break;
    default:
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}