////////////////////////////////////////////////////         
// straights.cpp
//
// Descrição da Prova(PP1):
// Desenvolver um aplicativo em OPENGL e C/C++ que inclua interação via mouse e teclado, texto e
// menus para apresentar de forma didática os tópicos especificados abaixo. Na maioria de tópicos
// forneço alguns links de aulas e/ou animações que podem servir de inspiração.
// 
// Projeto: Retas
// 
// Objetivos: 
// - Reta definida por dois pontos - ok
// - Reta definida por ponto e vetor - ok
// - Equação paramétrica de um segmento de reta - ok
// - Ângulo entre retas - ok
// - Retas paralelas - ok   
// - Retas ortogonais - ok
//
// João Vitor de Oliveira - 38342
// Linha de compilação: g++ -o exe straights.cpp -lglut -lGLU -lGL -lm
///////////////////////////////////////////////////// 

#include <cmath>
#include <vector>
#include <iostream>
#include <cstring>
#include <sstream>

#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif

// Constantes
    // Define o "Infinito" //
#define INF 9999
    // Definido largura e altura das janelas //
#define WIDTH_M 100
#define HEIGHT_M 600    
#define WIDTH_D 600
#define HEIGHT_D 600
    // Define Valor de PI //
#define PI 3.14159265358979324
    // Define Opções de Desenho //
#define INACTIVE 0              
#define TWO_POINTS 1            // Reta definida por dois pontos
#define VECTOR_POINT 2          // Reta definida por ponto e vetor
#define LINE_SEGMENT 3          // Equação paramétrica de um segmento de reta
#define ANGLES_LINE 4           // Ângulo entre retas
#define PARALLEL_STRAIGHT 5     // Retas paralelas
#define ORTHOGONAL_STRAIGHT 6   // Retas ortogonais

using namespace std;

    // Variaveis Globais //
static int menuOp, display; // identificadores das janelas
static float pointSize = 6.0; // tamanho do ponto
static int operation = INACTIVE; // operação  
static int tempX, tempY;    // temporaria do primeiro ponto
static int tempX2, tempY2;  // temporaria do segundo ponto
static int pointCount = 0;  // Contador para os pontos
static int pointVectorPoint[2] = {0 , 0}; //Auxiliar para o ponto da Classe VectorPoint
static int straightCount = 0; //Contador de Retas
static float firstStraight[2] = {0.0, 0.0}; //vetor da primeira reta - para o Angulo entre retas 
static float secondStraight[2] = {0.0, 0.0}; //vetor da primeira reta - para o Angulo entre retas 
static int upWidth = 150;
static long font = (long)GLUT_BITMAP_8_BY_13; // seleção da fonte.
static int modeEquation = 1;
static int modeExhibition = 1;
static int Counter = 0;
    // Variaveis do tamanho das janelas //
static int width_m = WIDTH_M;
static int height_m = HEIGHT_M;
static int width_d = WIDTH_D;
static int heigth_d = HEIGHT_D; 

    // Variaveis para fazer a translação do angulo entre duas retas // 
static int movimentCounter = 0;
static int movimentX, movimentY;
static int movimentTempX = 0, movimentTempY = 0;
static int counterX = 0, counterY = 0;  
static int someCounterX = 0, someCounterY = 0;

