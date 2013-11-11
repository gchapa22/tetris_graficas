/*
 Gerardo Chapa  -800249
 Norma Escobedo -805387

 */
#include <windows.h>
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
#define WIDTH 500
#define HEIGHT 700

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

GLfloat diffuseMaterial[4] = { 1.0, 0.0, 0.5, 1.0 };

int pos[4][2] = {0,0,0,0,
                  0,0,0,0};

int checaAbajo[3] = {0,0,0};
int checaArriba[3] = {0,0,0};
int checaIzq[4] = {0,0,0,0};
int checaDer[4] = {0,0,0,0};

int figura = 0;
int figuraSiguiente = 0;

int entraTimer = 0;
int velocidad = 500;

bool colision = false;
bool lleno = false;
int puntos = 0, vuelta=0;

int opcion = 0;
int pause = 0;

void figuraO(int a, int b)
{
  checaAbajo[0] = 2;
  checaAbajo[1] = 3;
  checaAbajo[2] = 2;

  checaArriba[0] = 0;
  checaArriba[1] = 1;
  checaArriba[2] = 0;

  checaIzq[0] = 0;
  checaIzq[1] = 2;
  checaIzq[2] = 0;
  checaIzq[3] = 2;

  checaDer[0] = 1;
  checaDer[1] = 3;
  checaDer[2] = 1;
  checaDer[3] = 3;

  pos[0][0] = a;
  pos[0][1] = b;

  pos[1][0] = a+1;
  pos[1][1] = b;

  pos[2][0] = a;
  pos[2][1] = b-1;

  pos[3][0] = a+1;
  pos[3][1] = b-1;

  matriz[a][b] = 1;
  matriz[a+1][b] = 1;
  matriz[a][b-1] = 1;
  matriz[a+1][b-1] = 1;
}

void figuraI(int a, int b)
{
  checaAbajo[0] = 3;
  checaAbajo[1] = 3;
  checaAbajo[2] = 3;

  checaArriba[0] = 0;
  checaArriba[1] = 0;
  checaArriba[2] = 0;

  checaIzq[0] = 0;
  checaIzq[1] = 1;
  checaIzq[2] = 2;
  checaIzq[3] = 3;

  checaDer[0] = 0;
  checaDer[1] = 1;
  checaDer[2] = 2;
  checaDer[3] = 3;

  pos[0][0] = a;
  pos[0][1] = b;

  pos[1][0] = a;
  pos[1][1] = b-1;

  pos[2][0] = a;
  pos[2][1] = b-2;

  pos[3][0] = a;
  pos[3][1] = b-3;

  matriz[a][b] = 2;
  matriz[a][b-1] = 2;
  matriz[a][b-2] = 2;
  matriz[a][b-3] = 2;
}

void figuraL(int a, int b)
{
  checaAbajo[0] = 3;
  checaAbajo[1] = 3;
  checaAbajo[2] = 2;

  checaArriba[0] = 0;
  checaArriba[1] = 3;
  checaArriba[2] = 0;

  checaIzq[0] = 0;
  checaIzq[1] = 1;
  checaIzq[2] = 2;
  checaIzq[3] = 0;

  checaDer[0] = 0;
  checaDer[1] = 1;
  checaDer[2] = 3;
  checaDer[3] = 3;

  pos[0][0] = a;
  pos[0][1] = b;

  pos[1][0] = a;
  pos[1][1] = b-1;

  pos[2][0] = a;
  pos[2][1] = b-2;

  pos[3][0] = a+1;
  pos[3][1] = b-2;

  matriz[a][b] = 3;
  matriz[a][b-1] = 3;
  matriz[a][b-2] = 3;
  matriz[a+1][b-2] = 3;
}

void figuraJ(int a, int b)
{
  checaAbajo[0] = 3;
  checaAbajo[1] = 3;
  checaAbajo[2] = 2;

  checaArriba[0] = 0;
  checaArriba[1] = 3;
  checaArriba[2] = 0;

  checaIzq[0] = 0;
  checaIzq[1] = 1;
  checaIzq[2] = 3;
  checaIzq[3] = 0;

  checaDer[0] = 0;
  checaDer[1] = 1;
  checaDer[2] = 2;
  checaDer[3] = 0;

  pos[0][0] = a;
  pos[0][1] = b;

  pos[1][0] = a;
  pos[1][1] = b-1;

  pos[2][0] = a;
  pos[2][1] = b-2;

  pos[3][0] = a-1;
  pos[3][1] = b-2;

  matriz[a][b] = 4;
  matriz[a][b-1] = 4;
  matriz[a][b-2] = 4;
  matriz[a-1][b-2] = 4;
}

