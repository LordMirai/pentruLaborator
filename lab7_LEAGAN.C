/*
Programul afiseaza un patrat pe care il translateaza 
pe axa x la apasarea sagetilor stanga, dreapta
*/
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>
#include <math.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK MutaStanga(void);
void CALLBACK MutaDreapta(void);
void CALLBACK MutaSus(void);
void CALLBACK MutaJos(void);
void CALLBACK rot_z_up(AUX_EVENTREC *event);
void CALLBACK rot_z_down(AUX_EVENTREC *event);



static int leagan = 0, x=0,y=0,alfa=10;


void myinit (void) {
// coeficientii de reflexie pentru reflexia ambientala 
	// si cea difuza sunt cei impliciti
    GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.0, 0.5, 0.5, 1.0 };
/*  rflectanta speculara si exponentul de reflexie speculara 
	nu sunt la valorile implicite (0.0)   */
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
// valori implicite pentru intensitatea sursei LIGHT0
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
/*  pozitia sursei nu are valori implicite */
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING); // activare iluminare
    glEnable(GL_LIGHT0);	// activare sursa 0

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
}


void CALLBACK leaganFata (void)
{
    leagan = (leagan + 5) % 360;
}

void CALLBACK leaganSpate (void)
{
    leagan = (leagan - 5) % 360;
}

void CALLBACK MutaStanga(void)
{
	x=x-10;
}

void CALLBACK MutaDreapta(void)
{
	x=x+10;
}

void CALLBACK MutaSus(void)
{
	y=y+10;
}

void CALLBACK MutaJos(void)
{
	y=y-10;
}

void CALLBACK rot_z_up(AUX_EVENTREC *event)
{
	alfa=alfa+10;
}

void CALLBACK rot_z_down(AUX_EVENTREC *event)
{
	alfa=alfa-10;
}


void CALLBACK display (void)
{

	GLfloat mat_diffuse1[] = { 0.5, 0.0, 1.0, 1.0 };
	GLfloat mat_diffuse2[] = { 1.0, 1.0, 0.0, 1.0 };
	GLfloat mat_diffuse3[] = { 0.0, 1.0, 1.0, 1.0 };
	GLfloat mat_diffuse4[] = { 0.0, 0.0, 1.0, 1.0 };

	//glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	glLoadIdentity();

	glRotatef(alfa,1,0,0);
	glRotated(20,0,1,0);


	//cilindru sus
	glPushMatrix();
	//glColor3f(0,0.5,0.5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse1);
	glTranslatef(x-75,y+75,0);
	glRotatef(90,0,0,1);
	auxSolidCylinder(10, 150); 
	glPopMatrix();

	
	//cilindru dreapta
	glPushMatrix();
	//glColor3f( 0.5,0.5,0);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse2);
	glTranslatef(x+75,y+80,0);
	glRotatef ((GLfloat) leagan, 1, 0.0, 0);
	auxSolidCylinder(10, 200); 
	glPopMatrix();

	
	//cilindru stanga
glPushMatrix();

	//glColor3f( 0.5,0.0,0.5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse3);
	glTranslatef(x-75,y+80,0);
	glRotatef ((GLfloat) leagan, 1, 0.0, 0);
	auxSolidCylinder(10, 200); 

	//paralelipiped
	glPushMatrix();
	//glColor3f(0.0,0.0,0.5);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glTranslatef(75,-200,0);
	glRotatef(90,1,0,0);
	auxSolidBox(150, 50, 20);
	glPopMatrix();


glPopMatrix();

	
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
     glOrtho (-160.0, 160.0, 160.0*(GLfloat)h/(GLfloat)w, 
        -160.0*(GLfloat)h/(GLfloat)w, -1000.0, 1000.0);
    else 
    glOrtho (-160.0*(GLfloat)w/(GLfloat)h, 
        160.0*(GLfloat)w/(GLfloat)h, -160.0, 160.0, -1000.0, 1000.0);
    glMatrixMode(GL_MODELVIEW);

	
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
    auxInitPosition (0, 0, 1000, 800);
    auxInitWindow ("Leaganul Uta-Uta");
    myinit ();

	auxKeyFunc (AUX_a, MutaStanga);
	auxKeyFunc (AUX_d, MutaDreapta);
	auxKeyFunc (AUX_w, MutaSus);
	auxKeyFunc (AUX_s, MutaJos);
	
	auxMouseFunc (AUX_LEFTBUTTON, AUX_MOUSEDOWN, rot_z_up);
	auxMouseFunc (AUX_RIGHTBUTTON, AUX_MOUSEDOWN, rot_z_down);

	
	auxKeyFunc (AUX_UP, leaganFata);
    auxKeyFunc (AUX_DOWN, leaganSpate);

    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