//====================================================================================//
// Objetivo da função: imprimir textos na janela, conforme a fonte escolhida
//====================================================================================//
void writeBitmapString(void *font, char *string)
{  
   char *c; 

   for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

//====================================================================================//
// Classe que representa a reta definida por dois pontos 
//====================================================================================//
class TwoPoints {
private:
    // Pontos para definir a reta
    int x1, y1, x2, y2;
    // Coodernadas do vetor da reta
    float v1, v2;
public:
    // Construtor 
    TwoPoints(int x1Val, int y1Val, int x2Val, int y2Val) {
        
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;    
             
    }
    // Construtor para desenhar a reta de modo interativo
    TwoPoints() { }
    // Desenha a Reta
    void drawTwoPoints(void); 

    // Desenha a Reta de modo interativo
    void drawTwoPointsInterativeClass(int, int, int, int);

    // Mostra a equação geral da reta
    void equationOverall();
};

//====================================================================================//
// Objetivo da função: Desenhar os pontos que foram selecionados e a reta gerada 
// a partir deles.
//====================================================================================//
void TwoPoints::drawTwoPoints() {
    int t;

    // definindo as coordenadas do vetor: V = (v1, v2)
    v1 = x2-x1;
    v2 = y2-y1;

    // Primeiro Ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
       glVertex3f(x1, y1, 0.0); 
    glEnd();
    
    // Reta
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        for (t = -INF; t < INF; t++)
        {
            // Equação parametrica da Reta, onde t é um valor que varia assim achamos outros pontos da reta
            glVertex3f( x1 + t*v1 , y1 + t*v2 , 0.0);
        }
    glEnd();
    glLineWidth(1.0);

    // Segundo ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(x2, y2, 0.0);
    glEnd();

    // Texto dos Pontos
    glColor3f(0, 0, 100);
    if (fabs(v2/v1) > 0 && fabs(v2/v1) < 0.80)
        glRasterPos3f(x1, y1+10, 0.0);
    else
        glRasterPos3f(x1+10, y1, 0.0);
    
    writeBitmapString((void*)font, (char*)"A");
    if (fabs(v2/v1) > 0 && fabs(v2/v1) < 0.80)
        glRasterPos3f(x2, y2+10, 0.0);
    else 
        glRasterPos3f(x2+10, y2, 0.0);
    writeBitmapString((void*)font, (char*)"B");

}

//====================================================================================//
// Objetivo da função: desenhar os pontos e a reta gerada por eles de forma interativa
//====================================================================================//
void TwoPoints::drawTwoPointsInterativeClass(int x1, int y1, int x2, int y2) {
    int t;

    // Calculo das coordenadas do vetor
    v1 = x2 - x1;
    v2 = y2 - y1;

    // Reta
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for (t = -INF; t < INF; t++)
    {
        // Equação parametrica da Reta, onde t pertence aos Reais
        glVertex3f( x1 + t*v1 , y1 + t*v2 , 0.0);
    }
    glEnd();
    glLineWidth(1.0);


    // Primeiro e Segundo ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    glEnd();

    if (operation == TWO_POINTS) {
        // Texto dos pontos
        glColor3f(0, 0, 100);
        if (fabs(v2/v1) > 0 && fabs(v2/v1) < 0.80)
            glRasterPos3f(x1, y1+10, 0.0);
        else
            glRasterPos3f(x1+10, y1, 0.0);
        
        writeBitmapString((void*)font, (char*)"A");
    }           
}

//====================================================================================//
// Objetivo da função: calcular a equação geral da reta e imprimir na tela  
//====================================================================================//
void TwoPoints::equationOverall() {
    float m;
    float tempEq;
    char term[33];
    char equation[33];
    
    glColor3f(100, 0, 0);
    // Se a reta for paralela ao eixo y - logo x = k
    if ((x2-x1) == 0) {
        m = 0;
        strcpy(equation, (char*)"Eq: x = ");
        sprintf(term, "%d", x1);    // transforma o x em string
        strcat(equation, term);     // concatena com a equação
        // definindo o posicionamento da eq. da reta
        if (x1 > 0 && x1 < 500)        
            glRasterPos3f(x1+10, (y2+y1)/2, 0.0);
        else 
            glRasterPos3f(x1-100, (y2+y1)/2, 0.0);

        // imprime na janela a eq.
        writeBitmapString((void*)font, equation);
        return;  //sair
    }else {
        // calculo do coeficiente angular da reta
        m = ((y2-y1)*1.0)/(x2-x1);
    }
    // se o coeficiente for 0, logo a reta é paralela ao eixo x - sua eq é y = k
    if (m > -0.0000001 && m < 0.0000001) {
        strcpy(equation, (char*)"Eq: y = ");
        sprintf(term, "%d", y1);  // transforma o y em string
        strcat(equation, term);   // concatena com a equação    
        
        // definindo o posicionamento da eq. da reta
        if (y1 > 0 && y1 < 450) 
            glRasterPos3f((x2+x1)/2 - 30, y1 + 10, 0.0);
        else 
            glRasterPos3f((x2+x1)/2 - 30, y1 - 20, 0.0);

        // imprime na janela a eq.
        writeBitmapString((void*)font, equation);
        return;  // sair
    // se o coeficiente é diferente de 0
    } else if (m > 0){
        strcpy(equation, (char*)"Eq: y - ");
        sprintf(term, "%.2f", m);
        strcat(term, "x");
        strcat(equation, term); 

    } else {
        strcpy(equation, (char*)"Eq: y + ");
        sprintf(term, "%.2f", m*-1.0);
        strcat(term, "x");
        strcat(equation, term); 
    }

    tempEq = m*x1 - y1;
    if (tempEq > 0) {
        strcat(equation, " + ");
        sprintf(term, "%.2f", tempEq);
        strcat(equation, term);       
    } else {
        strcat(equation, " - ");
        sprintf(term, "%.2f", tempEq*-1.0);
        strcat(equation, term); 
    }
    
    strcat(equation, (char*)" = 0");
    // onde será exibido a equação 
    if (modeExhibition == 1) 
        glRasterPos3f(50.0, 30.0, 0.0);  // lado esquerdo
    else
        glRasterPos3f(350.0, 30.0, 0.0); // lado direito
    writeBitmapString((void*)font, equation);
}


// Vetor da Classe TwoPoints
vector<TwoPoints> twoPoints;

// Iterator para manipular o Vetor.
vector<TwoPoints>::iterator twoPointsIterator; 

//====================================================================================//
// Classe que representa a reta definida por  ponto e vetor 
//====================================================================================//
class VectorPoint {

private:
    // Coordenadas do Ponto
    int ptx, pty;
    // Coodernadas do vetor da reta
    float v1, v2;
    int x1, x2, y1, y2;

    
public: 
    // Construtor
    VectorPoint(int x, int y, int x1Val, int y1Val, int x2Val, int y2Val ) {
            
        ptx = x; pty = y; 
        x1 = x1Val; y1 = y1Val;
        x2 = x2Val; y2 = y2Val; 
             
    }

    VectorPoint() { }

    // Desenha o vetor, o ponto e por fim a Reta gerada
    void drawVectorPoint(void);

    // Desenha o Ponto e o Vetor - enquanto estiver no modo interativo
    void drawVectorPointInterativeClass(int, int, int, int, int, int);
    
    // desenha a seta que indica direção do vetor
    void drawArrow(int, int, int, int);
};

//====================================================================================//
// Objetivo da função: Desenhar a seta (direção) do vetor diretor da reta
//====================================================================================//
void VectorPoint::drawArrow(int xo, int yo, int xf, int yf) {
    float w1, w2, param, angule;

    // vetor diretor da reta
    w1 = xf-xo;
    w2 = yf-yo;  

    // parametro para o calculo do angulo entre duas retas
    param = ( w1*1.0 + w2*0.0 ) / ( sqrt(w1*w1 + w2*w2) + sqrt(1.0) ); 

    // angulo entre o vetor diretor da reta e o vetor diretor da reta X(1.0 , 0.0) 
    angule = acos (param) * 180.0 / PI;    

    glColor3f(100.0, 0.0, 0.0);
    glPushMatrix();
        glTranslatef(xf, yf, 0.0);
        if (yf > yo)
            glRotatef(angule, 0.0, 0.0, 1.0);
        else 
            glRotatef(-angule, 0.0, 0.0, 1.0);
            
        glBegin(GL_TRIANGLES);
            glVertex3f(0, 7 , 0.0);
            glVertex3f(0, -7 , 0.0);
            glVertex3f(14, 0, 0.0);
        glEnd();    
    glPopMatrix();
}

//====================================================================================//
// Objetivo da função: Desenhar o Ponto e o Vetor definidos primeiramente, depois 
// desenha a reta que é definida pelo ponto e seu vetor diretor dela
//====================================================================================//
void VectorPoint::drawVectorPoint() {
    int t;
    
    // definindo o vetor diretor v = (v1, v2)
    v1 = x2 - x1;
    v2 = y2 - y1;


    // Desenha a Reta
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        for (t = -INF; t < INF; t++)
        {
            // Equação parametrica da Reta, onde t pertence aos Reais
            glVertex3f( ptx + t*v1 , pty + t*v2 , 0.0);
        }
    
    glEnd();
    // Desenha o Ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(ptx, pty, 0.0);
    glEnd();

    // Desenha o Vetor
    glColor3f(100.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    glEnd();

    drawArrow(x1, y1, x2, y2);
    
    glLineWidth(1.0);
}
//====================================================================================//
// Objetivo da função: desenhar o Ponto e o Vetor (de forma interativa com o mouse)
//====================================================================================//
void VectorPoint::drawVectorPointInterativeClass(int ptx, int pty, int x1, int y1, int x2, int y2) {
    v1 = x2 - x1;
    v2 = y2 - y1;

    //Desenha o Ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(ptx, pty, 0.0);
    glEnd();

    if (pointCount == 2) {
        //Desenha o Vetor
        glColor3f(100.0, 0.0, 0.0);
        glLineWidth(2.0);
        glBegin(GL_LINES);
            glVertex3f(x1, y1, 0.0);
            glVertex3f(x2, y2, 0.0);
        glEnd();

        //desenha a setinha
        drawArrow(x1, y1, x2, y2);

        glLineWidth(1.0);
    }
}

// Vetor da Classe VectorPoint
vector<VectorPoint> vectorPoint;

// Iterator para manipular o Vetor
vector<VectorPoint>::iterator vectorPointIterator;

//====================================================================================//
// Classe que representa a equação paramétrica de um segmento de reta
//====================================================================================//
class LineSegment {

private:
    // Pontos para definir a reta
    int x1, y1, x2, y2;
    // Coodernadas do vetor da reta
    float v1, v2;
public:
    // Construtor 
    LineSegment(int x1Val, int y1Val, int x2Val, int y2Val) {
        
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;    
             
    }

    LineSegment() { }

    // Desenha a Reta e as paralelas a ela
    void drawLineSegment(void);

    // Desenha a Reta Principal de modo interativo
    void drawLineSegmentInterativeClass(int, int, int, int);

    // mostra a equação paramétrica do segmento de reta
    void equationParametric();
};

//====================================================================================//
// Objetivo da função: desenhar o segmento de reta, utilizando os dois pontos selecionados
//====================================================================================//
void LineSegment::drawLineSegment() {
    int t;

    // definindo o vetor: v=(v1,v2)
    v1 = x2 - x1;
    v2 = y2 - y1;

    // Segmento de reta
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    // Como é um segmento de reta o intervalo é 0 <= t <= 1 
    for (t = 0; t <= 1; t++)
    {   
        // Equação parametrica do Segmento de reta
        glVertex3f( x1 + t*v1 , y1 + t*v2 , 0.0);   
    }
    glEnd();
    glLineWidth(1.0);

    // Primeiro e Segundo ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    glEnd();
}

//====================================================================================//
// Objetivo da função: desenhar o segmento de reta (de forma interativa com o mouse).
//====================================================================================//
void LineSegment::drawLineSegmentInterativeClass(int x1, int y1, int x2, int y2) {
    int t;

    // Primeiro ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(x1, y1, 0.0);
    glEnd();

    // Calculo das coordenadas do vetor
    v1 = x2 - x1;
    v2 = y2 - y1;

    // Segmento de reta
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    // Como é um segmento de reta o intervalo é 0 <= t <= 1 
    for (t = 0; t <= 1; t++)
    {   
        // Equação parametrica do Segmento de reta
        glVertex3f( x1 + t*v1 , y1 + t*v2 , 0.0);   
    }
    glEnd();
    glLineWidth(1.0);

    // Segundo ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(x2, y2, 0.0);
    glEnd();
}

//====================================================================================//
// Objetivo da função: Calcular a equação Paramétrica do segmento de reta e mostrar na
// janela de desenho.
//====================================================================================//
void LineSegment::equationParametric() {
    char equationX[33];
    char equationY[33];
    char interval[15] = {"0 <= t <= 1"};
    char aux[10];
    float tmp;

    v1 = x2 - x1;
    v2 = y2 - y1;

    strcpy(equationX, (char*)"X = ");
    strcpy(equationY, (char*)"Y = ");

    sprintf(aux, "%d", x1);
    strcat(equationX, aux);
    sprintf(aux, "%d", y1);
    strcat(equationY, aux);

    if (v1 < 0.0) {
        // negativo
        strcat(equationX, (char*)" - ");
        tmp = fabs(v1);
    } else {
        // positivo
        strcat(equationX, (char*)" + ");
        tmp = v1;
    }
    sprintf(aux, "%.2f", tmp);
    strcat(equationX, aux);

    if (v2 < 0.0) {
        // negativo
        strcat(equationY, (char*)" - ");
        tmp = fabs(v2);
    } else {
        // positivo
        strcat(equationY, (char*)" + ");
        tmp = v2;
    }
    sprintf(aux, "%.2f", tmp);
    strcat(equationY, aux);

    strcat(equationX, (char*)"t");
    strcat(equationY, (char*)"t");

    // onde será exibido a equação 
    glColor3f(100.0, 0.0, 0.0);
    if (modeExhibition == 1) {
        glRasterPos3f(50.0, 40.0, 0.0);  // lado esquerdo
        writeBitmapString((void*)font, equationX);
        glRasterPos3f(50.0, 20.0, 0.0);  
        writeBitmapString((void*)font, equationY);
        glRasterPos3f(50.0, 60.0, 0.0); 
        writeBitmapString((void*)font, interval);
    } else {
        glRasterPos3f(400.0, 40.0, 0.0); // lado direito
        writeBitmapString((void*)font, equationX);
        glRasterPos3f(400.0, 20.0, 0.0);  
        writeBitmapString((void*)font, equationY);
        glRasterPos3f(400.0, 60.0, 0.0); 
        writeBitmapString((void*)font, interval);
    }      
}

// Vetor da Classe LineSegment
vector<LineSegment> lineSegment;

// Iterator para manipular o vetor
vector<LineSegment>::iterator lineSegmentIterator;

//====================================================================================//
// Classe que representa o Ãngulo entre retas
//====================================================================================// 
class AnglesLine {
private:
    // Pontos para definir a reta
    int x1, y1, x2, y2;
    // Coodernadas do vetor da reta
    float v1, v2;
public:
    // Construtor
    AnglesLine(int x1Val, int y1Val, int x2Val, int y2Val) {
        
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;    
             
    }
    // Construtor para desenhar a reta de modo interativo
    AnglesLine() { }
    // Desenha as duas Retas
    void drawAnglesLine(void); 

    // Desenha a Reta de modo interativo
    void drawAnglesLineInterativeClass(int, int, int, int);

    // calcula o angulo entre as retas e monstra na janela
    void calculeAngle();
};

//====================================================================================//
// Objetivo da função: desenhar as duas retas para depois calcular o ângulo ente elas
//====================================================================================//
void AnglesLine::drawAnglesLine() {
    int t;

    // Calculo das coordenadas do vetor
    v1 = x2 - x1;
    v2 = y2 - y1;

    // salva as coordenadas do vetor em uma variavel auxiliar
    if (straightCount == 1) {
        firstStraight[0] = v1;
        firstStraight[1] = v2;
    } else {
        secondStraight[0] = v1;
        secondStraight[1] = v2;
    }

    // Reta
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);

    glPushMatrix();
    if (movimentCounter == 1) {
        glTranslatef((movimentTempX-movimentX)+someCounterX, movimentTempY-movimentY+someCounterY, 0);
    
    } else {
        glTranslatef(someCounterX, someCounterY, 0);
    }
    glBegin(GL_LINE_STRIP);
        for (t = -INF; t < INF; t++) {
            // Equação parametrica da Reta, onde t pertence aos Reais
            glVertex3f( x1 + t*v1 , y1 + t*v2 , 0.0);
        }
    glEnd();
    glLineWidth(1.0);
    glPopMatrix();
}

//====================================================================================//
// Objetivo da função: desenhar as retas de forma interativa, usando a 
// class TwoPoints (reta definida por dois pontos)
//====================================================================================//
void AnglesLine::drawAnglesLineInterativeClass(int x1, int y1, int x2, int y2) {
    TwoPoints obj;
    obj.drawTwoPointsInterativeClass(x1, y1, x2, y2);
}

//====================================================================================//
// Objetivo da função: calcular o ângulo entre as retas, e depois mostrar na janela 
//====================================================================================//
void AnglesLine::calculeAngle() {
    // coeficientes angular das duas retas
    float ms, mr;
    float tgAlpha = 1;
    float angule;
    float msX = firstStraight[0], msY = firstStraight[1]*1.0;
    float mrX = secondStraight[0], mrY = secondStraight[1]*1.0;

    if (straightCount == 2) {

        // se x nao varia
        if ( msX == 0) {
            if (mrX == 0 ) {
                angule = 0;
            } else {
                mr = mrY/mrX;
                tgAlpha = fabs(1/mr);
                angule = atan(tgAlpha) * 180/ PI;
            }
        } else if (mrX == 0) {
            if (msY == 0) {
                angule = 90;
            } else {
                ms = msY/msX;  // coeficiente angula da primeira reta
                tgAlpha = fabs(1/ms);
                angule = atan(tgAlpha) * 180/ PI;
            }
        } else {
            ms = msY/msX;  // coeficiente angula da primeira reta
            mr = mrY/mrX; // coeficiente angular da segunda reta
            // tg x = modulo( (m1-m2)/(1+m1*m2) )
            tgAlpha = fabs( (ms-mr)/(1+ms*mr) );
            angule = atan(tgAlpha) * 180/ PI;
        }

        

        char sAngule[8];
        
        sprintf(sAngule, "%.2f", angule);

        glColor3f(100,0,0);
        if (modeExhibition == 1) {
            // lado esquerdo
            glRasterPos3f(50, 40, 0);
        } else {
            // lado direito
            glRasterPos3f(350, 40, 0);
        }

        writeBitmapString((void*)font, (char*)"           ");

        if (Counter == 1) {
            writeBitmapString((void*)font, sAngule);
            Counter = 0;
        } else {
            Counter++;
        }
    }
}

// Vetor da Classe AnglesLine
vector<AnglesLine> anglesLine;      

// Iterator para manipular o vetor
vector<AnglesLine>::iterator anglesLineIterator;

//====================================================================================//
// Classe que representa as Retas Paralelas
//====================================================================================//
class ParallelStraight {

private:
    // Pontos para definir a reta
    int x1, y1, x2, y2;
    // Coodernadas do vetor da reta
    float v1, v2;
public:
    // Construtor 
    ParallelStraight(int x1Val, int y1Val, int x2Val, int y2Val) {
        
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;    
             
    }

    ParallelStraight() { }

    // Desenha a Reta e as paralelas a ela
    void drawParallelStraight(void);

    // Desenha a Reta Principal de modo interativo
    void drawParallelStraightInterativeClass(int, int, int, int);
};

//====================================================================================//
// Objetivo da função: desenhar a reta principal e as paralelas a ela
//====================================================================================//
void ParallelStraight::drawParallelStraight() {
    int t;
    int cont = -40;
    float m; // coeficiente angular da reta

    // Calculo das coordenadas do vetor
    v1 = x2 - x1;
    v2 = y2 - y1;

    m = v2/v1;

    // Retas Paralelas
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
    for (int i = 1; i <= 3; i++) {
        for (t = -INF; t < INF; t++)
        {   
            i == 2 ? glColor3f(100.0, 0.0, 0.0) : glColor3f(0.0, 0.0, 0.0);
            if (fabs(m) > 1) {
                // Equação parametrica da Reta, onde t pertence aos Reais
                glVertex3f( (x1+cont) + t*v1 , y1 + t*v2 , 0.0);
            } else {
                // Equação parametrica da Reta, onde t pertence aos Reais
                glVertex3f( x1 + t*v1 , (y1+cont) + t*v2 , 0.0);
            }
        }
        cont = cont + 40;
    }
    glEnd();
    glLineWidth(1.0);

    // Primeiro e Segundo ponto
    glPointSize(5.0);
    glColor3f(0.0, 0.0, 100.0);
    glBegin(GL_POINTS);
        glVertex3f(x1, y1, 0.0);
        glVertex3f(x2, y2, 0.0);
    glEnd();
}

//====================================================================================//
// Objetivo da função: desenhar a reta principal de forma interativa, utilizando a classe
// TwoPoints (reta definida por dois pontos)
//====================================================================================//
void ParallelStraight::drawParallelStraightInterativeClass(int x1, int y1, int x2, int y2) {
    TwoPoints obj;
    obj.drawTwoPointsInterativeClass(x1, y1, x2, y2);
}
// Vetor da Classe ParallelStraight
vector<ParallelStraight> parallelStraight;

// Iterator para manipular o vetor
vector<ParallelStraight>::iterator parallelStraightIterator;

//====================================================================================//
// Classe que representa as Retas Paralelas 
//====================================================================================//
class OrthogonalStraight {

private:
    //Pontos para definir a reta
    int x1, y1, x2, y2;
    // Coodernadas do vetor da reta
    float v1, v2;
public:
    //Construtor 
    OrthogonalStraight(int x1Val, int y1Val, int x2Val, int y2Val) {
        
        x1 = x1Val; y1 = y1Val; x2 = x2Val; y2 = y2Val;    
             
    }

    OrthogonalStraight() { }

    //Desenha a Reta e sua Ortogonal
    void drawOrthogonalStraight(void);

    //Desenha a Reta Principal de modo interativo
    void drawOrthogonalStraightInterativeClass(int, int, int, int);

};

//====================================================================================//
// Objetivo da função: desenhar uma reta a partir de dois pontos, depois desenhar uma 
// reta ortogonal a primeira.
//====================================================================================//
void OrthogonalStraight::drawOrthogonalStraight() {
    int t;
    float w1, w2;
    int q1, q2; 

    //Calculo das coordenadas do vetor
    v1 = x2 - x1;
    v2 = y2 - y1;

    //Vetor ortogonal
    w1 = v2*(-1);
    w2 = v1;

    //Ponto para a reta ortogonal
    q1 = (x2+x1)/2;
    q2 = (y2+y1)/2;


    glLineWidth(2.0);
    //Primeira Reta
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
        for (t = -INF; t < INF; t++) {
            // Equação parametrica da Reta, onde t pertence aos Reais
            glVertex3f( x1 + t*v1 , y1 + t*v2 , 0.0);
        }
    glEnd();

    //Reta Ortogonal a primeira Reta
    glColor3f(100.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);
        for (t = -INF; t < INF; t++) {
            // Equação parametrica da Reta, onde t pertence aos Reais
            glVertex3f( q1 + t*w1 , q2 + t*w2 , 0.0);
        }
    glEnd();

    glLineWidth(1.0);
}

//====================================================================================//
// Objetivo da função: desenhar uma reta a partir de dois pontos, de forma interativa,
// usando a classe TwoPoints.
//====================================================================================//
void OrthogonalStraight::drawOrthogonalStraightInterativeClass(int x1, int y1, int x2, int y2) {
    TwoPoints obj;
    obj.drawTwoPointsInterativeClass(x1, y1, x2, y2);
}

// Vetor da Classe OrthogonalStraight
vector<OrthogonalStraight> orthogonalStraight;

// Iterator para manipular o vetor
vector<OrthogonalStraight>::iterator orthogonalStraightIterator;

//====================================================================================//
// Objetivo da função: Desenhar a Grid(grade/quadriculado) na janela de desenho
//====================================================================================//
void drawGrid(void) {
    int i;

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x5555);
    glColor3f(0.8, 0.8, 0.8);

    glBegin(GL_LINES);
        //Vertical
        for (i = 0; i < 30; i++) {
            glVertex3f(i*(width_d/20.0), 0.0, 0.0);
            glVertex3f(i*(width_d/20.0), heigth_d, 0.0);
        }
        //Horizontal
        for (i = 0; i < 30; i++) {
            glVertex3f(0.0, i*(heigth_d/20.0) , 0.0);
            glVertex3f(width_d, i*(heigth_d/20.0), 0.0);
        }
    glEnd();

    glDisable(GL_LINE_STIPPLE);
}