void figuraS(int a, int b)
{
  checaAbajo[0] = 3;
  checaAbajo[1] = 2;
  checaAbajo[2] = 1;

  checaArriba[0] = 0;
  checaArriba[1] = 1;
  checaArriba[2] = 3;

  checaIzq[0] = 0;
  checaIzq[1] = 0;
  checaIzq[2] = 3;
  checaIzq[3] = 3;

  checaDer[0] = 1;
  checaDer[1] = 1;
  checaDer[2] = 2;
  checaDer[3] = 2;

  pos[0][0] = a;
  pos[0][1] = b;

  pos[1][0] = a+1;
  pos[1][1] = b;

  pos[2][0] = a;
  pos[2][1] = b-1;

  pos[3][0] = a-1;
  pos[3][1] = b-1;

  matriz[a][b] = 5;
  matriz[a+1][b] = 5;
  matriz[a][b-1] = 5;
  matriz[a-1][b-1] = 5;
}

void figuraT(int a, int b)
{
  checaAbajo[0] = 3;
  checaAbajo[1] = 2;
  checaAbajo[2] = 0;

  checaArriba[0] = 0;
  checaArriba[1] = 1;
  checaArriba[2] = 3;

  checaIzq[0] = 0;
  checaIzq[1] = 0;
  checaIzq[2] = 3;
  checaIzq[3] = 3;

  checaDer[0] = 2;
  checaDer[1] = 2;
  checaDer[2] = 3;
  checaDer[3] = 3;

  pos[0][0] = a;
  pos[0][1] = b;

  pos[1][0] = a+1;
  pos[1][1] = b;

  pos[2][0] = a+2;
  pos[2][1] = b;

  pos[3][0] = a+1;
  pos[3][1] = b-1;

  matriz[a][b] = 6;
  matriz[a+1][b] = 6;
  matriz[a+2][b] = 6;
  matriz[a+1][b-1] = 6;
}

void nuevafigura()
{
  pos[0][0] = rand() % (COLUMNAS-3);
  pos[0][0]++;
  pos[0][1] = RENGLONES-1;
  if(entraTimer<=1)
  {
    figura = rand() % 6;
  }
  else
  {
    figura = figuraSiguiente;
  }
  figura=0;
  figuraSiguiente = rand() % 6;

  printf("Figura------------");
  switch(figura)
  {
    case 0:
    printf("1\n");
    figuraO(pos[0][0],pos[0][1]);
    break;
    case 1:
    printf("2\n");
    figuraI(pos[0][0],pos[0][1]);
    break;
    case 2:
    printf("3\n");
    figuraL(pos[0][0],pos[0][1]);
    break;
    case 3:
    printf("4\n");
    figuraJ(pos[0][0],pos[0][1]);
    break;
    case 4:
    printf("5\n");
    figuraS(pos[0][0],pos[0][1]);
    break;
    case 5:
    printf("6\n");
    figuraT(pos[0][0],pos[0][1]);
    break;
    default:
    printf("Ninguno\n");
    break;
  }
}

void limpia()
{
    for(int x=0; x<COLUMNAS; x++){
        for(int y=0;y<RENGLONES; y++)
        {
            matriz[x][y] = 0;
        }
    }
}

void imprime()
{
  for(int y=0; y<RENGLONES; y++){
        for(int x=0;x<COLUMNAS; x++)
        {
          printf("%d, ",matriz[x][y]);
        }
        printf("\n");
      }
}

void imprimePos()
{
  for(int y=0; y<2; y++){
        for(int x=0;x<4; x++)
        {
          printf("%d, ",pos[x][y]);
        }
        printf("\n");
      }
}

void imprimePosMatMenos()
{
  printf("Pos Mat\n");
  printf("%d\n", matriz[pos[0][0]][pos[0][1]-1]);
  printf("%d\n", matriz[pos[1][0]][pos[1][1]-1]);
  printf("%d\n", matriz[pos[2][0]][pos[2][1]-1]);
  printf("%d\n", matriz[pos[3][0]][pos[3][1]-1]);
  printf("////////////////////////////////\n");
}

