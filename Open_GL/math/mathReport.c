#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define SIZE 1000
#define PI 3.141592
#define START 7.0
#define END -7.5
#define LOOP 0.5

void Draw();
void drawYX();
void drawYXOfPoints();
void drawSquartX();
void drawSquartXOfPoints();
void RdrawSquartX();
void RdrawSquartXOfPoints();
void drawSinx();
void drawCircle();

float x_w = 7.0, y_w = -7.0;
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(SIZE, SIZE);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("y=x");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-x_w, x_w, y_w, -y_w, -1.0, 1.0);

	//콜백함수 등록
	glutDisplayFunc(Draw);

	glutMainLoop();
	return 0;
}

void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	//세로축
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(x_w, 0.0, 0);
	glVertex3f(y_w, 0.0, 0);
	glEnd();

	//가로축
	glColor3f(0.5, 0.5, 0.5);
	glLineWidth(5.0);
	glBegin(GL_LINE_STRIP);
	glVertex3f(0.0, y_w, 0);
	glVertex3f(0.0, x_w, 0);
	glEnd();

	//drawYXOfPoints();
	//drawYX();
	//drawSquartX(); // y = x^2 선
	//drawSquartXOfPoints();; // y = x^2 점
	//RdrawSquartX(); // y = -x^2 선
	//RdrawSquartXOfPoints(); // y = -x^2 점
	//drawSinx(); //사인함수
	drawCircle();
	glFlush();
}

void drawYX()
{
	float i;

	glLineWidth(5.0);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = END; i <= START; i += 0.1){
		glVertex3f(i, i, 0);
	}
	glEnd();
}

void drawYXOfPoints()
{
	float i;
	glPointSize(20.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	for (i = END; i <= START; i += LOOP){
		glVertex3f(i, i, 0);
	}
	glEnd();
}

// y = x^2 선
void drawSquartX()
{
	float i;

	glLineWidth(5.0);
	glColor3f(0.5, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = END; i <= START; i += 0.1){
		glVertex3f(i, pow(i, 2), 0);
	}
	glEnd();
}

// y = -x^2 점
void drawSquartXOfPoints()
{
	float i;

	glPointSize(20.0);
	glColor3f(0.2, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (i = END; i <= START; i += LOOP){
		glVertex3f(i, -pow(i, 2), 0);
	}
	glEnd();
}

// y = -x^2 선
void RdrawSquartX()
{
	float i;

	glLineWidth(5.0);
	glColor3f(0.5, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	for (i = START; i >= END; i -= 0.1){
		glVertex3f(i, -pow(i, 2), 0);
	}
	glEnd();
}

// y = -x^2 점
void RdrawSquartXOfPoints()
{
	float i;

	glPointSize(20.0);
	glColor3f(0.2, 1.0, 0.5);
	glBegin(GL_POINTS);
	for (i = END; i >= START; i -= LOOP){
		glVertex3f(i, pow(i, 2), 0);
	}
	glEnd();
}

void drawSinx()
{
	float i;
	int degree = 180;
	float radian = degree * 3.141592 / 180;

	glLineWidth(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (i = -6.8; i <= 6.8; i += 0.1){
		glVertex3f(i, sin(i), 0);

	}
	glEnd();
}

void drawCircle()
{
	float x, y;
	float r = 3.0;
	int a = 3, b = 2;

	glLineWidth(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (x = 0; x <= 3.0; x += 0.1){
		y = sqrt(pow(r, 2) - pow(x, 2) );
		glVertex3f(x+a, y+b, 0);				
	}
	glEnd();

	glLineWidth(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (x = 0; x <= 3.0; x += 0.1){
		y = sqrt(pow(r, 2) - pow(x, 2));
		glVertex3f(x+a, -y+b, 0);		
	}
	glEnd();

	glLineWidth(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (x = 0; x <= 3.0; x += 0.1){
		y = sqrt(pow(r, 2) - pow(x, 2));
		glVertex3f(-x+a, y+b, 0);
		
	}
	glEnd();

	glLineWidth(5.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	for (x = 0; x <= 3.0; x += 0.1){
		y = sqrt(pow(r, 2) - pow(x, 2));
		glVertex3f(-x+a, -y+b, 0);
	}
	glEnd();
}
