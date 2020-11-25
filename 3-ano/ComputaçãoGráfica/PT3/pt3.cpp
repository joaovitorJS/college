/**
 * Aluno: João Vitor de Oliveira
 * RGM: 38342
 * Trabalho 3 - Computação Gráfica
 */ 

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif
#include <iostream>
#include <time.h>
#include <math.h>

#define ROWS 8  
#define COLUMNS 5 
#define FILL_PROBABILITY 100 

using namespace std;

typedef struct S {
  GLdouble x, y, z;
}Point, Vector, Near, Far;

Near near;
Far far;
int alignBalls = 0;
bool isMultiColor = false;

class Esfera  {
private:
  float centerX, centerY, centerZ, radius;
  unsigned char color[3];

public:
  Esfera();

  Esfera(float x, float y, float z, float r, unsigned char colorR, unsigned char colorG, unsigned char colorB);

  float getCenterX() { return centerX; }
  float getCenterY() { return centerY; }
  float getCenterZ() { return centerZ; }
  float getRadius()  { return radius; }
  void setCenterY(float y) { centerY = y; }

  void setColor(unsigned char R, unsigned char G, unsigned char B) {
    
    if (!isMultiColor) { 
      color[0] = 200; color[1] = 0; color[2] = 0;
    } else {
      color[0] = R;
      color[1] = G;
      color[2] = B;
    }
  }

  void draw();
};

