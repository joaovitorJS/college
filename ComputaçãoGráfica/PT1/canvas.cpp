////////////////////////////////////////////////////////////////////////////////////        
// canvas.cpp
// 
// PT1 - Computação Gráfica
// 
// Aluno: João Vitor de Oliveira
// 
// 
//////////////////////////////////////////////////////////////////////////////////// 

#include <cstdlib>
#include <vector>
#include <iostream>
#include <math.h>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

using namespace std;
   // Constantes //
#define INACTIVE 0
#define POINT 1
#define LINE 2
#define RECTANGLE 3
#define POLYLINE 4
#define CIRCULE 5
#define HEXAGON 6
#define NUMBERPRIMITIVES 6
#define PI 3.14159265358979324

using namespace std;

   // Variaveis Global //
static GLsizei width, height; // tamanho da janela OpenGL
static float pointSize = 3.0; // tamanho do ponto
static int primitive = INACTIVE; // primitivas.
static int pointCount = 0; // Contador para o numero de pontos
static int tempX1, tempY1; // primeiro ponto
static int tempX2, tempY2; // ponto interativo
static int isGrid = 1; // variavel para habilitar a grade/malha
static float sizeGrid[3] = {9, 0.1, 2}; // tamanho da grade/malha
static int modeDraw = 1;   // modo de desenho = preenchido/aramado
static float setColor[3] = {0.0, 0.0, 0.0}; // cor para o desenho
static int setStipple = 0; // modo pontilhado/normal
static int legX, legY; // auxiliares para a legenda
static long font = (long)GLUT_BITMAP_8_BY_13; // seleção da fonte.

//====================================================================================//
// Classe que representa o Ponto
//====================================================================================//
class Point {
public:
   Point(int xVal, int yVal, float r, float g, float b) {
      //coordenadas do ponto
	   x = xVal; y = yVal;
      //cor
      color[0] = r;
      color[1] = g;
      color[2] = b;
   }
   void drawPoint(void); // Função que desenha um ponto

private:
   int x, y; // coordenadas do ponto
   static float size; // Tamanho do ponto
   float color[3] = {0, 0, 0}; // Cor
};

float Point::size = pointSize; // atribuindo o tamanho do ponto.

//====================================================================================//
// Objetivo da Função: desenhar o ponto conforme o click do mouse na janela 
//====================================================================================//
void Point::drawPoint()
{  
   glColor3fv(color);
   glPointSize(size);
   glBegin(GL_POINTS);
      glVertex3f(x, y, 0.0);
   glEnd();   
}

// Vetor dos Pontos
vector<Point> points;

// Iterator para manipular o Vetor.
vector<Point>::iterator pointsIterator; 

//====================================================================================//
// Objetivo da Função: Desenhar os Pontos que estam no vetor
//====================================================================================//
void drawPoints(void) {

   pointsIterator = points.begin();
   while(pointsIterator != points.end() )
   {
      pointsIterator->drawPoint();
	  pointsIterator++;
   }
}


//====================================================================================//
// Classe que representa a linha
//====================================================================================//
class Line {
public:
   Line(int x1Val, int y1Val, int x2Val, int y2Val, float r, float g, float b, int setstipple) {
      //coordendas dos pontos
      x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
      //cor
      color[0] = r;
      color[1] = g;
      color[2] = b;
      //pontilhado 
      stipple = setstipple;
   }

   void drawLine(); // Função que desenha uma linha
private:
   int x1, y1, x2, y2; // coordenadas da linha
   float color[3] = {0, 0, 0}; //cor
   int stipple; //pontilhado
};


//====================================================================================//
// Objetivo da Função: desenhar uma linha conforme a cor setada e as coordenadas
//====================================================================================//
void Line::drawLine() {
   glColor3fv(color);

   // ativa o pontilhado
   glEnable(GL_LINE_STIPPLE);
   if (stipple) 
      glLineStipple(1, 0x5555);
   else
      glLineStipple(1, 0xFFFF);

   glLineWidth(1.5);
   glBegin(GL_LINES);
      glVertex3f(x1, y1, 0.0);
      glVertex3f(x2, y2, 0.0);
   glEnd();
   glLineWidth(1.0);
   glDisable(GL_LINE_STIPPLE);
}

// Vetor das Linhas
vector<Line> lines;

