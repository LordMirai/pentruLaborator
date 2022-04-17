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
GLUnurbsObj* theNurb;

void myinit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glShadeModel(GL_FLAT);
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10.0);
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
	glRotatef(alfa, 0, 1, 0);

	// TRACTOR START: doua discuri, cateva dreptunghiuri

	// corp principal (orizontal (dreapta))
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 10, y + 80, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.6, 0, 0);
	gluCylinder(qobj, 20, 20, 40, 4, 100);
	glPopMatrix();

	// corp principal (orizontal (stanga))
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x -30, y + 80, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.6, 0, 0);
	gluCylinder(qobj, 20, 20, 40, 4, 100);
	glPopMatrix();	

	// cabina (vertical)
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 110, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0.5);
	gluCylinder(qobj, 20, 20, 70, 4, 250);
	glPopMatrix();

	// esapament
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 30, y + 98, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.3, 0.05, 0);
	gluCylinder(qobj, 5, 5, 18, 4, 60);
	glPopMatrix();

	// roata spate-dreapta
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 28, 26);
	glColor3f(0.3,0, 0.4);
	glutSolidTorus(10, 30, 80, 80);
	glPopMatrix();

	// roata spate-stanga
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 28, -26);
	glColor3f(0.2, 0, 0.3);
	glutSolidTorus(10, 30, 80, 80);
	glPopMatrix();

	//roata fata-stanga
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 40, y + 20, -20);
	glColor3f(0, 0.25, 0.2);
	glutSolidTorus(7, 20, 50, 50);
	glPopMatrix();

	//roata fata-dreapta
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 40, y + 20, 20);
	glColor3f(0, 0.2, 0.15);
	glutSolidTorus(7, 20, 50, 50);
	glPopMatrix();


	auxSwapBuffers();

	GLfloat ctlpoints[4][3] = { {-.75, -.75, 0.0},
	{-.5, .75, 0.0}, {.5, .75, 0.0}, {.75, -.75, 0.0} };
	GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0); // culoarea curenta de desenare
	// incepe corpul de redare al curbei Spline
	gluBeginCurve(theNurb);
	gluNurbsCurve(theNurb,	// pointer obiect NURBS
		8, knots,			//numar noduri, tablou noduri
		3,					// intervalul de valori dintre doua puncte de control consecutive
		&ctlpoints[0][0],	// vector puncte de control
		4,					// ordinul curbei 
		GL_MAP1_VERTEX_3);	// tip evaluator
	gluEndCurve(theNurb);

	glFlush();
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
	auxInitDisplayMode(AUX_DOUBLE | AUX_RGB | AUX_DEPTH);
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