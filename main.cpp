#define GLUT_DISABLE_ATEXIT_HACK
#include <windows.h>
#include <iostream>
#include <math.h>
#include<GL/glut.h>
#include "quadtree.h"
#define KEY_ESC 27

using namespace std;

//Crear quad tree
    punto2d pu1={-200.0,200.0,0};
	punto2d pu2={200.0,-200.0,0};
	int nx,ny,cx,cy,dim=50;
    quadTree* qt;
    bool anticlic=0;

void OnMouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //convertir x,y
        nx=x-300;
        ny=300-y;
        //insertar un nuevo punto en el quadtree
        punto2d p={nx,ny,0};
        qt->insertar(p);
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN){
        cx=x-300;
        cy=300-y;
        anticlic=1;
    }
    else
        anticlic=0;
}

void OnMouseMotion(int x, int y)
{
     //opcional
	 //hacer algo x,z cuando se mueve el mouse
    cx=x-300;
    cy=300-y;
    if(anticlic)
        qt->busqueda(cx-dim/2,cx+dim/2,cy-dim/2,cy+dim/2);
}



void idle(){ // AGREGAR ESTA FUNCION
	glutPostRedisplay();
}

//funcion llamada a cada imagen
void glPaint(void) {

	//El fondo de la escena al color initial
	glClear(GL_COLOR_BUFFER_BIT); //CAMBIO
	glLoadIdentity();
	glOrtho(-300.0f,  300.0f,-300.0f, 300.0f, -1.0f, 1.0f);

	//dibujar quadTree (qt->draw())
    qt->draw();
    if(anticlic)
        qt->cuadro(cx-dim/2,cx+dim/2,cy-dim/2,cy+dim/2);
	//dibuja el gizmo
	//displayGizmo();

	//doble buffer, mantener esta instruccion al fin de la funcion
	glutSwapBuffers();
}

//
//inicializacion de OpenGL
//
void init_GL(void) {
	//Color del fondo de la escena
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //(R, G, B, transparencia) en este caso un fondo negro

	//modo projeccion
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}

//en el caso que la ventana cambie de tamaño
GLvoid window_redraw(GLsizei width, GLsizei height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();


}

GLvoid window_key(unsigned char key, int x, int y) {
	switch (key) {
	case KEY_ESC:
		exit(0);
		break;

	default:
		break;
	}

}
//
//el programa principal
//
int main(int argc, char** argv) {

	//Inicializacion de la GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600); //tamaño de la ventana
	glutInitWindowPosition(100, 100); //posicion de la ventana
	glutCreateWindow("TP2 bis OpenGL : Bresenham"); //titulo de la ventana

	init_GL(); //funcion de inicializacion de OpenGL

	glutDisplayFunc(glPaint);
	glutReshapeFunc(&window_redraw);
	// Callback del teclado
	glutKeyboardFunc(&window_key);
	glutMouseFunc(&OnMouseClick);
	glutMotionFunc(&OnMouseMotion);
	glutIdleFunc(&idle);
    qt=new quadTree;
    qt->p1=pu1;
    qt->p2=pu2;
    qt->leerArchivo("quad.txt");
	//qt = new quadTree();
	glutMainLoop(); //bucle de rendering
	//no escribir nada abajo de mainloop
	return 0;
}