void imprimeChecaAbajoMenos()
{
  printf("Checa Abajo------------------\n");
  printf("%d\n", pos[checaAbajo[0]][1]);
  printf("%d\n", pos[checaAbajo[1]][1]);
  printf("%d\n", pos[checaAbajo[2]][1]);
  printf("Checa Menos------------------\n");
  printf("%d\n", pos[checaAbajo[0]][1]-1);
  printf("%d\n", pos[checaAbajo[1]][1]-1);
  printf("%d\n", pos[checaAbajo[2]][1]-1);
}

void eliminaRenglonesCompletos(){
    bool lleno=true;
      for(int x=0; x<RENGLONES; x++){
        lleno=true;
        for(int y=0;y<COLUMNAS; y++)
        {
          if(matriz[y][x]==0)
            lleno = false;
        }
        if(lleno)
        {
          puntos+=100;
          for(int y=0;y<COLUMNAS; y++)
          {
            matriz[y][x]= matriz[y][x+1];
            matriz[y][x+1]=0;
          }
          lleno = true;
          velocidad/=1.2;
        }
      }
}

void myTimer(int h)
{
    entraTimer+=1;
    imprime();
    printf("------------------------------------\n");
    if(pause==0)
    {
        if((pos[checaArriba[0]][1]<RENGLONES-1 &&
          pos[checaArriba[1]][1]<RENGLONES-1 &&
          pos[checaArriba[2]][1]<RENGLONES-1) ||
          !colision)
        {
            if(lleno || colision){
                colision = false;
                lleno=false;
                eliminaRenglonesCompletos();
                nuevafigura();
            }
            if(matriz[pos[0][0]][pos[0][1]]>0 &&
            matriz[pos[1][0]][pos[1][1]]>0 &&
            matriz[pos[2][0]][pos[2][1]]>0 &&
            matriz[pos[3][0]][pos[3][1]]>0 &&
            matriz[pos[checaAbajo[0]][0]][pos[checaAbajo[0]][1]-1]==0 &&
            matriz[pos[checaAbajo[1]][0]][pos[checaAbajo[1]][1]-1]==0 &&
            matriz[pos[checaAbajo[2]][0]][pos[checaAbajo[2]][1]-1]==0)
            {
                if(pos[checaAbajo[0]][1]==0)
                {
                    matriz[pos[0][0]][pos[0][1]] = figura+1;
                  matriz[pos[1][0]][pos[1][1]] = figura+1;
                  matriz[pos[2][0]][pos[2][1]] = figura+1;
                  matriz[pos[3][0]][pos[3][1]] = figura+1;
                  colision = true;
                  glutPostRedisplay();
                  glutTimerFunc(velocidad,myTimer,1);
                }
                else{
                    matriz[pos[0][0]][pos[0][1]] = 0;
                  matriz[pos[1][0]][pos[1][1]] = 0;
                  matriz[pos[2][0]][pos[2][1]] = 0;
                  matriz[pos[3][0]][pos[3][1]] = 0;
                  matriz[pos[0][0]][pos[0][1]-1] = figura+1;
                  matriz[pos[1][0]][pos[1][1]-1] = figura+1;
                  matriz[pos[2][0]][pos[2][1]-1] = figura+1;
                  matriz[pos[3][0]][pos[3][1]-1] = figura+1;
                  pos[0][1]-=1;
                  pos[1][1]-=1;
                  pos[2][1]-=1;
                  pos[3][1]-=1;
                  glutPostRedisplay();
                  glutTimerFunc(velocidad,myTimer,1);
                }
            }
             else if(matriz[pos[0][0]][pos[0][1]] > 0 &&
                  matriz[pos[1][0]][pos[1][1]] > 0 &&
                  matriz[pos[2][0]][pos[2][1]] > 0 &&
                  matriz[pos[3][0]][pos[3][1]] > 0 &&
                  (matriz[pos[checaAbajo[0]][0]][pos[checaAbajo[0]][1]-1] > 0 ||
                  matriz[pos[checaAbajo[1]][0]][pos[checaAbajo[1]][1]-1] > 0 ||
                  matriz[pos[checaAbajo[3]][0]][pos[checaAbajo[3]][1]-1] > 0))
            {
                colision = true;
                glutPostRedisplay();
                glutTimerFunc(300,myTimer,1);
            }
        }
        else
        {
            printf("perdiste : %d puntos\n",puntos);
              limpia();
              std::ofstream log("scores.txt", std::ios_base::app | std::ios_base::out);
              log << puntos << std::endl;
              glutPostRedisplay();
        }
    }
    else if(pause==1)
    {
        printf("pause\n");
        glutPostRedisplay();
        glutTimerFunc(velocidad,myTimer,1);
    }

}


