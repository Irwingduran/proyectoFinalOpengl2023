//gcc mouse_tetera.c -o mouse_tetera -lGL -lGLU -lglut
#include <stdlib.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
float alpha,beta;
int x0,y0,cont=0;
int coord[4][2];
void display(void) {
glClear(GL_COLOR_BUFFER_BIT);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(20.0f, 1.0f, 1.0f, 10.0f);
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0f, 0.0f, 5.0f,0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
glRotatef(alpha, 1.0f, 0.0f, 0.0f);
glRotatef(beta, 0.0f, 1.0f, 0.0f);
glutWireTeapot(0.5);
glFlush();
glutSwapBuffers();
}
void mouseCoordinate(GLint x,GLint y)
{ coord[cont][0]=(GLfloat)x;
coord[cont][1]=(GLfloat)y;
printf("Posicion del mouse en coordenadas de ventana:\n");
printf("X = %d Y=%d \n",coord[cont][0],coord[cont][1]);
}
void onMouse(int button, int state, int x, int y) {
if ( (button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN) ) {
x0 = x; y0 = y;
cont++;

printf("coordenada=%d \n",cont);
mouseCoordinate(x0,y0);

}
}
void onMotion(int x, int y) {
alpha = (alpha + (y - y0));
beta = (beta + (x - x0));
x0 = x; y0 = y;
glutPostRedisplay();
}
int main(int argc, char* argv[]){
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
glutInitWindowSize(400, 400);
glutInitWindowPosition(100, 100);
glutCreateWindow("Ejemplo de menus");
glutDisplayFunc(display);
glutMouseFunc(onMouse);
glutMotionFunc(onMotion);
glutMainLoop();

return 0;
}