//====================================================================================//
// Objetivo da função: desenhar a caixa de seleção da Reta definida por 2 pontos
//====================================================================================//
void drawTwoPointsSelectionBox(void) {
    
    (operation == TWO_POINTS) ? glColor3f(0.9, 0.9, 0.9) : glColor3f(0.7, 0.7, 0.7); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.833*HEIGHT_M, WIDTH_M, HEIGHT_M);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.833*HEIGHT_M, WIDTH_M, HEIGHT_M);

    // Desenho do icone
    glColor3f(0.0, 0.0, 0.0);

    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(25.0, 0.875*HEIGHT_M, 0.0);
        glVertex3f(70.0, 0.95*HEIGHT_M, 0.0);
    glEnd();
    glLineWidth(1.0);

    glPointSize(6.0);
    glColor3f(0.0, 0.0, 100.0);

    glBegin(GL_POINTS);
        glVertex3f(35.0, 0.8916*HEIGHT_M, 0.0);
        glVertex3f(60.0, 0.9333*HEIGHT_M, 0.0);
    glEnd();
}

//====================================================================================//
// Objetivo da função: desenhar a caixa de seleção da Reta definida por ponto e vetor
//====================================================================================//
void drawVectorPointSelectionBox(void) {
    
    (operation == VECTOR_POINT) ? glColor3f(0.9, 0.9, 0.9) : glColor3f(0.7, 0.7, 0.7); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.666*HEIGHT_M, WIDTH_M, 0.833*HEIGHT_M);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.666*HEIGHT_M, WIDTH_M, 0.833*HEIGHT_M);

    // Desenho do icone
    glColor3f(100.0, 0.0, 0.0);
    
    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(35.0, 0.725*HEIGHT_M, 0.0);
        glVertex3f(60.0, 0.766*HEIGHT_M, 0.0);
    glEnd();
    glLineWidth(1.0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_TRIANGLES);
        glVertex3f(60.0, 0.766*HEIGHT_M, 0.0);
        glVertex3f(50.0, 0.762*HEIGHT_M, 0.0);
        glVertex3f(58.0, 0.745*HEIGHT_M, 0.0);
    glEnd();

    glPointSize(6.0);
    glColor3f(0.0, 0.0, 100.0);

    glBegin(GL_POINTS);
        glVertex3f(35.0, 0.725*HEIGHT_M, 0.0);
    glEnd();
}