void display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    switch(vuelta%4){
        case 0:
            glRotated(0,0,0,1);
            break;
        case 1:
            glTranslated(RENGLONES/2 + COLUMNAS/2, (RENGLONES/2 - COLUMNAS/2),0);
            glRotated(90,0,0,1);
            break;
        case 2:
            glTranslated(COLUMNAS, RENGLONES,0);
            glRotated(180,0,0,1);
            break;
        case 3:
            glTranslated((-RENGLONES/2 + COLUMNAS/2 -1),(RENGLONES/2 + COLUMNAS/2),0);
            glRotated(-90,0,0,1);
            break;
    }

    glColor3f(1.0,0.0,0.5);
    glBegin(GL_LINES);
    glVertex2i(0-0.5,0-.5);
    glVertex2i(0-0.5,RENGLONES+.5);
    glVertex2i(COLUMNAS+0.5, 0);
    glVertex2i(COLUMNAS+0.5, RENGLONES);
    glVertex2i(0, RENGLONES);
    glVertex2i(COLUMNAS, RENGLONES);
    glVertex2i(0,0);
    glVertex2i(COLUMNAS,0);
    glEnd();

    glPushMatrix();
    glRotated(10,0,1,0);
    glRotated(10,1,0,0);
    for(int columna=0; columna<COLUMNAS; columna++){
        /*glBegin(GL_LINES);
        glVertex3i(columna, 0, 0);
        glVertex3i(columna, RENGLONES, 0);
        glEnd();*/
        for(int renglon=0 ; renglon<RENGLONES; renglon++){
            /*glBegin(GL_LINES);
            glVertex3i(0, renglon, 0);
            glVertex3i(COLUMNAS, renglon, 0);
            glEnd();*/
            if(matriz[columna][renglon]==1){
                glPushMatrix();
                glTranslated(columna + 0.5, renglon+0.5, 0);
                glutSolidCube(1);
                glPopMatrix();
            }
        }
    }
    glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}

void init(){
    //srand(time_t());
    glEnable(GL_DEPTH_TEST);
    nuevafigura();
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    glShadeModel (GL_FLAT);  //Flat para que se vea mejor
    glEnable(GL_DEPTH_TEST);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 125.0);

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glClearColor(1, 1, 1, 1);
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
    glColor4fv(diffuseMaterial);
}