// Iterator para manipular o Vetor.
vector<Line>::iterator linesIterator;

//====================================================================================//
// Objetivo da Função: desenhar as linhas que estam no vetor
//====================================================================================//
void drawLines(void) {

   linesIterator = lines.begin();
   while(linesIterator != lines.end() )
   {
      linesIterator->drawLine();
	  linesIterator++;
   }
}

//====================================================================================//
// Classe que representa o Retângulo
//====================================================================================//
class Rectangle {
public:
   Rectangle(int x1Val, int y1Val, int x2Val, int y2Val, float r, float g, float b, int setmode, int setstipple) {
	   //coordenadas dos pontos
      x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
      //cor
      color[0] = r;
      color[1] = g;
      color[2] = b;
      //modo
      mode = setmode;
      //pontilhado 
      stipple = setstipple;
   }
   void drawRectangle();
private:
   int x1, y1, x2, y2; // coordenadas da diagonal do retângulo
   float color[3] = {0, 0, 0}; 
   int mode;
   int stipple;
};

//====================================================================================//
// Objetivo da Função: desenhar o retângulo, conforme as coordenadas da diagonal e suas
// opções de desenho
//====================================================================================//
void Rectangle::drawRectangle() {  
   // ativa o pontilhado
   glEnable(GL_LINE_STIPPLE);
   if (stipple) 
      glLineStipple(1, 0x5555);
   else
      glLineStipple(1, 0xFFFF);

   //aplica o modo
   if (mode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //aramado
   } else {    
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //preenchido
   }
   glColor3fv(color);
   glLineWidth(1.5);
   glRectf(x1, y1, x2, y2);
   glLineWidth(1.0);
}

// Vetor da Classe Rectangle
vector<Rectangle> rectangles;

// Iterator para manipular o Vetor.
vector<Rectangle>::iterator rectanglesIterator;

//====================================================================================//
// Objetivo da Função: desenhar os retângulos que estam no vetor
//====================================================================================//
void drawRectangles(void) {
   
   rectanglesIterator = rectangles.begin();
   while(rectanglesIterator != rectangles.end() )
   {
      rectanglesIterator->drawRectangle();
	   rectanglesIterator++;
   }
}

//====================================================================================//
// Classe que representa as poli-linhas
//====================================================================================//
class Polyline {
public:
   Polyline(int x1Val, int y1Val, int x2Val, int y2Val, float r, float g, float b, int setstipple) {
      //coordenadas dos pontos
	   x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
      //cor
      color[0] = r;
      color[1] = g;
      color[2] = b;
      //pontilhado 
      stipple = setstipple;
   }
   void drawPolyline();
private:
   int x1, y1, x2, y2; 
   float color[3] = {0, 0, 0};
   int stipple;
};


//====================================================================================//
// Objetivo da Função: Desenhar a Poli-Linha  
//====================================================================================//
void Polyline::drawPolyline() {  
   
   glColor3fv(color);

   // ativa o pontilhado
   glEnable(GL_LINE_STIPPLE);
   if (stipple) 
      glLineStipple(1, 0x5555);
   else
      glLineStipple(1, 0xFFFF);

   glLineWidth(1.5);
   glBegin(GL_LINE_STRIP);
      glVertex3f(x1, y1, 0.0);
      glVertex3f(x2, y2, 0.0);
   glEnd();
   glLineWidth(1.0);
}

// Vetor da Classe Polylines
vector<Polyline> polylines;

// Iterator para manipular o Vetor.
vector<Polyline>::iterator polylinesIterator;

//====================================================================================//
// Objetivo da Função: desenhar as poli-linhas que estam no vetor
//====================================================================================//
void drawPolylines(void) {  
   
   polylinesIterator = polylines.begin();
   while(polylinesIterator != polylines.end() )
   {
      polylinesIterator->drawPolyline();
	   polylinesIterator++;
   }
}

//====================================================================================//
// Classe que representa o Circulo
//====================================================================================//
class Circule {
public:
   Circule(int x1Val, int y1Val, int x2Val, int y2Val, float r, float g, float b, int setmode, int setstipple) {
	   //coordendas dos pontos
      x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
      //cor
      color[0] = r;
      color[1] = g;
      color[2] = b;
      //modo
      mode = setmode;
      //pontilhado 
      stipple = setstipple;
   }
   void drawCircule();
private:
   int x1, y1, x2, y2; 
   float color[3] = {0, 0, 0};
   int mode;
   int stipple;
};