//======================Exceção de ponto flutuante ==============================================================//
// Objetivo da função: desenhar a caixa de seleção da Equação paramétrica de um segmento de reta
//====================================================================================//
void drawLineSegmentSelectionBox(void) {
    
    (operation == LINE_SEGMENT) ? glColor3f(0.9, 0.9, 0.9) : glColor3f(0.7, 0.7, 0.7); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.5*HEIGHT_M, WIDTH_M, 0.666*HEIGHT_M);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.5*HEIGHT_M, WIDTH_M, 0.666*HEIGHT_M);

    // Desenho do icone
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINE_STRIP);
        glVertex3f(35.0, 0.5583*HEIGHT_M, 0.0);
        glVertex3f(60.0, 0.6*HEIGHT_M, 0.0);
    glEnd();
    glLineWidth(1.0);

    glPointSize(6.0);
    glColor3f(0.0, 0.0, 100.0);

    glBegin(GL_POINTS);
        glVertex3f(35.0, 0.5583*HEIGHT_M, 0.0);
        glVertex3f(60.0, 0.6*HEIGHT_M, 0.0);
    glEnd();
}

//====================================================================================//
// Objetivo da função: desenhar a caixa de seleção do Ângulo entre retas
//====================================================================================//
void drawAnglesLineSelectionBox(void) {
    float t = 0.0;
    int i;

    (operation == ANGLES_LINE) ? glColor3f(0.9, 0.9, 0.9) : glColor3f(0.7, 0.7, 0.7); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.333*HEIGHT_M, WIDTH_M, 0.5*HEIGHT_M);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.333*HEIGHT_M, WIDTH_M, 0.5*HEIGHT_M);

    // Desenho do icone
    glColor3f(0.0, 0.0, 0.0);

    glLineWidth(2.0);
    glBegin(GL_LINE_STRIP);
        glVertex3f(70.0, 0.3833*HEIGHT_M, 0.0);
        glVertex3f(30.0, 0.3833*HEIGHT_M, 0.0);
        glVertex3f(70.0, 0.4333*HEIGHT_M, 0.0);
    glEnd();

    glBegin(GL_LINE_LOOP);
       for(i = 0; i <= 4; ++i)
       {
          t = 2 * PI * i / 40; 
          glVertex3f( 30.0 + 20 * cos(t), 0.3833*HEIGHT_M + 20 * sin(t), 0.0);
	   }
    glEnd();

    glLineWidth(1.0);
}

