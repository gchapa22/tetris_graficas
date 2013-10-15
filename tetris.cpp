#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdlib.h>

const int screenWidth = 800;
const int screenHeight = 800;

void bloque()
{
	glBegin(GL_QUADS);
	glVertex3f(-1.0f, -1.0f, 0.0f); 
	glVertex3f(-1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 0.0f); 
	glEnd();
}

// void figura()
// {

// }

void display()
{
	bloque();
}

void init(void)
{
    glClearColor(1.0,1.0,1.0,0.0);       // the background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // the drawing color is black
 	glPointSize(8.0);		           // a 'dot' is 2 by 2 pixels
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

int main(int argc, char*argv[])
{
	 glutInit(&argc, argv);          // initialize the toolkit
	 glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set the display mode
	 glutInitWindowSize(screenWidth, screenHeight); // set the window size
	 glutInitWindowPosition(0, 0); // set the window position on screen
	 glutCreateWindow("Tetris"); // open the screen window
	 glViewport(0, 0, screenWidth, screenHeight);
	 glutDisplayFunc(display);     // register the redraw function
	 init();
	 glutMainLoop(); 
}
