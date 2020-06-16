////////////////////////////////////////////////////          
// square.cpp
//
// Stripped down OpenGL program that draws a square.
// 
// Sumanta Guha.
////////////////////////////////////////////////////
//Linha de Compilação: g++ -o square square.cpp –lglut –lGL –lGLU -lm

#include <iostream>


#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;

// Globals.
static int isWire = 0; // Is wireframe?


// Drawing (display) routine.
// Rotina/Função de Desenho
void drawScene(void)
{
   // Clear screen to background color.
   // Limpa a cor do fundo da tela
   glClear(GL_COLOR_BUFFER_BIT);

   
   //if (isWire) glPolygonMode(GL_FRONT, GL_LINE);else glPolygonMode(GL_FRONT, GL_FILL);
   if (isWire) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   } else {
      glPolygonMode(GL_FRONT, GL_FILL);
   }
    // Set foreground (or drawing) color.
   // Definindo cor em primeiro plano (ou desenho)
   glColor3f(1.0,0.0,0.0);
   

   // Draw a polygon with specified vertices.
   // Desenha um poligono com vertices especificados   
   glBegin(GL_TRIANGLE_STRIP); // Começo
      glVertex3f(30.0, 20.0, 0.0);
      glVertex3f(20.0, 20.0, 0.0);
      glVertex3f(40.0, 50.0, 0.0);
      glVertex3f(40.0, 80.0, 0.0);
      glVertex3f(50.0, 70.0, 0.0);
      glVertex3f(60.0, 80.0, 0.0);
      glVertex3f(60.0, 50.0, 0.0);
      glVertex3f(80.0, 20.0, 0.0);
      glVertex3f(70.0, 20.0, 0.0); 
      glVertex3f(60.0, 50.0, 0.0);
      glVertex3f(63.2, 40.0, 0.0);
      glVertex3f(40.0, 50.0, 0.0);
      glVertex3f(36.65, 40.0, 0.0);
   glEnd();

   
   // Flush created objects to the screen, i.e., force rendering.
   // Descarrega os objetos criados para a tela, ou seja, renderização força 
   glFlush(); 
}

// Initialization routine.
// Rotina de Inicialização
void setup(void) 
{
   // Set background (or clearing) color.
   // Define a cor do fundo 
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

// OpenGL window reshape routine.
// Rotina de remodelação da janela OpenGL 
void resize(int w, int h)
{
   // Set viewport size to be entire OpenGL window.
   // Definir 
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  
   // Set matrix mode to projection.
   glMatrixMode(GL_PROJECTION);

   // Clear current projection matrix to identity.
   glLoadIdentity();

   // Specify the orthographic (or perpendicular) projection, 
   // i.e., define the viewing box.
   glOrtho(0.0, 100.0, 0.0, 100.0, -1.0, 1.0);

   // Set matrix mode to modelview.
   glMatrixMode(GL_MODELVIEW);

   // Clear current modelview matrix to identity.
   glLoadIdentity();
}

// Keyboard input processing routine.
void keyInput(unsigned char key, int x, int y)
{
   switch(key) 
   {
    case ' ':
        if (isWire == 0) {
           isWire = 1;
        } else {
           isWire = 0;
        } 
        
        glutPostRedisplay();
        break;
	// Press escape to exit.
    case 27:
        exit(0);
        break;
    default:
        break;
   }
}

// Main routine: defines window properties, creates window,
// registers callback routines and begins processing.
int main(int argc, char **argv) 
{  
   // Initialize GLUT.
   glutInit(&argc, argv);
 
   // Set display mode as single-buffered and RGB color.
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   
   // Set OpenGL window size.
   // Definindo o tamanho da janela OpenGL
   glutInitWindowSize(500, 500);

   // Set position of OpenGL window upper-left corner.
   // Definindo a posição do canto superior-esquerdo da janela OpenGL
   glutInitWindowPosition(0, 0); 
   
   // Create OpenGL window with title.
   // Cria janela OpenGl com titulo
   glutCreateWindow("exercicio3.cpp");
   
   // Initialize.
   // inicializa
   setup(); 
   
   // Register display routine.
   glutDisplayFunc(drawScene); 
   
   // Register reshape routine.
   glutReshapeFunc(resize);  

   // Register keyboard routine.
   glutKeyboardFunc(keyInput);
   
   // Begin processing.
   glutMainLoop(); 

   return 0;  
}