//====================================================================================//
// Objetivo da função: desenhar a caixa de seleção das Retas paralelas 
//====================================================================================//
void drawParallelStraightsSelectionBox(void) {

    (operation == PARALLEL_STRAIGHT) ? glColor3f(0.9, 0.9, 0.9) : glColor3f(0.7, 0.7, 0.7); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.166*HEIGHT_M, WIDTH_M, 0.333*HEIGHT_M);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.166*HEIGHT_M, WIDTH_M, 0.333*HEIGHT_M);

    // Desenho do icone
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(2.0);

    glBegin(GL_LINES);
        glVertex3f(30.0, 0.2*HEIGHT_M, 0.0);
        glVertex3f(70.0, 0.266*HEIGHT_M, 0.0);

        glVertex3f(30.0, 0.233*HEIGHT_M, 0.0);
        glVertex3f(70.0, 0.3*HEIGHT_M, 0.0);
    glEnd();

    glLineWidth(1.0);
}

//====================================================================================//
// Objetivo da função: desenhar a caixa de seleção das Retas ortogonais
//====================================================================================//
void drawOrthogonalStraightsSelectionBox(void) {

    (operation == ORTHOGONAL_STRAIGHT) ? glColor3f(0.9, 0.9, 0.9) : glColor3f(0.7, 0.7, 0.7); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glRectf(0.0, 0.0, WIDTH_M, 0.166*HEIGHT_M);

    // Draw black boundary.
    glColor3f(0.0, 0.0, 0.0); 
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glRectf(0.0, 0.0*HEIGHT_M, WIDTH_M, 0.166*HEIGHT_M);

    // Desenho do icone
    glColor3f(0.0, 0.0, 0.0);

    glLineWidth(2.0);
    glBegin(GL_LINES);
        glVertex3f(30.0, 30.0, 0.0);
        glVertex3f(70.0, 30.0, 0.0);

        glVertex3f(50.0, 45.0, 0.0);
        glVertex3f(50.0, 70.0, 0.0);
    glEnd();

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x5555); 
    glBegin(GL_LINES);
        glVertex3f(50.0, 30.0, 0.0);
        glVertex3f(50.0, 45.0, 0.0);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    
    glBegin(GL_QUADS);
        glVertex3f(50.0, 45.0, 0.0);
        glVertex3f(50.0, 50.0, 0.0);
        glVertex3f(55.0, 50.0, 0.0);
        glVertex3f(55.0, 45.0, 0.0);
    glEnd();    

    glLineWidth(1.0);
}

