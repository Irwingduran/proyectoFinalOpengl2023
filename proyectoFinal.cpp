#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <string.h>
#include <vector>

// Constantes
#define QUADRADO 1
#define TRIANGULO 2
#define LOSANGO 3

// Variables
char texto[30];
GLfloat win, r, g, b;
GLint view_w, view_h, primitiva;

// Estructura para un punto en 2D
struct Point {
	float x, y;
};

// Vector para puntos de control del spline cuadrático
std::vector<Point> quadraticControlPoints;

// Vector para puntos de control del spline cúbico
GLfloat cubicControlPoints[4][3] = {
	{-1.0, -1.0, 0.0},
{-0.5, 1.0, 0.0},
	{0.5, -1.0, 0.0},
{1.0, 1.0, 0.0}
};

// Factor de escala en las direcciones x e y para el escalado 2D
float Sx = 15.0f;
float Sy = 20.0f;

// Factor de escala para el escalado respecto a un punto en 2D
GLfloat scaleSx = 2.0;
GLfloat scaleSy = 2.0;
GLfloat scalexF = 55.0;
GLfloat scaleyF = 60.0;

// Ángulo de rotación para la rotación 2D
float angle = 45.0;

// Variables para la rotación 3D
GLfloat rotationAngle = 0.0f;

// Función que despliega el menú principal
void MenuPrincipal(int op);

// Función que dibuja un cuadrado
void DesenhaQuadrado(void) {
	glBegin(GL_QUADS);
	glVertex2f(-25.0f, -25.0f);
	glVertex2f(-25.0f, 25.0f);
	glVertex2f(25.0f, 25.0f);
	glVertex2f(25.0f, -25.0f);
	glEnd();
}

// Función que dibuja un triángulo
void DesenhaTriangulo(void) {
	glBegin(GL_TRIANGLES);
	glVertex2f(-25.0f, -25.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(25.0f, -25.0f);
	glEnd();
}

// Función que dibuja un rombo
void DesenhaRombo(void) {
	glBegin(GL_POLYGON);
	glVertex2f(-25.0f, 0.0f);
	glVertex2f(0.0f, 25.0f);
	glVertex2f(25.0f, 0.0f);
	glVertex2f(0.0f, -25.0f);
	glEnd();
}

// Función que dibuja un texto en la ventana GLUT
void DesenhaTexto(char *string) {
	glPushMatrix();
	glRasterPos2f(-win, win - (win * 0.08));
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *string++);
	glPopMatrix();
}

// Función callback para el dibujo
void Desenha(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Define el color actual
	glColor3f(r, g, b);
	
	// Dibuja la primitiva seleccionada
	switch (primitiva) {
	case QUADRADO:
		DesenhaQuadrado();
		break;
	case TRIANGULO:
		DesenhaTriangulo();
		break;
	case LOSANGO:
		DesenhaRombo();
		break;
	}
	
	// Muestra la posición del mouse en la ventana
	glColor3f(1.0f, 1.0f, 1.0f);
	DesenhaTexto(texto);
	
	glutSwapBuffers();
}

// Inicializa los parámetros de rendering
void Inicializa(void) {
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	win = 150.0f;
	primitiva = QUADRADO;
	r = 0.0f;
	g = 0.0f;
	b = 1.0f;
	strcpy(texto, "(0,0)");
}

// Función callback para cambios en el tamaño de la ventana
void AlteraTamanhoJanela(GLsizei w, GLsizei h) {
	glViewport(0, 0, w, h);
	view_w = w;
	view_h = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-win, win, -win, win);
}

// Función callback para el movimiento del mouse con un botón presionado
void MoveMouseBotaoPressionado(int x, int y) {
	sprintf(texto, "Botao pressionado (%d,%d)", x, y);
	glutPostRedisplay();
}

// Función callback para el movimiento del mouse
void MoveMouse(int x, int y) {
	sprintf(texto, "(%d,%d)", x, y);
	glutPostRedisplay();
}

// Función callback para gestionar eventos del teclado para teclas especiales
void TeclasEspeciais(int key, int x, int y) {
	if (key == GLUT_KEY_UP) {
		win -= 10;
		if (win < 10)
			win = 10;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win, win, -win, win);
	}
	if (key == GLUT_KEY_DOWN) {
		win += 10;
		if (win > 500)
			win = 500;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(-win, win, -win, win);
	}
	glutPostRedisplay();
}

// Función callback para el manejo del menú de colores
void MenuCor(int op) {
	switch (op) {
	case 0:
		r = 1.0f;
		g = 0.0f;
		b = 0.0f;
		break;
	case 1:
		r = 0.0f;
		g = 1.0f;
		b = 0.0f;
		break;
	case 2:
		r = 0.0f;
		g = 0.0f;
		b = 1.0f;
		break;
	}
	glutPostRedisplay();
}