//====================================================================================//
// Objetivo da Função: desenhar o circulo, conforme a escolha do centro e um ponto do circulo 
//====================================================================================//
void Circule::drawCircule() {
   // raio
   float radius = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
   float t;
   int i;

   glColor3fv(color);

   // ativa o pontilhado
   glEnable(GL_LINE_STIPPLE);
   if (stipple) 
      glLineStipple(1, 0x5555);
   else
      glLineStipple(1, 0xFFFF);

   glLineWidth(1.5);

   // aplica o modo
   if (mode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //aramado
      glBegin(GL_LINE_LOOP);
   } else { 
      glPolygonMode(GL_FRONT, GL_FILL);   //preenchido
      glBegin(GL_TRIANGLE_FAN);
   }

      for(i = 0; i <= 40; ++i) {
         t = 2 * PI * i / 40; 
         glVertex3f(x1 + radius * cos(t), y1 + radius *sin(t), 0.0);
      }
   glEnd();
   glLineWidth(1.0);
}

// Vetor da Classe Circule
vector<Circule> circules;

// Iterator para manipular o Vetor.
vector<Circule>::iterator circulesIterator;

//====================================================================================//
// Objetivo da Função: desenhar os circulos que estam no vetor
//====================================================================================//
void drawCircules(void) {  

   circulesIterator = circules.begin();
   while(circulesIterator != circules.end() )
   {
      circulesIterator->drawCircule();
	  circulesIterator++;
   }
}

//====================================================================================//
// Classe que representa o Hexágono 
//====================================================================================//
class Hexagon {
public:
   Hexagon(int x1Val, int y1Val, int x2Val, int y2Val, float r, float g, float b, int setmode, int setstipple) {
      //coordenadas dos pontos
	   x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;
      //cor
      color[0] = r;
      color[1] = g;
      color[2] = b;
      //modo
      mode = setmode;
      //pontilhado 
      stipple = setstipple;
   }
   void drawHexagon();
private:
   int x1, y1, x2, y2; 
   float color[3] = {0, 0, 0}; 
   int mode;
   int stipple;
};

//====================================================================================//
// Objetivo da Função: desenhar o hexágono, conforme a escolha co centro e um vertice do
// hexágono
//====================================================================================//
void Hexagon::drawHexagon() {
   float radius = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
   float t;
   int i;

   glColor3fv(color);

   // ativa o pontilhado
   glEnable(GL_LINE_STIPPLE);
   if (stipple) 
      glLineStipple(1, 0x5555);
   else
      glLineStipple(1, 0xFFFF);
   
   glLineWidth(1.5);

   //aplica o modo
   if (mode) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //aramado
      glBegin(GL_LINE_LOOP);
   } else { 
      glPolygonMode(GL_FRONT, GL_FILL);   //preenchido
      glBegin(GL_TRIANGLE_FAN);
   }

      for(i = 0; i <= 6; ++i) {
         t = 2 * PI * i / 6; 
         glVertex3f(x1 + radius * cos(t), y1 + radius *sin(t), 1.0);
      }
   glEnd();

   glLineWidth(1.0);
}

// Vetor da Classe Hexagon
vector<Hexagon> hexagons;

// Iterator para manipular o Vetor.
vector<Hexagon>::iterator hexagonsIterator;

//====================================================================================//
// Objetivo da Função: desenhar os hexagonos que estão no vetor
//====================================================================================//
void drawHexagons(void) {  
   
   hexagonsIterator = hexagons.begin();
   while(hexagonsIterator != hexagons.end() )
   {
      hexagonsIterator->drawHexagon();
	   hexagonsIterator++;
   }
}

//====================================================================================//
// Objetivo da Função: desenhar a caixa de seleção do ponto
//====================================================================================//
void drawPointSelectionBox(void) {  
   if (primitive == POINT) 
      glColor3f(1.0, 1.0, 1.0); // destacar
   else 
      glColor3f(0.8, 0.8, 0.8); // não destacar.
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.9*height, 0.1*width, height);

   // desenha a borda da caixa
   glColor3f(0.0, 0.0, 0.0); 
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.9*height, 0.1*width, height); 

   // desenha o icone 
   glPointSize(pointSize);
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_POINTS);
      glVertex3f(0.05*width, 0.95*height, 0.0);
   glEnd();  
}