//====================================================================================//
// Objetivo da função: colocar todos as caixas de seleção em uma janela de Opções
//====================================================================================//
void drawSceneMenu(void) {
    // Escolha da janela
    glutSetWindow(menuOp);

    glClear(GL_COLOR_BUFFER_BIT);

    drawTwoPointsSelectionBox();
    drawLineSegmentSelectionBox();
    drawVectorPointSelectionBox();
    drawAnglesLineSelectionBox();
    drawParallelStraightsSelectionBox();
    drawOrthogonalStraightsSelectionBox();

    glFlush();
}

//====================================================================================//
// Objetivo da função: desenhar a opção escolhida de modo interativo
//====================================================================================//
void drawInterative(void) {
    float x1, x2, y1, y2;
    x1 = tempX;
    x2 = tempX2;
    y1 = tempY;
    y2 = tempY2;

    if (operation == TWO_POINTS) {
        TwoPoints obj;
        obj.drawTwoPointsInterativeClass(x1, y1, x2, y2);
    }

    if (operation == VECTOR_POINT) {
        VectorPoint obj;
        obj.drawVectorPointInterativeClass(pointVectorPoint[0], pointVectorPoint[1], x1, y1, x2, y2);
    }

    if (operation == LINE_SEGMENT) {
        LineSegment obj;
        obj.drawLineSegmentInterativeClass(x1, y1, x2, y2);
    }

    if (operation == ANGLES_LINE) {
        AnglesLine obj;
        obj.drawAnglesLineInterativeClass(x1, y1, x2, y2);
    }
  
    if (operation == PARALLEL_STRAIGHT) {
        ParallelStraight obj;
        obj.drawParallelStraightInterativeClass(x1, y1, x2, y2);
    }

    if (operation == ORTHOGONAL_STRAIGHT) {
        OrthogonalStraight obj;
        obj.drawOrthogonalStraightInterativeClass(x1, y1, x2, y2);
    }
}

//====================================================================================//
// Objetivo da função: desenhar a reta e sua equação que estam no vector
//====================================================================================//
void drawTwoPointsIterator(void) {
    
    twoPointsIterator = twoPoints.begin();
    while (twoPointsIterator != twoPoints.end() ) {
      twoPointsIterator->drawTwoPoints();
      twoPointsIterator->equationOverall();
	  twoPointsIterator++;
    }
}