void mueve(int n){
    //Izquierda
    if(n==0){
            if(pos[checaIzq[0]][0]>0 &&
            pos[checaIzq[1]][0]>0 &&
            pos[checaIzq[2]][0]>0 &&
            pos[checaIzq[3]][0]>0 &&
            matriz[pos[checaIzq[0]][0]-1][pos[checaIzq[0]][1]]==0 &&
            matriz[pos[checaIzq[1]][0]-1][pos[checaIzq[1]][1]]==0 &&
            matriz[pos[checaIzq[2]][0]-1][pos[checaIzq[2]][1]]==0 &&
            matriz[pos[checaIzq[3]][0]-1][pos[checaIzq[3]][1]]==0)
            {
                matriz[pos[0][0]][pos[0][1]]=0;
                matriz[pos[1][0]][pos[1][1]]=0;
                matriz[pos[2][0]][pos[2][1]]=0;
                matriz[pos[3][0]][pos[3][1]]=0;

                pos[0][0]--;
                pos[1][0]--;
                pos[2][0]--;
                pos[3][0]--;

                matriz[pos[0][0]][pos[0][1]]=figura+1;
                matriz[pos[1][0]][pos[1][1]]=figura+1;
                matriz[pos[2][0]][pos[2][1]]=figura+1;
                matriz[pos[3][0]][pos[3][1]]=figura+1;
            }
    }
    //Derecha
    else if(n==1){
        if(pos[checaDer[0]][0]<COLUMNAS-1 &&
            pos[checaDer[1]][0]<COLUMNAS-1 &&
            pos[checaDer[2]][0]<COLUMNAS-1 &&
            pos[checaDer[3]][0]<COLUMNAS-1 &&
            matriz[pos[checaDer[0]][0]+1][pos[checaDer[0]][1]]==0 &&
            matriz[pos[checaDer[1]][0]+1][pos[checaDer[1]][1]]==0 &&
            matriz[pos[checaDer[2]][0]+1][pos[checaDer[2]][1]]==0 &&
            matriz[pos[checaDer[3]][0]+1][pos[checaDer[3]][1]]==0)
            {
                matriz[pos[0][0]][pos[0][1]]=0;
                matriz[pos[1][0]][pos[1][1]]=0;
                matriz[pos[2][0]][pos[2][1]]=0;
                matriz[pos[3][0]][pos[3][1]]=0;

                pos[0][0]++;
                pos[1][0]++;
                pos[2][0]++;
                pos[3][0]++;

                matriz[pos[0][0]][pos[0][1]]=figura+1;
                matriz[pos[1][0]][pos[1][1]]=figura+1;
                matriz[pos[2][0]][pos[2][1]]=figura+1;
                matriz[pos[3][0]][pos[3][1]]=figura+1;
              }
    }
    //Abajo
    else if(n==2){
        if(pos[0][1]>0 &&
            pos[1][1]>0 &&
            pos[2][1]>0 &&
            pos[3][1]>0 &&
            matriz[pos[checaAbajo[0]][0]][pos[checaAbajo[0]][1]-1]==0 &&
            matriz[pos[checaAbajo[1]][0]][pos[checaAbajo[1]][1]-1]==0 &&
            matriz[pos[checaAbajo[2]][0]][pos[checaAbajo[2]][1]-1]==0 )
            {
                matriz[pos[0][0]][pos[0][1]]=0;
                matriz[pos[1][0]][pos[1][1]]=0;
                matriz[pos[2][0]][pos[2][1]]=0;
                matriz[pos[3][0]][pos[3][1]]=0;

                pos[0][1]--;
                pos[1][1]--;
                pos[2][1]--;
                pos[3][1]--;

                matriz[pos[0][0]][pos[0][1]]=figura+1;
                matriz[pos[1][0]][pos[1][1]]=figura+1;
                matriz[pos[2][0]][pos[2][1]]=figura+1;
                matriz[pos[3][0]][pos[3][1]]=figura+1;
              }
    }
}