//====================================================================================//
// Objetivo da Função: desenhar a caixa de seleção da linha
//====================================================================================//
void drawLineSelectionBox(void) {  
   if (primitive == POINT) 
      glColor3f(1.0, 1.0, 1.0); // destacar
   else 
      glColor3f(0.8, 0.8, 0.8); // não destacar.

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

   // desenha a borda da caixa
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.8*height, 0.1*width, 0.9*height);

   // desenha o icone 
   glColor3f(0.0, 0.0, 0.0);
   glBegin(GL_LINES);
      glVertex3f(0.025*width, 0.825*height, 0.0);
      glVertex3f(0.075*width, 0.875*height, 0.0);
   glEnd();  
}

//====================================================================================//
// Objetivo da Função: desenhar a caixa de seleção do retângulo
//====================================================================================//
void drawRectangleSelectionBox(void) {  
   if (primitive == POINT) 
      glColor3f(1.0, 1.0, 1.0); // destacar
   else 
      glColor3f(0.8, 0.8, 0.8); // não destacar.

   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

   // desenha a borda da caixa
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.7*height, 0.1*width, 0.8*height);

   // desenha o icone 
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.025*width, 0.735*height, 0.075*width, 0.765*height);
   glEnd();  
}

//====================================================================================//
// Objetivo da Função: desenhar a caixa de seleção da poli-linha
//====================================================================================//
void drawPolylineSelectionBox(void) {
   if (primitive == POINT) 
      glColor3f(1.0, 1.0, 1.0); // destacar
   else 
      glColor3f(0.8, 0.8, 0.8); // não destacar.
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.6*height, 0.1*width, 0.7*height);

   // desenha a borda da caixa
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.6*height, 0.1*width, 0.7*height);

   // desenha o icone 
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glBegin(GL_LINE_STRIP);
      glVertex3f(0.02*width, 0.625*height, 0.0);
      glVertex3f(0.04*width, 0.675*height, 0.0);
      glVertex3f(0.06*width, 0.625*height, 0.0);	
      glVertex3f(0.08*width, 0.675*height, 0.0);
   glEnd();

}

//====================================================================================//
// Objetivo da Função: desenhar a caixa de seleção do circulo
//====================================================================================//
void drawCirculeSelectionBox(void) {
   if (primitive == POINT) 
      glColor3f(1.0, 1.0, 1.0); // destacar
   else 
      glColor3f(0.8, 0.8, 0.8); // não destacar.
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.5*height, 0.1*width, 0.6*height);

   // desenha a borda da caixa
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.5*height, 0.1*width, 0.6*height);

   // desenha o icone 
   float t;
   int i;
   glColor3f(0.0, 0.0, 0.0); 
   glBegin(GL_LINE_LOOP);
      for(i = 0; i <= 40; ++i) {
         t = 2 * PI * i / 40; 
         glVertex3f(0.05*width + 15 * cos(t), 0.55*height + 15*sin(t), 0.0);
      }
   glEnd();

}

//====================================================================================//
// Objetivo da Função: desenhar a caixa de seleção do hexágono
//====================================================================================//
void drawHexagonSelectionBox(void) {
   if (primitive == POINT) 
      glColor3f(1.0, 1.0, 1.0); // destacar
   else 
      glColor3f(0.8, 0.8, 0.8); // não destacar.
   
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.4*height, 0.1*width, 0.5*height);

   // desenha a borda da caixa
   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.4*height, 0.1*width, 0.5*height);

   // desenha o icone 
   float t;
   int i;
   glColor3f(0.0, 0.0, 0.0); 
   glBegin(GL_LINE_LOOP);
      for(i = 0; i <= 6; ++i) {
         t = 2 * PI * i / 6; 
         glVertex3f(0.05*width + 15 * cos(t), 0.45*height + 15*sin(t), 0.0);
      }
   glEnd();
}

//====================================================================================//
// Objetivo da Função: desenhar a parte inativa da caixa de seleção
//====================================================================================//
void drawInactiveArea(void) {
   glColor3f(0.6, 0.6, 0.6);
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
   glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);

   glColor3f(0.0, 0.0, 0.0);
   glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   glRectf(0.0, 0.0, 0.1*width, (1 - NUMBERPRIMITIVES*0.1)*height);
}

