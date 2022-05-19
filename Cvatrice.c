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

#define stripeImageWidth 32
GLubyte stripeImage[3 * stripeImageWidth];

void makeStripeImage(void)
{ //construieste o textura 1D cu 3 octeti pentru fiecare texel
	//din 32 texeli 5 sunt rosii si 27 sunt verzi
	int j;

	for (j = 0; j < stripeImageWidth; j++) {
		stripeImage[3 * j] = (j <= 4) ? 255 : 0; //rosu
		stripeImage[3 * j + 1] = (j > 4) ? 255 : 0; //verde
		stripeImage[3 * j + 2] = 0; //galben
	}
}

GLfloat sgenparams[] = { 1.0, 1.0, 1.0, 0.0 };

void myinit(void) {
	glClearColor(1.0, 1.0, 1.0, 1.0);

	makeStripeImage();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage1D(GL_TEXTURE_1D, 0, 3, stripeImageWidth, 0,
		GL_RGB, GL_UNSIGNED_BYTE, stripeImage); //specificare texturii

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	glTexGenfv(GL_S, GL_OBJECT_PLANE, sgenparams);

	glShadeModel(GL_FLAT);
	theNurb = gluNewNurbsRenderer();
	gluNurbsProperty(theNurb, GLU_SAMPLING_TOLERANCE, 10.0);

	glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	glEnable(GL_TEXTURE_GEN_S);
	//glEnable(GL_TEXTURE_1D);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_NORMALIZE);

	//glMaterialf(GL_FRONT, GL_SHININESS, 70.0);

	GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	//componenta ambientala din sursa 0 este lumina cu intensitate 0
	GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//componenta difuza din sursa 0 este lumina cu intensitate 1 
	//pentru fiecare componenta de culoare R, G, B
	GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
	//componenta speculara din sursa 0 este lumina cu intensitate 1 
	//pentru fiecare componenta de culoare
	GLfloat position[] = { 5.0, 1.0, 0.0, 0.0 };
	//sursa 0 este la infinit pe directia y=3, z=2
	GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat local_view[] = { 0.0 };


	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);

	glEnable(GL_LIGHTING);//activare iluminare
	glEnable(GL_LIGHT0);//activare sursa 0
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

void CALLBACK rot_z_down(AUX_EVENTREC* event)
{
	alfa = alfa + 10;
}

void CALLBACK rot_z_up(AUX_EVENTREC* event)
{
	alfa = alfa - 10;
}

void CALLBACK IdleFunction(void)
{
	alfa -= 1;
	display();
	Sleep(4);
}

void CALLBACK display(void)
{

	GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };//coeficient de reflexie ambientala
	GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
	GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };//coeficient de reflexie difuza
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };//coeficient de reflexie speculara
	GLfloat no_shininess[] = { 0.0 };//exponentul de reflexie speculara
	GLfloat low_shininess[] = { 5.0 };//exponentul de reflexie speculara
	GLfloat high_shininess[] = { 100.0 };//exponentul de reflexie speculara
	GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };//intensitatea luminii emise


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	qobj = gluNewQuadric();
	glRotatef(alfa, 0, 1, 0);

	// corp principal (orizontal (dreapta))
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 22, y + 80, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glColor3f(0.6, 0, 0);
	gluCylinder(qobj, 20, 20, 40, 4, 200);
	glPopMatrix();

	// corp principal (orizontal (mij))
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 5, y + 80, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glColor3f(0.6, 0, 0);

	gluCylinder(qobj, 20, 20, 40, 4, 200);
	glPopMatrix();

	// corp principal (orizontal (stanga))
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 30, y + 80, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glColor3f(0.6, 0, 0);
	gluCylinder(qobj, 20, 20, 40, 4, 200);
	glPopMatrix();

	// cabina (vertical)
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 110, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glColor3f(0, 0, 0.5);
	gluCylinder(qobj, 20, 20, 70, 4, 250);
	glPopMatrix();

	// esapament
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 30, y + 98, 0);
	glRotatef(90, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glColor3f(0.3, 0.05, 0);
	gluCylinder(qobj, 5, 5, 18, 4, 60);
	glPopMatrix();


	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);


	// roata spate-dreapta
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 28, 24.5);
	glColor3f(0.3, 0, 0.4);
	glutSolidTorus(10, 30, 80, 80);
	glPopMatrix();

	// roata spate-stanga
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x + 50, y + 28, -24.5);
	glColor3f(0.2, 0, 0.3);
	glutSolidTorus(10, 30, 80, 80);
	glPopMatrix();

	//roata fata-stanga
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 40, y + 20, -21.5);
	glColor3f(0, 0.25, 0.2);
	glutSolidTorus(7, 20, 50, 50);
	glPopMatrix();

	//roata fata-dreapta
	glPushMatrix();
	gluQuadricDrawStyle(qobj, GLU_LINE);
	glTranslatef(x - 40, y + 20, 21.5);
	glColor3f(0, 0.2, 0.15);
	glutSolidTorus(7, 20, 50, 50);
	glPopMatrix();

	auxSwapBuffers();

	GLfloat ctlpoints[4][3] = { {-.75, -.75, 0.0},
	{-.5, .75, 0.0}, {.5, .75, 0.0}, {.75, -.75, 0.0} };
	GLfloat knots[8] = { 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	auxKeyFunc(AUX_LEFT, MutaStanga);
	auxKeyFunc(AUX_RIGHT, MutaDreapta);
	auxKeyFunc(AUX_UP, MutaSus);
	auxKeyFunc(AUX_DOWN, MutaJos);
	auxMouseFunc(AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
	auxMouseFunc(AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);


	auxReshapeFunc(myReshape);
	auxIdleFunc(IdleFunction);
	auxMainLoop(display);
	return(0);
}