void special(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_LEFT:
           switch (vuelta%4){
               case 0:
                   mueve(0);
                   break;
               case 1:
                   vuelta++;
                   break;
               case 2:
                   mueve(1);
                   break;
               case 3:
                   mueve(2);
                   break;
           }
            break;
        case GLUT_KEY_RIGHT:
            switch (vuelta%4){
               case 0:
                   mueve(1);
                   break;
               case 1:
                   mueve(2);
                   break;
               case 2:
                   mueve(0);
                   break;
               case 3:
                   vuelta++;
                   break;
           }
            break;
        case GLUT_KEY_UP:
            switch (vuelta%4){
               case 0:
                   vuelta++;
                   break;
               case 1:
                   mueve(1);
                   break;
               case 2:
                   mueve(2);
                   break;
               case 3:
                   mueve(0);
                   break;
           }
            break;
        case GLUT_KEY_DOWN:
			switch (vuelta%4){
               case 0:
                   mueve(2);
                   break;
               case 1:
                   mueve(0);
                   break;
               case 2:
                   vuelta++;
                   break;
               case 3:
                   mueve(1);
                   break;
           }
            break;
    }
}
void keyboard(unsigned char key, int xMouse, int yMouse){
    switch(key)
    {
        case 'd':
    case 'D':
      if(pos[checaDer[0]][0]<COLUMNAS-1 &&
        pos[checaDer[1]][0]<COLUMNAS-1 &&
        pos[checaDer[2]][0]<COLUMNAS-1 &&
        pos[checaDer[3]][0]<COLUMNAS-1 &&
        matriz[pos[checaDer[0]][0]+1][pos[checaDer[0]][1]]==0 &&
        matriz[pos[checaDer[1]][0]+1][pos[checaDer[1]][1]]==0 &&
        matriz[pos[checaDer[2]][0]+1][pos[checaDer[2]][1]]==0 &&
        matriz[pos[checaDer[3]][0]+1][pos[checaDer[3]][1]]==0){

        matriz[pos[0][0]][pos[0][1]]=0;
        matriz[pos[1][0]][pos[1][1]]=0;
        matriz[pos[2][0]][pos[2][1]]=0;
        matriz[pos[3][0]][pos[3][1]]=0;

        pos[0][0]++;
        pos[1][0]++;
        pos[2][0]++;
        pos[3][0]++;

        matriz[pos[0][0]][pos[0][1]]=figura+1;
        matriz[pos[1][0]][pos[1][1]]=figura+1;
        matriz[pos[2][0]][pos[2][1]]=figura+1;
        matriz[pos[3][0]][pos[3][1]]=figura+1;
      }
      break;

    case 'a':
    case 'A':
      if(pos[checaIzq[0]][0]>0 &&
        pos[checaIzq[1]][0]>0 &&
        pos[checaIzq[2]][0]>0 &&
        pos[checaIzq[3]][0]>0 &&
        matriz[pos[checaIzq[0]][0]-1][pos[checaIzq[0]][1]]==0 &&
        matriz[pos[checaIzq[1]][0]-1][pos[checaIzq[1]][1]]==0 &&
        matriz[pos[checaIzq[2]][0]-1][pos[checaIzq[2]][1]]==0 &&
        matriz[pos[checaIzq[3]][0]-1][pos[checaIzq[3]][1]]==0){

        matriz[pos[0][0]][pos[0][1]]=0;
        matriz[pos[1][0]][pos[1][1]]=0;
        matriz[pos[2][0]][pos[2][1]]=0;
        matriz[pos[3][0]][pos[3][1]]=0;

        pos[0][0]--;
        pos[1][0]--;
        pos[2][0]--;
        pos[3][0]--;

        matriz[pos[0][0]][pos[0][1]]=figura+1;
        matriz[pos[1][0]][pos[1][1]]=figura+1;
        matriz[pos[2][0]][pos[2][1]]=figura+1;
        matriz[pos[3][0]][pos[3][1]]=figura+1;
      }
      break;
    case 's':
    case 'S':
      if(pos[0][1]>0 &&
        pos[1][1]>0 &&
        pos[2][1]>0 &&
        pos[3][1]>0 &&
        matriz[pos[checaAbajo[0]][0]][pos[checaAbajo[0]][1]-1]==0 &&
        matriz[pos[checaAbajo[1]][0]][pos[checaAbajo[1]][1]-1]==0 &&
        matriz[pos[checaAbajo[2]][0]][pos[checaAbajo[2]][1]-1]==0 ){

        matriz[pos[0][0]][pos[0][1]]=0;
        matriz[pos[1][0]][pos[1][1]]=0;
        matriz[pos[2][0]][pos[2][1]]=0;
        matriz[pos[3][0]][pos[3][1]]=0;

        pos[0][1]--;
        pos[1][1]--;
        pos[2][1]--;
        pos[3][1]--;

        matriz[pos[0][0]][pos[0][1]]=figura+1;
        matriz[pos[1][0]][pos[1][1]]=figura+1;
        matriz[pos[2][0]][pos[2][1]]=figura+1;
        matriz[pos[3][0]][pos[3][1]]=figura+1;
      }
      break;
        case 'r':
        case 'R':
            vuelta++;
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
            nuevafigura();
            colision = false;
            lleno=false;
            glutTimerFunc(300,myTimer,1);
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

void addMenues(){
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

void myReshape(int ancho, int alto)
{

    glViewport(0, 0, ancho, alto); /* Ventana */
    glMatrixMode(GL_PROJECTION); /* Sistema de coordenadas */
    glLoadIdentity();
    glOrtho(-5, COLUMNAS+5, -10, RENGLONES+10,-10,10); /* izq, der, abajo, arriba, cerca, lejos */
  //  glFrustum(0, COLUMNAS, 0, RENGLONES, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(-2,0,0, 1,-1,-1,0, 1, 0);
   // gluLookAt(COLUMNAS/2.0,RENGLONES/2.0,-5, 2,RENGLONES/2,-1,0, 1, 0);
}



int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE |GLUT_DEPTH| GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Tetris prueba");
    init();
    glutReshapeFunc(myReshape);
    glutTimerFunc(200,myTimer,1);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    addMenues();
    glutMainLoop();
    return 0;
}