//====================================================================================//
// Objetivo da Função: desenhar o ponto temporário/ primeiro ponto
//====================================================================================//
void drawTempPoint(void) {
   glColor3f(1.0, 0.0, 0.0);
   glPointSize(pointSize);
   glBegin(GL_POINTS);
      glVertex3f(tempX1, tempY1, 0.0);
   glEnd(); 
}

//====================================================================================//
// Objetivo da Função: desenhar  grid/malha quadriculada
//====================================================================================//
void drawGrid(void) {
   int i;
   
   glEnable(GL_LINE_STIPPLE);
   glLineStipple(1, 0x5555); 
   glColor3f(0.75, 0.75, 0.75);

   glBegin(GL_LINES);
     // Vertical
	  for (i=sizeGrid[2]; i <=sizeGrid[0]; i++)
	  {
         glVertex3f(i*sizeGrid[1]*width, 0.0, 0.0);
         glVertex3f(i*sizeGrid[1]*width, height, 0.0);
	  }
     // Horizontal
	  for (i=1; i <=sizeGrid[0]; i++)
	  {
         glVertex3f(0.1*width, i*sizeGrid[1]*height, 0.0);
         glVertex3f(width, i*sizeGrid[1]*height, 0.0);
	  }
   glEnd();
   glDisable(GL_LINE_STIPPLE);
}

//====================================================================================//
// Objetivo da Função: desenhar as primitivas de forma interativa
//====================================================================================//
void drawInterative(void) {
   float x1,y1,x2,y2;
   
   x1 = tempX1;
   y1 = tempY1;
   x2 = tempX2;
   y2 = tempY2;

   if (primitive == LINE) {
      Line objLine(x1, y1, x2, y2, setColor[0], setColor[1], setColor[2], setStipple);
      objLine.drawLine();
   }

   if (primitive == RECTANGLE) {
      Rectangle objRectangle(x1, y1, x2, y2, setColor[0], setColor[1], setColor[2], modeDraw, setStipple);
      objRectangle.drawRectangle();
   }

   if (primitive == POLYLINE) {
      Polyline objPolyline(x1, y1, x2, y2, setColor[0], setColor[1], setColor[2], setStipple);
      objPolyline.drawPolyline();
   }

   if (primitive == CIRCULE) {
      Circule objCircule(x1, y1, x2, y2, setColor[0], setColor[1], setColor[2], modeDraw, setStipple);
      objCircule.drawCircule();
   }

   if (primitive == HEXAGON) {
      Hexagon objHexagon(x1, y1, x2, y2, setColor[0], setColor[1], setColor[2], modeDraw, setStipple);
      objHexagon.drawHexagon();
   }
   
}

