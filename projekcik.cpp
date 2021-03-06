#include "stdafx.h"
#include "glut.h"

GLfloat v[4][2] = { { -1.5, -1.5 },{ 1.5, -1.5 },{ -1.5, 1.5 },{ 1.5, 1.5 } };
int n; 

void rectangle(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d)
{
	glBegin(GL_POLYGON);
	glVertex2fv(b);
	glVertex2fv(a);
	glVertex2fv(c);
	glVertex2fv(d);
	glEnd();
}

void divide_rectangle(GLfloat *a, GLfloat *b, GLfloat *c, GLfloat *d, int m)
{
	GLfloat v0_0[2], v0_1[2], v1_0[2], v1_1[2], v2_0[2], v2_1[2], v3_0[2], v3_1[2], vA[2], vB[2], vC[2], vD[2];
	int j;
	
	if (m > 0)
	{
		for (j = 0; j < 2; j++)
		{
			v0_0[j] = (b[j] - a[j]) / 3 + a[j];
			v0_1[j] = (b[j] - a[j]) * 2 / 3 + a[j];
			v1_0[j] = (d[j] - b[j]) / 3 + b[j];
			v1_1[j] = (d[j] - b[j]) * 2 / 3 + b[j];
			v2_0[j] = (c[j] - a[j]) / 3 + a[j];
			v2_1[j] = (c[j] - a[j]) * 2 / 3 + a[j];
			v3_0[j] = (d[j] - c[j]) / 3 + c[j];
			v3_1[j] = (d[j] - c[j]) * 2 / 3 + c[j];
			vA[j] = (v1_0[j] - v2_0[j]) / 3 + v2_0[j];
			vB[j] = (v1_0[j] - v2_0[j]) * 2 / 3 + v2_0[j];
			vC[j] = (v1_1[j] - v2_1[j]) / 3 + v2_1[j];
			vD[j] = (v1_1[j] - v2_1[j]) * 2 / 3 + v2_1[j];
		}
		
		divide_rectangle(a, v0_0, v2_0, vA, m - 1);
		divide_rectangle(v0_0, v0_1, vA, vB, m - 1);
		divide_rectangle(v0_1, b, vB, v1_0, m - 1);
		divide_rectangle(v2_0, vA, v2_1, vC, m - 1);
		divide_rectangle(vB, v1_0, vD, v1_1, m - 1);
		divide_rectangle(v2_1, vC, c, v3_0, m - 1);
		divide_rectangle(vC, vD, v3_0, v3_1, m - 1);
		divide_rectangle(vD, v1_1, v3_1, d, m - 1);
	}
	else(rectangle(a, b, c, d));
}

void display()
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	divide_rectangle(v[0], v[1], v[2], v[3], n);
	glFlush();
}

void myinit()
{ 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2.0, 2.0, -2.0, 2.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(0.34f, 0.53f, 0.65f);
}

int main(int argc, char **argv)
{
	n = 5;
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000); 
	glutCreateWindow("Dywan Sierpinskiego");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}