//====================================================================================//
// Objetivo da função: desenhar a reta e o vetor que estam no vector
//====================================================================================//
void drawVectorPointIterator(void) {

    vectorPointIterator = vectorPoint.begin();
    while (vectorPointIterator != vectorPoint.end()) {
        vectorPointIterator->drawVectorPoint();
        vectorPointIterator++;
    } 
}

//====================================================================================//
// Objetivo da função: desenhar o segmento de reta e sua equação paramétrica que estam no
// vector.
//====================================================================================//
void drawLineSegmentIterator(void) {

    lineSegmentIterator = lineSegment.begin();
    while (lineSegmentIterator != lineSegment.end()) {
        lineSegmentIterator->drawLineSegment();
        lineSegmentIterator->equationParametric();
        lineSegmentIterator++;
    } 
}

//====================================================================================//
// Objetivo da função: desenhar as retas que estam no vetor e o ângulo entre elas
//====================================================================================//
void drawAnglesLineIterator(void) {
   
    anglesLineIterator = anglesLine.begin();
    while (anglesLineIterator != anglesLine.end()) {
        anglesLineIterator->drawAnglesLine();
        anglesLineIterator->calculeAngle();
        anglesLineIterator++;
    }
    
}

//====================================================================================//
// Objetivo da função: desenhar as retas paralelas que estam no vetor
//====================================================================================//
void drawParallelStraightIterator(void) {

    parallelStraightIterator = parallelStraight.begin();
    while (parallelStraightIterator != parallelStraight.end()) {
        parallelStraightIterator->drawParallelStraight();
        parallelStraightIterator++;
    } 
}

//====================================================================================//
// Objetivo da função: desenhar a reta e sua ortogonal que estam no vetor
//====================================================================================//
void drawOrthogonalStraightIterator(void) {
    
    orthogonalStraightIterator = orthogonalStraight.begin();
    while (orthogonalStraightIterator != orthogonalStraight.end()) {
        orthogonalStraightIterator->drawOrthogonalStraight();
        orthogonalStraightIterator++;
    }
}

//====================================================================================//
// Rotina de desenho para a janela principal
//====================================================================================//
void drawSceneDisplay(void) {
    // Escolha da janela
    glutSetWindow(display);
    glClear(GL_COLOR_BUFFER_BIT);
    
    drawGrid();

    if ( pointCount == 1 || pointCount == 2) {
        drawInterative();
    }

    drawTwoPointsIterator();
    drawVectorPointIterator();
    drawLineSegmentIterator();
    drawAnglesLineIterator();
    drawParallelStraightIterator();
    drawOrthogonalStraightIterator();

    glFlush();
}

//====================================================================================//
// Objetivo da função: selecionar a operação desejada
//====================================================================================//
void pickOperation(int y) {
    if ( y < 0.1666*HEIGHT_M ) 
        operation = ORTHOGONAL_STRAIGHT;
    else if ( y < 0.3333*HEIGHT_M )
        operation = PARALLEL_STRAIGHT;
    else if ( y < 0.5000*HEIGHT_M )
        operation = ANGLES_LINE;
    else if ( y < 0.6666*HEIGHT_M )
        operation = LINE_SEGMENT;
    else if ( y < 0.8333*HEIGHT_M )
        operation = VECTOR_POINT;
    else if ( y < HEIGHT_M)
        operation = TWO_POINTS;
}

//====================================================================================//
// Objetivo da função: controlar os clicks do mouse para a seleção no menu de opção
//====================================================================================//
void mouseControlMenu(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = HEIGHT_M - y; // correção para a coordenada y

        if ( x < 0 || x > WIDTH_M || y < 0 || y > HEIGHT_M) ;

        else {
            pickOperation(y);
            twoPoints.clear();
            vectorPoint.clear();
            lineSegment.clear();
            anglesLine.clear();
            parallelStraight.clear();
            orthogonalStraight.clear();

        }    
    }

    glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: Controlar os clicks do mouse para os desenhos, conforme o escolhido.
//====================================================================================//
void mouseControlDisplay(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = HEIGHT_M - y; // correção para a coordenada y

        if ( x < 0 || x > width_d || y < 0 || y > heigth_d) ;

        else {
            // Reta definida por dois pontos
            if (operation == TWO_POINTS) {
                twoPoints.clear(); //limpa o vetor
                if (pointCount == 0) {
                    tempX = x;
                    tempY = y;
                    tempX2 = tempX;
                    tempY2 = tempY;
                    pointCount++;
                } else {
                    twoPoints.push_back( TwoPoints(tempX, tempY, x, y));
                    pointCount = 0;
                }
            } 
            // Reta definida por ponto e vetor
            if (operation == VECTOR_POINT) {
                vectorPoint.clear(); //limpa o vetor
                if (pointCount == 0) {
                    //Pega o ponto
                    pointVectorPoint[0] = x;
                    pointVectorPoint[1] = y;
                    pointCount++;
                } else {
                    if (pointCount == 1) {
                        tempX = x;
                        tempY = y;
                        //Para o modo interativo
                        tempX2 = tempX;
                        tempY2 = tempY;
                        pointCount++;
                    } else {                    
                        vectorPoint.push_back( VectorPoint(pointVectorPoint[0], pointVectorPoint[1], tempX, tempY, x, y));
                        pointCount = 0;
                    }
                }
            }
            //Equação Paramétrica de um segmento de Reta
            if (operation == LINE_SEGMENT) {
                lineSegment.clear();
                if (pointCount == 0) {
                    tempX = x;
                    tempY = y;
                    //Para o modo interativo
                    tempX2 = tempX;
                    tempY2 = tempY;
                    pointCount++;
                } else {
                    lineSegment.push_back( LineSegment(tempX, tempY, x, y));
                    pointCount = 0;
                }
            } 

            //Ângulo entre retas
            if (operation == ANGLES_LINE) {
                someCounterY = 0;
                someCounterX = 0;
                if (straightCount == 2) {
                    anglesLine.clear();
                    straightCount = 0;
                } 
                
                if (pointCount == 0) {
                    tempX = x;
                    tempY = y;
                    //Para o modo interativo
                    tempX2 = tempX;
                    tempY2 = tempY;
                    pointCount++;
                } else {
                    anglesLine.push_back( AnglesLine(tempX, tempY, x, y) );
                    pointCount = 0;
                    straightCount++;
                }
            }

            // Retas Paralelas
            if (operation == PARALLEL_STRAIGHT) {
                parallelStraight.clear();
                if (pointCount == 0) {
                    tempX = x;
                    tempY = y;
                    //Para o modo interativo
                    tempX2 = tempX;
                    tempY2 = tempY;
                    pointCount++;
                } else {
                    parallelStraight.push_back( ParallelStraight(tempX, tempY, x, y) );
                    pointCount = 0;
                }
            }

            // Retas Ortogonais
            if (operation == ORTHOGONAL_STRAIGHT) {
                orthogonalStraight.clear();
                if (pointCount == 0) {
                    tempX = x;
                    tempY = y;
                    //Para o modo interativo
                    tempX2 = tempX;
                    tempY2 = tempY;
                    pointCount++;
                } else {
                    orthogonalStraight.push_back( OrthogonalStraight(tempX, tempY, x, y) );
                    pointCount = 0;
                }
            }
        }    
    } //GLUT_LEFT_BUTTON

    // trata do movimento do mouse para transladar o angulo entre duas retas
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {

        if (operation == ANGLES_LINE) {

            y = HEIGHT_M - y; // correção para a coordenada y

            if (movimentCounter == 0) {
                movimentX = x;
                movimentY = y;

                movimentTempX = movimentX;
                movimentTempY = movimentY;
                movimentCounter++;
            } else {
                counterX = x - movimentX;
                counterY = y - movimentY;
                movimentCounter = 0;
                someCounterX += counterX;
                someCounterY += counterY;
            }
        }
    }

    glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: pegar as coordenadas a partir do movimento do mouse
