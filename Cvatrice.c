#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>
#include <math.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);
void CALLBACK rot_z_up(AUX_EVENTREC* event);
void CALLBACK rot_z_down(AUX_EVENTREC* event);


static GLfloat x = 0, y = 0, alfa = 0;
GLUquadricObj* qobj;

void myinit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void CALLBACK MutaStanga(void)
{
	x = x - 10;
}

void CALLBACK MutaDreapta(void)
{
	x = x + 10;
}

void CALLBACK MutaSus(void)
{
	y = y + 10;
}

void CALLBACK MutaJos(void)
{
	y = y - 10;
}

void CALLBACK rot_z_up(AUX_EVENTREC* event)
{
	alfa = alfa + 10;
}

void CALLBACK rot_z_down(AUX_EVENTREC* event)
{
	alfa = alfa - 10;
}

void CALLBACK display(void)
{


	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	qobj = gluNewQuadric();


	// TRACTOR START: doua discuri, cateva dreptunghiuri
	// roata dreapta
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 20, 0);
	glRotatef(alfa, 1, 1, 1);
	glColor3f(0, 0, 0);
	glutSolidTorus(10, 30, 80, 80);
	glPopMatrix();

	//roata stanga
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 40, y + 20, 0);
	glRotatef(alfa, 1, 1, 1);
	glColor3f(0, 0, 0);
	glutSolidTorus(7, 20, 50, 50);
	glPopMatrix();

	// corp principal (orizontal)
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 0, y + 60, 0);
	glRotatef(alfa, 1, 1, 1);
	glColor3f(0, 0, 0);
	auxWireBox(100, 40, 100);
	//gluCylinder(qobj, 100,100,34,4,44);
	glPopMatrix();

	// cabina (vertical)
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 80, 0);
	glRotatef(alfa, 1, 1, 1);
	glColor3f(0, 0, 0);
	auxWireBox(40, 50, 130);
	glPopMatrix();

	// esapament?
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 25, y + 90, 0);
	glRotatef(alfa, 1, 1, 1);
	glColor3f(0, 0, 0);
	auxWireBox(10, 20, 10);
	glPopMatrix();


	auxSwapBuffers();
}

/*void CALLBACK myReshape(GLsizei w, GLsizei h)
{
if (!h) return;			//transformare anizotropica, forma se modifica functie de forma(dimens) viewportului
glViewport(0, 0, w, h);	//daca w>h stabilim ca baza inaltime, si stab unit logica de dimens in fct de h(h/320, 320 lungime lat patrat)
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glOrtho (-160.0, 160.0, -160.0,
160.0, -10.0, 10.0);
glMatrixMode(GL_MODELVIEW);
}*/

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
	if (!h) return;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		glOrtho(-160.0, 160.0, 160.0 * (GLfloat)h / (GLfloat)w,
			-160.0 * (GLfloat)h / (GLfloat)w, -100.0, 100.0);
	else
		glOrtho(-160.0 * (GLfloat)w / (GLfloat)h,
			160.0 * (GLfloat)w / (GLfloat)h, -160.0, 160.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB);
	auxInitPosition(0, 0, 1000, 800);
	auxInitWindow("Un patrat care se translateaza pe axa x");
	myinit();

	auxKeyFunc(AUX_LEFT, MutaStanga);
	auxKeyFunc(AUX_RIGHT, MutaDreapta);
	auxKeyFunc(AUX_UP, MutaSus);
	auxKeyFunc(AUX_DOWN, MutaJos);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
	auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);


	auxReshapeFunc(myReshape);
	auxMainLoop(display);
	return(0);
}