Esfera::Esfera() {
    centerX = 0.0;
    centerY = 0.0;
    centerZ = 0.0;
    radius = 0.0; 
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

Esfera::Esfera(float x, float y, float z, float r, unsigned char colorR, unsigned char colorG, unsigned char colorB) {
  centerX = x;
  centerY = y;
  centerZ = z;
  radius = r;
  color[0] = colorR;
  color[1] = colorG;
  color[2] = colorB;
}

void Esfera::draw() {
  if (radius > 0.0) { 
    glPushMatrix();
      glTranslatef(centerX, centerY, centerZ);
      glColor3ubv(color);
      glutWireSphere(radius, (int)radius * 2, (int)radius * 2);
    glPopMatrix();
  }
}
//Matriz das eferas
Esfera arrayEsferas[ROWS][COLUMNS]; 

void setup(void) {
  srand(time(NULL));
  //Inicializa a matriz de bolas
  for (int j = 0; j < COLUMNS; j++)
    for (int i = 0; i < ROWS; i++)
      if (rand() % 100 < FILL_PROBABILITY)
        if (COLUMNS % 2) 
          arrayEsferas[i][j] = Esfera( 25.0 * (-COLUMNS/2 + j), rand()%30 - 5, -40.0 - 30.0 * i, 6.0, 0, 0, 150);

  glEnable(GL_DEPTH_TEST);
  glClearColor (0.0, 0.0, 0.0, 0.0);
}

//Calcula o modulo de um vetor
float vectorModule(Vector v) {
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

float calculeDistance(Point point) {
  Vector ray, vectorAux, w;
  float dst;

  //vetor do raio 
  ray.x = far.x - near.x;
  ray.y = far.y - near.y;
  ray.z = far.z - near.z;

  //vetor entre o centro da bola e o ponto near -> z = 0
  vectorAux.x = near.x - point.x;
  vectorAux.y = near.y - point.y;
  vectorAux.z = near.z - point.z;

  //Produto vetorial
  w.x = ray.y * vectorAux.z - ray.z * vectorAux.y;
  w.y = ray.x * vectorAux.z - ray.z * vectorAux.x;
  w.z = ray.x * vectorAux.y - ray.y * vectorAux.x;

  dst = vectorModule(w) / vectorModule(ray);

  return dst;
}

void testCollision() {
  Point point;

  for (int j = 0; j < COLUMNS; j++) {
    for (int i = 0; i < ROWS; i++) {

      point.x =  arrayEsferas[i][j].getCenterX();
      point.y =  arrayEsferas[i][j].getCenterY();
      point.z =  arrayEsferas[i][j].getCenterZ();

      float dst = calculeDistance(point);

      if(dst < arrayEsferas[i][j].getRadius()) {
        if (isMultiColor) 
          arrayEsferas[i][j].setColor(rand() % 256, rand() % 256, rand() % 256);
        else { 
          arrayEsferas[i][j].setColor(0, 0, 0); 
        }  
      }
    }
  }
}

void display(void) {

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
    glColor3f(255.0, 255.0, 255.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
      glVertex3f(near.x, near.y, near.z);
      glVertex3f(far.x, far.y, far.z);
    glEnd();
  glPopMatrix();

  testCollision();

  srand(time(NULL));
  for (int j = 0; j < COLUMNS; j++) {
    for (int i = 0; i < ROWS; i++) {
      if (alignBalls != 0) {
        if (alignBalls == 1) {
          //alinhar as bolas
          arrayEsferas[i][j].setCenterY(0.0);
        } else {
          arrayEsferas[i][j].setCenterY(rand()%30 - 5);
        }
      }
      arrayEsferas[i][j].draw();
    }
  }
  if (alignBalls == 2) 
    alignBalls = 0;

  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glRotatef(-30, 20.0, 0.0, 0.0);

  gluPerspective (60.0, (GLfloat) w/(GLfloat) h, 65.0, 300.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void handleMouse(int button, int state, int x, int y) {
  GLint viewport[4];
  GLdouble matModelView[16], matProjection[16];
  GLdouble winX, winY;  

  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
    glGetIntegerv (GL_VIEWPORT, viewport);
    glGetDoublev (GL_MODELVIEW_MATRIX, matModelView);
    glGetDoublev (GL_PROJECTION_MATRIX, matProjection); 
    winX = (GLdouble) x;
    winY = viewport[3] - (GLdouble) y - 1;

    //gluUnProject -> palno Near  Winz = 0
    gluUnProject ( winX, winY, 0.0,
                   matModelView, matProjection, viewport,
                   &near.x, &near.y, &near.z
                 );
    
    //gluUnProject -> palno Far  Winz = 1
    gluUnProject ( winX, winY, 1.0,
                   matModelView, matProjection, viewport,
                   &far.x, &far.y, &far.z
                 );

  }

  glutPostRedisplay();
}

void handleKeyboard(unsigned char key, int x, int y) {
  switch (key) {
    //ESC -> sair do programa
    case 27:
      exit(0);
      break;
  }
}

void menu_organization(int id) {
  switch (id) {
  case 1:
    alignBalls = 1;
    break;
  case 2:
    alignBalls = 2;
    break;
  default:
    break;
  }
}

void menu_selection_colors(int id) {
  switch (id) {
  case 1:
    isMultiColor = false;
    break;
  case 2:
    isMultiColor = true;
    break;
  default:
    break;
  }
}

void createMenu(int id) { }

void handleMenu() {
  int sub_opc_menu_1, sub_opc_menu_2;

  sub_opc_menu_1 = glutCreateMenu(menu_organization);
  glutAddMenuEntry("Alinhar", 1);
  glutAddMenuEntry("Baguncar", 2);
  sub_opc_menu_2 = glutCreateMenu(menu_selection_colors);
  glutAddMenuEntry("Uma cor", 1);
  glutAddMenuEntry("Multi-cores", 2);

  glutCreateMenu(createMenu);
  glutAddSubMenu("Organizar Bolas", sub_opc_menu_1);
  glutAddSubMenu("Cores de selecao", sub_opc_menu_2);

  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void printInstructions() {
  cout << endl;
  cout << "Para mais opcoes como o alinhamento das bolas ou cores de selecao: " << endl;
  cout << "    - clique com o botao direito do mouse" << endl << endl;
}

int main(int argc, char** argv) {
    printInstructions();

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE  | GLUT_DEPTH);
    glutInitWindowSize (1200, 900);
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("Selecionando Bolas");

    setup();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc (handleKeyboard);
    glutMouseFunc(handleMouse);

    handleMenu();

    glutMainLoop();
    return 0;
}
