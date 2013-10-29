/*
    Gerardo Chapa  -800249
    Norma Escobedo -805387

*/

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include<stdio.h>
#define FILAS 15
#define COLUMNAS 8
#define WIDTH 300
#define HEIGHT 500

static int matriz[FILAS][COLUMNAS]  = {0,0,0,0,0,0,0,0,
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

int i = rand() % COLUMNAS;
int j = FILAS-1;


void myTimer(int h)
{
    //matriz[4][5]=1;
      if(matriz[i][j]==1 && matriz[i][j-1] == 0)
        {
          matriz[i][j]=0;
          matriz[i][j-1]=1;
          j-=1;
        }
        else if(matriz[i][j]==1 && matriz[i][j-1] == 1)
        {
          i = rand() % COLUMNAS;
          matriz[i][j]=1;
          j= FILAS-1;
        }
      if(j==0){
            j = FILAS-1;
            i = rand() % COLUMNAS;
            matriz[i][j]=1;
      }
      //glutTimerFunc(200,myTimer,1);
      glutPostRedisplay();
}

bool filaCompleta(int n){
    bool resultado = true;
    if(n>=0 && n<FILAS){
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

void eliminaFila(int n){
    bool encontro = false;
    if(n>=0 && n<FILAS){
        for(int i=0; i<FILAS; i++){
                if(i==n){
                    encontro = true;
                }
                if(encontro){
                    if(i == (FILAS-1)){
                        for(int j=0; j<COLUMNAS ; j++){
                                matriz[i][j] = 0;
                        }
                    }
                    else{
                        for(int j=0; j<COLUMNAS ; j++){
                                matriz[i][j] = matriz[i+1][j];
                        }
                    }
                }
            }
    }
}

void eliminaFilasCompletas(){
    for(int i=0; i<FILAS; i++){
        if(filaCompleta(i))
            eliminaFila(i);
    }
}

void cuadro(int i, int j)
{
  glBegin(GL_QUADS);
    glVertex3f(i, j, 1.0);
    glVertex3f(i+1, j, 1.0);
    glVertex3f(i+1, j+1, 1.0);
    glVertex3f(i, j+1, 1.0);
  glEnd();
}

void figuraI(int i, int j)
{
    cuadro(i,j);
    cuadro(i,j+1);
    cuadro(i,j+2);
    cuadro(i,j+3);
}

void figuraO(int i, int j)
{
    cuadro(i,j);
    cuadro(i,j+1);
    cuadro(i+1,j);
    cuadro(i+1,j+1);
}

void figuraS(int i, int j)
{
    cuadro(i,j);
    cuadro(i+1,j);
    cuadro(i+1,j+1);
    cuadro(i+1,j+2);
}

void figuraZ(int i, int j)
{
    cuadro(i,j);
    cuadro(i,j+1);
    cuadro(i-1,j+1);
    cuadro(i+1,j+1);
}


void figuraT(int i, int j)
{
    cuadro(i,j);
    cuadro(i,j+1);
    cuadro(i,j+2);
    cuadro(i+1,j+1);
}


void figuraL(int i, int j)
{
    cuadro(i,j);
    cuadro(i+1,j);
    cuadro(i+1,j+1);
    cuadro(i+1,j+2);
}


void figuraJ(int i, int j)
{
    cuadro(i,j);
    cuadro(i,j+1);
    cuadro(i+1,j+1);
    cuadro(i+2,j+1);
}



void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3f(1.0,0.0,0.5);
  for(int i=0; i<COLUMNAS; i++){
    for(int j=0 ; j<FILAS; j++){
        if(matriz[i][j]==1){
                printf("La columna %d El renglon %d \n",i, j);
            cuadro(i,j);
        }
    }
  }
  //eliminaFilasCompletas();
  glutSwapBuffers();
}

void init(){
    glOrtho(0, COLUMNAS, 0, FILAS, -1,1);
}


int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Tetris prueba");
  init();
  glutTimerFunc(200,myTimer,1);
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
