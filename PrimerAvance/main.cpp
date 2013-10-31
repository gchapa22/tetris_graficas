/*
    Gerardo Chapa  -800249
    Norma Escobedo -805387

*/

#include<windows.h>
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

int x = 0;
int y = RENGLONES-1;
bool colision = false;
bool lleno = false;



void myTimer(int h)
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
      if(x<COLUMNAS-1){
        x++;
        matriz[x][y]=1;
        matriz[x-1][y]=0;
      }
      break;

    case 'a':
    case 'A':
      if(x>0){
        x--;
        matriz[x][y]=1;
        matriz[x+1][y]=0;
      }
      break;

    case 27:   // escape
      exit(0);
      break;
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
  glutMainLoop();
  return 0;
}