//====================================================================================//
// Objetivo da Função: imprimir textos na janela, conforme a fonte escolhida
//====================================================================================//
void writeBitmapString(void *font, char *string) {  
   char *c;
   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

//====================================================================================//
// Objetivo da Função: escrever as legendas/ajuda conforme for passando o mouse na 
// caixa de seleção
//====================================================================================//
void legend(void) {
   int x, y;

   x = legX;
   y = legY;

   glColor3f(0.0, 0.0, 0.0);
   if ( x < 0.1*width ) {
      if ( y < (1- NUMBERPRIMITIVES*0.1)*height ) {
      } else if ( y < (1 - 5*0.1)*height ) {
         //Hexagono
         glRasterPos3f(55.0, 40.0, 0.0);
         writeBitmapString((void*)font, (char*)"Hexagono");
         glRasterPos3f(55.0, 20.0, 0.0);
         writeBitmapString((void*)font, (char*)"Para criar o hexagono, selecione dois pontos");
      } else if ( y < (1 - 4*0.1)*height ) {
         //Circulo
         glRasterPos3f(55.0, 40.0, 0.0);
         writeBitmapString((void*)font, (char*)"Circulo");
         glRasterPos3f(55.0, 20.0, 0.0);
         writeBitmapString((void*)font, (char*)"Para criar o circulo, selecione dois pontos");
      } else if ( y < (1 - 3*0.1)*height ) {
         //Polilinha
         glRasterPos3f(55.0, 40.0, 0.0);
         writeBitmapString((void*)font, (char*)"Crie Polinhas selecionando pontos");
         glRasterPos3f(55.0, 20.0, 0.0);
         writeBitmapString((void*)font, (char*)"Obs: Clique com o botao do meio para parar a selecao");
         
      } else if ( y < (1 - 2*0.1)*height ) {
         //Retangulo
         glRasterPos3f(55.0, 40.0, 0.0);
         writeBitmapString((void*)font, (char*)"Retangulo");
         glRasterPos3f(55.0, 20.0, 0.0);
         writeBitmapString((void*)font, (char*)"Para criar um retangulo, selecione dois pontos");
      } else if ( y < (1 - 1*0.1)*height ) {
         //Linha
         glRasterPos3f(55.0, 40.0, 0.0);
         writeBitmapString((void*)font, (char*)"Linha");
         glRasterPos3f(55.0, 20.0, 0.0);
         writeBitmapString((void*)font, (char*)"Para criar uma linha, selecione dois pontos");
      } else {
         //Ponto
         glRasterPos3f(55.0, 40.0, 0.0);
         writeBitmapString((void*)font, (char*)"Ponto");
         glRasterPos3f(55.0, 20.0, 0.0);
         writeBitmapString((void*)font, (char*)"Selecione uma posicao");
      }
   }
}

//====================================================================================//
// Rotina de desenho para a janela principal
//====================================================================================//
void drawScene(void) {
   glClear(GL_COLOR_BUFFER_BIT);

   legend();

   //desenha interativamente ate o segundo click do mouse
   if (pointCount == 1)
      drawInterative();

   drawPoints();
   drawLines();
   drawRectangles();
   drawPolylines();
   drawCircules();
   drawHexagons();
   if ( ((primitive == LINE) || (primitive == RECTANGLE) || (primitive == POLYLINE) || (primitive == CIRCULE) || (primitive == HEXAGON)) &&
	   (pointCount == 1) ) drawTempPoint();
   if (isGrid) drawGrid();

   drawPointSelectionBox();
   drawLineSelectionBox();
   drawRectangleSelectionBox();
   drawPolylineSelectionBox();
   drawCirculeSelectionBox();
   drawHexagonSelectionBox();
   drawInactiveArea();

   glutSwapBuffers();
}

//====================================================================================//
// Objetivo da Função: pegar a opção escolhida na caixa de seleção
//====================================================================================//
void pickPrimitive(int y) {
   if ( y < (1- NUMBERPRIMITIVES*0.1)*height ) primitive = INACTIVE;
   else if ( y < (1 - 5*0.1)*height ) primitive = HEXAGON;
   else if ( y < (1 - 4*0.1)*height ) primitive = CIRCULE;
   else if ( y < (1 - 3*0.1)*height ) primitive = POLYLINE;
   else if ( y < (1 - 2*0.1)*height ) primitive = RECTANGLE;
   else if ( y < (1 - 1*0.1)*height ) primitive = LINE;
   else primitive = POINT;
}

//====================================================================================//
// Objetivo da Função: controlar os clicks do mouse
//====================================================================================//
void mouseControl(int button, int state, int x, int y) {
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
      y = height - y; // correção da coordenada do mouse.

      if ( x < 0 || x > width || y < 0 || y > height ) ;

      // Seleciona um item da caixa de seleção
      else if ( x < 0.1*width ) {
	      pickPrimitive(y);
		   pointCount = 0;
         legX = x;
         legY = y;
	   }

	   // Click no canvas.
      else {
	     
         if (primitive == POINT) points.push_back( Point(x,y, setColor[0], setColor[1], setColor[2]) );
         
         else if (primitive == LINE) { 
	         if (pointCount == 0) {
               tempX1 = x; tempY1 = y;
               tempX2 = tempX1; tempY2 = tempY1;  // pega o estado onde se inicia para ir atualizando
		         pointCount++;

			   } else {
               lines.push_back( Line(tempX1, tempY1, x, y, setColor[0], setColor[1], setColor[2], setStipple) );
		         pointCount = 0;
			   }

		   } else if (primitive == RECTANGLE) { 
	         if (pointCount == 0) {
               tempX1 = x; tempY1 = y;
               tempX2 = tempX1; tempY2 = tempY1;
		         pointCount++;

			   } else {
               rectangles.push_back( Rectangle(tempX1, tempY1, x, y, setColor[0], setColor[1], setColor[2], modeDraw, setStipple) );
		         pointCount = 0;
			   }
         } else if (primitive == POLYLINE) {
            if (pointCount == 0) {
               tempX1 = x; tempY1 = y;
		         pointCount++;

			   } else {
               polylines.push_back( Polyline(tempX1, tempY1, x, y, setColor[0], setColor[1], setColor[2], setStipple) );
               tempX1 = x; tempY1 = y;
               tempX2 = tempX1; tempY2 = tempY1;
			   }

		   } else if (primitive == CIRCULE) {
            if (pointCount == 0) {
               tempX1 = x; tempY1 = y;
               tempX2 = tempX1; tempY2 = tempY1;
		         pointCount++;

			   } else {
               circules.push_back( Circule(tempX1, tempY1, x, y, setColor[0], setColor[1], setColor[2], modeDraw, setStipple) );
		         pointCount = 0;
			   }
         } else if (primitive == HEXAGON) {
            if (pointCount == 0) {
               tempX1 = x; tempY1 = y;
               tempX2 = tempX1; tempY2 = tempY1;
		         pointCount++;

			   } else {
               hexagons.push_back( Hexagon(tempX1, tempY1, x, y, setColor[0], setColor[1], setColor[2], modeDraw, setStipple) );
		         pointCount = 0;
			   }
         }
	   }
   }

   if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
      pointCount = 0;
   }

   glutPostRedisplay();
}

