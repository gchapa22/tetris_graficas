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

int j = rand() % COLUMNAS;

void reshape(int width, int height){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //gluPerspective(60.0f,1.0f, 0.01f, 100.0f);
    glOrtho(-10, 10, -10, 10, 0.1f, 20);
  glTranslatef(-3.0f, 0.0f, -15.0f);
  //glRotatef(40, 1.0f, 1.0f, 0.0f);
  glMatrixMode(GL_MODELVIEW);
}

void myTimer()
{
	for ( int i = FILAS-1; i >=0 ; i--)
    	{
        	if(matriz[i][j]==1 && matriz[i-1][j] == 0)
        	{
        		matriz[i][j]=0;
        		matriz[i-1][j]=1;
        	}
        	else
        	{
        	    j = rand() % COLUMNAS;
        		matriz[0][j]=1;
        	}
    	}
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

void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  eliminaFilasCompletas();
  glColor3f(1.0,0.0,0.5);
  for(int i=0; i<FILAS; i++){
    for(int j=0 ; j<COLUMNAS; j++){
        if(matriz[i][j]==1){
            glBegin(GL_QUADS);
                  glVertex3f(i, j, 0.0);
                  glVertex3f(i+1, j, 0.0);
                  glVertex3f(i+1, j+1, 0.0);
                  glVertex3f(i, j+1, 0.0);
            glEnd();
        }
    }
  }
  glutSwapBuffers();
}

void init(){
    glOrtho(0, COLUMNAS, 0, FILAS, 0,0);

}


int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("Tetris prueba");
  init();
  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}