//====================================================================================//
void mouseMotion(int x, int y) {
    if (operation == VECTOR_POINT) {
        if (pointCount == 2) {
            tempX2 = x;
            tempY2 = heigth_d - y;
        }
    } else {
        if (pointCount == 1) {
            tempX2 = x;
            tempY2 = heigth_d - y;
        } 
    }

    if (movimentCounter == 1) {
        movimentTempX = x;
        movimentTempY = heigth_d - y;
    }
    glutPostRedisplay();
}

//====================================================================================//
// Objetivo da função: Inicializar a janela de Opções
//====================================================================================//
void setupMenu(void) {
    // Cor de Fundo.
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

//====================================================================================//
// Objetivo da função: Inicializar a janela de Desenho
//====================================================================================//
void setupDisplay(void) {
    // Cor de Fundo.
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

//====================================================================================//
// Objetivo da função: Reformular a rotina para a janela de Opções
//====================================================================================//
void resizeMenu(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//====================================================================================//
// Objetivo da função: Reformular a rotina para a janela de Desenho
//====================================================================================//
void resizeDisplay(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, (float)w, 0.0, (float)h, -1.0, 1.0);    

    width_d = w;
    heigth_d = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//====================================================================================//
// Objetivo da função: processar a entrada do teclado para a Janela de Opções
//====================================================================================//
void keyInputMenu(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);   
            break;
        default:
            break;
    }
}

//====================================================================================//
// Objetivo da função: processar a entrada do teclado para a Janela de Desenho
//====================================================================================//
void keyInputDisplay(unsigned char key, int x, int y) {
    switch(key) {
        case 27:
            exit(0);
            break;
        default:
            break;
    }
}

//====================================================================================//
// Objetivo da função: tratar as opcões do sub-menu -> 'Vizualizar Equacao'
//====================================================================================//
void menuEquation(int id) {
    if (id == 1) {
        modeExhibition = 1;   //lado esquerdo
    }
    if (id == 2) {
        modeExhibition = 0;   //lado direito
    }
}

//====================================================================================//
// Objetivo da função: tratar a opção de saida do menu.
//====================================================================================//
void rightMenu(int id)
{
    if (id==1) 
        exit(0);
}

//====================================================================================//
// Objetivo da função: criar o menu de opções, na tela de desenho
//====================================================================================//
void makeMenu() {
    int sub_menu_eq;

    sub_menu_eq = glutCreateMenu(menuEquation);
    glutAddMenuEntry("Lado Esquerdo", 1);
    glutAddMenuEntry("Lado Direito", 2);

    glutCreateMenu(rightMenu);
    glutAddSubMenu("Vizualizar", sub_menu_eq);

    glutAddMenuEntry("Sair", 1);  //para sair do programa
    
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
}

//====================================================================================//
// Objetivo da função: informar as possiveis interações com o usuário, no terminal
//====================================================================================//
void printInteraction(void) {
   cout << "Interacoes:" << endl;
   cout << "ESC -> para sair" << endl;
   cout << "Clique com o botao meio do mouse para mais opcoes" << endl;
   cout << "A opcao Vizualizar do menu, serve para mudar a vizualizacao do texto" 
        << endl
        << "No 'angulo entre duas retas' clique com o botão direito do mouse para habilitar o modo de arrastar a tela, clique novamente para desabilitar"
        << endl;
}

//====================================================================================//
//                      PRINCIPAL
//====================================================================================//
int main(int argc, char **argv) {

    printInteraction();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
   
    // Definicição da janela de Opções.
    glutInitWindowSize(WIDTH_M, HEIGHT_M); 
    glutInitWindowPosition(100, 100);

    // Cria a janela com o titulo e returna um ID.
    menuOp = glutCreateWindow("Menu"); 

    // Inicialização das funçoes da janela de Opções
    setupMenu();
    glutDisplayFunc(drawSceneMenu);
    glutReshapeFunc(resizeMenu);
    glutKeyboardFunc(keyInputMenu);
    glutMouseFunc(mouseControlMenu);

    // Definição da janela de Desenho
    glutInitWindowSize(WIDTH_D, HEIGHT_D); 
    glutInitWindowPosition(300, 100);

    // Cria a janela com o titulo e returna um ID.
    display = glutCreateWindow("Desenho");

    // Inicialização das funções da janela de Desenho
    setupDisplay();
    glutDisplayFunc(drawSceneDisplay);
    glutReshapeFunc(resizeDisplay);
    glutKeyboardFunc(keyInputDisplay);
    glutMouseFunc(mouseControlDisplay);
    glutPassiveMotionFunc(mouseMotion);
    makeMenu(); 

    glutMainLoop();
}