// Función callback para el manejo del menú de primitivas
void MenuPrimitiva(int op) {
	switch (op) {
	case 3:
		primitiva = QUADRADO;
		break;
	case 4:
		primitiva = TRIANGULO;
		break;
	case 5:
		primitiva = LOSANGO;
		break;
	}
	glutPostRedisplay();
}

// Función callback para el manejo del menú principal
void MenuPrincipal(int op) {
	switch (op) {
	case 6:
		exit(0);
		break;
	}
}

// Función callback para la rotación de la primitiva seleccionada
void RotacionPrimitiva() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
	glColor3f(r, g, b);
	
	// Dibuja la primitiva seleccionada
	switch (primitiva) {
	case QUADRADO:
		DesenhaQuadrado();
		break;
	case TRIANGULO:
		DesenhaTriangulo();
		break;
	case LOSANGO:
		DesenhaRombo();
		break;
	}
	
	glutSwapBuffers();
	glFlush();
}

// Función callback para el manejo del menú de transformaciones
void MenuTransformacoes(int op) {
	switch (op) {
	case 7: // Escalado
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glScalef(Sx, Sy, 1.0);
		glColor3f(r, g, b);
		
		// Dibuja la primitiva seleccionada
		switch (primitiva) {
		case QUADRADO:
			DesenhaQuadrado();
			break;
		case TRIANGULO:
			DesenhaTriangulo();
			break;
		case LOSANGO:
			DesenhaRombo();
			break;
		}
		
		glutSwapBuffers();
		glFlush();
		break;
	case 8: // Rotación 2D
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glColor3f(r, g, b);
		
		// Dibuja la primitiva seleccionada
		switch (primitiva) {
		case QUADRADO:
			DesenhaQuadrado();
			break;
		case TRIANGULO:
			DesenhaTriangulo();
			break;
		case LOSANGO:
			DesenhaRombo();
			break;
		}
		
		glutSwapBuffers();
		glFlush();
		break;
	case 9: // Rotación 3D
		rotationAngle += 5.0f;
		RotacionPrimitiva();
		break;
	case 10: // Escalado respecto a un punto en 2D
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(scalexF, scaleyF, 0.0);
		glScalef(scaleSx, scaleSy, 1.0);
		glTranslatef(-scalexF, -scaleyF, 0.0);
		glColor3f(r, g, b);
		
		// Dibuja la primitiva seleccionada
		switch (primitiva) {
		case QUADRADO:
			DesenhaQuadrado();
			break;
		case TRIANGULO:
			DesenhaTriangulo();
			break;
		case LOSANGO:
			DesenhaRombo();
			break;
		}
		
		glutSwapBuffers();
		glFlush();
		break;
	}
}

// Función principal
int main(int argc, char **argv) {
	// Inicializa GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Trabalho 2 - Computacao Grafica");
	
	// Registra las funciones callback
	glutDisplayFunc(Desenha);
	glutReshapeFunc(AlteraTamanhoJanela);
	glutMotionFunc(MoveMouseBotaoPressionado);
	glutPassiveMotionFunc(MoveMouse);
	glutSpecialFunc(TeclasEspeciais);
	
	// Crea el submenú de colores
	int menuCor = glutCreateMenu(MenuCor);
	glutAddMenuEntry("Vermelho", 0);
	glutAddMenuEntry("Verde", 1);
	glutAddMenuEntry("Azul", 2);
	
	// Crea el submenú de primitivas
	int menuPrimitiva = glutCreateMenu(MenuPrimitiva);
	glutAddMenuEntry("Quadrado", 3);
	glutAddMenuEntry("Triangulo", 4);
	glutAddMenuEntry("Losango", 5);
	
	// Crea el menú principal
	glutCreateMenu(MenuPrincipal);
	glutAddSubMenu("Cor", menuCor);
	glutAddSubMenu("Primitiva", menuPrimitiva);
	glutAddMenuEntry("Sair", 6);
	
	// Asigna la posición del menú principal
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	// Crea el submenú de transformaciones
	int menuTransformacoes = glutCreateMenu(MenuTransformacoes);
	glutAddMenuEntry("Escalado", 7);
	glutAddMenuEntry("Rotacao 2D", 8);
	glutAddMenuEntry("Rotacao 3D", 9);
	glutAddMenuEntry("Escalado respecto a um ponto em 2D", 10);
	
	// Asigna la posición del menú de transformaciones
	glutAttachMenu(GLUT_LEFT_BUTTON);
	
	// Inicializa parámetros de rendering
	Inicializa();
	
	// Bucle principal
	glutMainLoop();
	
	return 0;
}
