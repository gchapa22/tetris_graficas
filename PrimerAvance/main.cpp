/*
    Gerardo Chapa  -800249
    Norma Escobedo -805387

*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<stdio.h>
#define RENGLONES 15
#define COLUMNAS 8
#define WIDTH 300
#define HEIGHT 500

static int matriz[COLUMNAS][RENGLONES]  = {0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0,
                                        0,0,0,0,0,0,0,0};

int x = 1;
int y = RENGLONES-1;
bool colision = false;
bool lleno = false;
int puntos = 0;

int opcion = 0;
int pause = 0;

// //Clase cuadro-------------------------------
// class Cuadro()
// {
//   int x, y;
//   public:
//     Cuadro(int, int);

//    void setxy(int, int);
//    void setx(int);
//    void sety(int);

//    int getx();
//    int gety();

//    void baja();
//    void mueveIzq();
//    void mueveDer();
// }

// void Cuadro::Cuadro(int a, int b) {
//   x = a;
//   y = b;
// }

// void Cuadro::setxy(int a, int b) {
//   x = a;
//   y = b;
// }

// void Cuadro::setx(int a) {
//   x = a;
// }

// void Cuadro::sety(int b) {
//   y = b;
// }

// void Cuadro::getx() {
//   return x;
// }

// void Cuadro::gety(){
//   return y;
// }

// void Cuadro::baja() {
//   y++;
// }

// void Cuadro::mueveIzq() {
//   x--;
// }

// void Cuadro::mueveDer() {
//   x++;
// }
// //--------------------------------------------

// //Clase figura--------------------------------
// class Figura()
// {
//   Cuadro uno, dos, tres, cuatro;
//   int color[3];
//   public:
//     void baja();
// }

// void Figura::baja() {
//   uno.baja();
//   dos.baja();
//   tres.baja();
//   cuatro.baja();
// }
// //---------------------------------------------

void limpia()
{
  for(int x=0; x<COLUMNAS; x++){
        for(int y=0;y<RENGLONES; y++)
        {
          matriz[x][y] = 0;
        }
      }
}

void myTimer(int h)
{
  if(pause==0)
  {
    if(y<RENGLONES-1 || !colision)
    {
          if(lleno || colision){
              colision = false;
              lleno=false;
              x = rand() % COLUMNAS;
              y = RENGLONES-1;
              matriz[x][y]=1;
            }
          if(matriz[x][y]==1 && matriz[x][y-1] == 0)
          {
              if(y==0){
                  matriz[x][y]=1;
                  colision = true;
                  glutPostRedisplay();
                  glutTimerFunc(300,myTimer,1);
              }
              else{
                  matriz[x][y]=0;
                  matriz[x][y-1]=1;
                  y-=1;
                  glutPostRedisplay();
                  glutTimerFunc(300,myTimer,1);
              }
          }
          else if(matriz[x][y]==1 && matriz[x][y-1] == 1 )
          {
            matriz[x][y]=1;
            colision = true;
            glutPostRedisplay();
            glutTimerFunc(300,myTimer,1);
          }
    }
    else
    {
      limpia();
      std::ofstream log("scores.txt", std::ios_base::app | std::ios_base::out);
      log << puntos << std::endl;
      // std::stringstream ss;//create a stringstream
      // ss << puntos;//add number to the stream
      // char *mensaje = "Tu puntuacion es de: " + (char) ss.str(); 
      // int len = (int) strlen(mensaje);
      // for (int i = 0; i < len; i++) 
      // {
      //   glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mensaje[i]);
      // }
      glutPostRedisplay();
    }
  }
else if(pause==1)
{
  glutPostRedisplay();
}
  
}

bool renglonCompleto(int n){
    bool resultado = true;
    if(n>=0 && n<RENGLONES){
        for(int i=0; i<COLUMNAS; i++){
            if(matriz[i][n]!=1){
                resultado = false;
                break;
            }
        }
    }
    else{resultado=false;}
    return resultado;
}

void eliminaRenglon(int n){
    bool encontro = false;
    if(n>=0 && n<RENGLONES){
        for(int r=0; r<RENGLONES; r++){
                if(r==n){
                    encontro = true;
                }
                if(encontro){
                    if(r == (RENGLONES-1)){
                        for(int x=0; x<COLUMNAS ; x++){
                                matriz[x][r] = 0;
                        }
                    }
                    else{
                        for(int x=0; x<COLUMNAS ; x++){
                                matriz[x][r] = matriz[x][r+1];

                        }
                    }
                }
        }
    }
}

void eliminaRenglonesCompletos(){
    for(int i=0; i<RENGLONES; i++){
        if(renglonCompleto(i)){
            lleno = true;
            eliminaRenglon(i);
            puntos+=100;
        }
    }
}



void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,0.0,0.5);
  for(int columna=0; columna<COLUMNAS; columna++){
    for(int renglon=0 ; renglon<RENGLONES; renglon++){
        if(matriz[columna][renglon]==1){
            glBegin(GL_QUADS);
                  glVertex3f(columna, renglon, 1.0);
                  glVertex3f(columna+1, renglon, 1.0);
                  glVertex3f(columna+1, renglon+1, 1.0);
                  glVertex3f(columna, renglon+1, 1.0);
            glEnd();
        }
    }
  }
  if(colision){
    eliminaRenglonesCompletos();
  }
  glutSwapBuffers();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, COLUMNAS, 0, RENGLONES);
    glMatrixMode(GL_MODELVIEW);
    srand(time_t());
    matriz[x][y]=1;
}

void keyboard(unsigned char key, int xMouse, int yMouse){
  switch(key)
    {
    case 'd':
    case 'D':
      if(x<COLUMNAS-1 && matriz[x+1][y]==0){
        x++;
        matriz[x][y]=1;
        matriz[x-1][y]=0;
      }
      break;

    case 'a':
    case 'A':
      if(x>0 && matriz[x-1][y]==0){
        x--;
        matriz[x][y]=1;
        matriz[x+1][y]=0;
      }
      break;
    case 's':
    case 'S':
      if(y>0 && matriz[x][y-1]==0){
        y--;
        matriz[x][y]=1;
        matriz[x][y+1]=0;
      }
      break;

    case 27:   // escape
      exit(0);
      break;
    }
}

void procesaMenu(int val){
  switch(val)
  {
    case 10:
      exit(0);
    break;

    case 20:
      limpia();
      puntos=0;
      x = rand() % COLUMNAS;
      y = RENGLONES-1;
      matriz[x][y]=1;
    break;

    case 30:
    exit(0);
    break;

    case 40:
    exit(0);
    break;

    default:
    break;
  }
}

int addMenues(){
  int mainMenu;
  mainMenu = glutCreateMenu(procesaMenu);
  glutSetMenu(mainMenu);
  glutAddMenuEntry("Salir", 10);
  glutAddMenuEntry("Nuevo Juego", 20);
  glutAddMenuEntry("Scoreboard", 30);
  glutAddMenuEntry("Creditos", 40);
  glutSetMenu(mainMenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y){
  if(button == GLUT_RIGHT_BUTTON){
    if(state == GLUT_DOWN){
      pause = 1;
    }
  }
}

int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Tetris prueba");
  init();
  glutTimerFunc(200,myTimer,1);
  glutKeyboardFunc(keyboard);
  glutDisplayFunc(display);
  addMenues();
  glutMainLoop();
  return 0;
}