//====================================================================================//
// Objetivo da Função: pegar as coordenadas do segundo ponto conforme o movimento do mouse
//====================================================================================//
void mouseMotion(int x, int y) {
   if (pointCount == 1) {
      tempX2 = x;
      tempY2 = height - y;
   } 

   if (pointCount == 0) {
      legX = x;
      legY = height - y;
   }

   glutPostRedisplay();
}

//====================================================================================//
// Objetivo da Função: Inicializar a janela
//====================================================================================//
void setup(void) {
   glClearColor(1.0, 1.0, 1.0, 0.0); 
}

//====================================================================================//
// Objetivo da Função: Reformular a rotina para a janela
//====================================================================================//
void resize(int w, int h) {
   glViewport(0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Set viewing box dimensions equal to window dimensions.
   glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);
   
   // Pass the size of the OpenGL window to globals.
   width = w; 
   height = h;  

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

//====================================================================================//
// Objetivo da Função: processar a entrada do teclado
//====================================================================================//
void keyInput(unsigned char key, int x, int y) {
   switch (key) 
   {
      case 27:
         exit(0);
         break;
      default:
         break;
   }
}

//====================================================================================//
// Objetivo da Função: limpar tudo do canvas
//====================================================================================//
void clearAll(void) {
   points.clear();
   lines.clear();
   rectangles.clear();
   polylines.clear();
   circules.clear();
   hexagons.clear();
   primitive = INACTIVE;
   pointCount = 0;
   // reset color
   setColor[0] = 0.0;
   setColor[1] = 0.0;
   setColor[2] = 0.0;
   // reset mode
   modeDraw = 1;
   // reset stipple
   setStipple = 0;
}

//====================================================================================//
// Objetivo da função: tratar a opção de saida do menu e de limpar o canvas.
//====================================================================================//
void rightMenu(int id) {
   if (id==1) 
   {
	  clearAll();
	  glutPostRedisplay();
   }
   if (id==2) exit(0);
}

//====================================================================================//
// Objetivo da função: tratar a opção "Grid" do menu
//====================================================================================//
void grid_menu(int id) {
   if (id==1) isGrid = 1;
   if (id==2) isGrid = 0;
   glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: tratar a opção "Color" do menu
//====================================================================================//
void color_menu(int id) {
   if (id == 1) {
      // Blue
      setColor[0] = 0.0;
      setColor[1] = 0.0;
      setColor[2] = 1.0;
   }
   if (id == 2) {
      // Red
      setColor[0] = 1.0;
      setColor[1] = 0.0;
      setColor[2] = 0.0;
   }
   if (id == 3) {
      // Yellow
      setColor[0] = 1.0;
      setColor[1] = 1.0;
      setColor[2] = 0.0;
   } 
   if (id == 4) {
      // Green
      setColor[0] = 0.0;
      setColor[1] = 1.0;
      setColor[2] = 0.0;
   }
   if (id == 5) {
      //Black
      setColor[0] = 0.0;
      setColor[1] = 0.0;
      setColor[2] = 0.0;
   }

   glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: tratar a opção "Size" do sub-menu "Grid"
//====================================================================================//
void size_grid(int id) {
   // Small
   if (id == 1) { 
      sizeGrid[0] = 19; //ate onde vai
      sizeGrid[1] = 0.05; //fator de dividi
      sizeGrid[2] = 3;  //onde inicia
   }
   // Medium
   if (id == 2) {
      sizeGrid[0] = 9;
      sizeGrid[1] = 0.1;
      sizeGrid[2] = 2; 
   }
   // Large
   if (id == 3) {
      sizeGrid[0] = 4;
      sizeGrid[1] = 0.2;
      sizeGrid[2] = 1;      
   }

   glutPostRedisplay();   
}

//====================================================================================//
// Objetivo da função: tratar a opção "Mode" do menu
//====================================================================================//
void mode_menu(int id) {
   if (id == 1) {
      modeDraw = 1;
   }  
   if (id == 2) {
      modeDraw = 0;
   }

   glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: tratar a opção "Stipple" do menu
//====================================================================================//
void stipple_menu(int id) {
   if (id == 1) {
      setStipple = 1;
   }
   if (id == 2) {
      setStipple = 0;
   }

   glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: criar o menu
//====================================================================================//
void makeMenu(void) {
   int sub_menu_grid, sub_menu_color, sub_menu_grid_size, sub_menu_mode, sub_menu_stipple;

   sub_menu_grid_size = glutCreateMenu(size_grid);
   glutAddMenuEntry("Small", 1);
   glutAddMenuEntry("Medium", 2);
   glutAddMenuEntry("Large", 3);

   sub_menu_grid = glutCreateMenu(grid_menu);
   glutAddMenuEntry("On", 1);
   glutAddMenuEntry("Off", 2);
   glutAddSubMenu("Size", sub_menu_grid_size);

   sub_menu_color = glutCreateMenu(color_menu);
   glutAddMenuEntry("Blue", 1);
   glutAddMenuEntry("Red", 2);
   glutAddMenuEntry("Yellow", 3);
   glutAddMenuEntry("Green", 4);
   glutAddMenuEntry("Black", 5);

   sub_menu_mode = glutCreateMenu(mode_menu);
   glutAddMenuEntry("Outlined", 1);
   glutAddMenuEntry("Filled", 2);

   sub_menu_stipple = glutCreateMenu(stipple_menu);
   glutAddMenuEntry("Enabled", 1);
   glutAddMenuEntry("Disabled", 2);

   glutCreateMenu(rightMenu);
   glutAddSubMenu("Grid", sub_menu_grid);
   glutAddSubMenu("Color", sub_menu_color);
   glutAddSubMenu("Mode", sub_menu_mode);
   glutAddSubMenu("Stipple", sub_menu_stipple);
   glutAddMenuEntry("Clear",1);
   glutAddMenuEntry("Quit",2);
   glutAttachMenu(GLUT_RIGHT_BUTTON);
}

//====================================================================================//
// Objetivo da função: informar as possiveis interações com o usuário, no terminal
//====================================================================================//
void printInteraction(void) {
   cout << "Interação:" << endl;
   cout << "Left click on a box on the left to select a primitive." << endl
        << "Then left click on the drawing area: once for point, twice for line, rectangle, polyline, cirule or hexagon" << endl
        << "Right click for menu options." <<  endl; 
}

//====================================================================================//
//                      PRINCIPAL
//====================================================================================//
int main(int argc, char **argv) {
   printInteraction();
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_DOUBLE); 
   
   // Definicição da janela
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);

   // Cria a janela com o titulo e returna um ID
   glutCreateWindow("canvas.cpp");

   // Inicialização das funçoes da janela
   setup(); 
   glutDisplayFunc(drawScene); 
   glutReshapeFunc(resize);  
   glutKeyboardFunc(keyInput);
   glutMouseFunc(mouseControl); 
   glutPassiveMotionFunc(mouseMotion);
   makeMenu(); // Cria menu.

   glutMainLoop(); 

   return 0;  
}