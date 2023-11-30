#include <GL/glut.h>
#include <string.h>
#include <stdio.h>

#define QUADRADO 1
#define TRIANGULO 2
#define LOSANGO 3

char texto[30];
GLfloat win, r, g, b;
Glint view_w, view_h, primitiva
	
void DesenhaQuadrado(void)
{
	 glBegin(GL_QUADS);
			glVertex2f(-25.0f, -25.0f);
			glVertex2f(-25.0f, 25.0f);
			glVertex2f(25.0f, 25.0f);
			glVertex2f(25.0f, -25.0f);
	 glEnd();
	
}

void DesenhaTriangulo(void)
{
	glBegin(GL_TRIANGLES);
			glVertex2f(-25.0f, -25.0f);
	        glVertex2f(0.0f, 25.0f);
			glVertex2f(25.0f, -25.0f);
	glEnd();
}

void DesenhaLosango(void)
{
	glBegin(GL_POLYGON);
			glVertex2f(-25.0f, 0.0f);
	        glVertex2f(0.0f, 25.0f);
	        glVertex2f(25.0f, 0.0f);
	        glVertex2f(0.0f, -25.0f);
	glEnd();
}

void DesenhaTexto(char *string)
{
	glPushMatrix();
		glRasterPos2f(-win,win-(win*0.08));
		
		while(*string)
			gluBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,*string++);
	glPopMatrix();
}

void Desenha(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	
	glColor3f(r,g,b);
	
	switch (primitiva) {
	case QUADRADO: DesenhaQuadrado();
	break;
	case TRIANGULO: DesenhaTriangulo();
	break;
	case LOSANGO: DesenhaLosango();
	break;
	}
	glColor3f(1.0f,1.0f,1.0f);
	DesenhaTexto(texto);
	glutSwapBuffers();
}

void Inicializa (void)
{
	glClearColor(0.0f,0.0f, 0.0f, 1.0f)0;
	win=150.0f;
	primitiva = QUADRADO;
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	strcpy(texto, "(0,0)");
}

void AlteraTemanhoJanela(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (-win, win, -win, win);
}

void MoveMouseBotaoPressionado(int x, int y)
{
	sprintf(texto, "Botao pressionado (%d,%d)", x, y);
	glutPostRedisplay();
}

void TeclasEspeciais(int key, int x, int y) 
{
	if(key == GLUT_KEY_UP){
		win -= 10;
		if (win < 10) win = 10;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D (-win, win, -win, win);
	}
	if(key == GLUT_KEY_DOWN) {
		win += 10;
		if (win > 500) win = 500;
		glMatrixMode(GL_PROJECTION);
		G	}
}














