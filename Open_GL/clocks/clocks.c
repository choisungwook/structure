#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <stdio.h>
#define M_PI 3.14

const int windowWidth = 600, windowHeight = 600;
const float clockR = 80.0f, clockVol = 100.0f, angle1min = M_PI / 30.0f,
			minStart = 0.9f, minEnd = 1.0f, stepStart = 0.8f, stepEnd = 1.0f;


//시, 분, 초 시계바늘 변수
float angleHour = 0, angleMin = 0, angleSec = 0;


//시, 분, 초 눈금을 그리는데 사용되는 함수
//이 함수는 동쪽부터 시작해서 북, 서, 남, 동으로 반시계방향으로
//회전하면서 눈금을 그린다.
void newLine(float rStart, float rEnd, float angle){
	float c = cos(angle) / 2, s = sin(angle) / 2;
	glVertex2f(clockR*rStart*c, clockR*rStart*s);
	glVertex2f(clockR*rEnd*c, clockR*rEnd*s);
}

typedef struct
{
	float x;
	float y;
}CIRCLE;

CIRCLE circle;

void createcircle(int k, int r, int h) {
	//glBegin(GL_LINES);
	glBegin(GL_QUADS);
	for (float i = 0; i < 180; i++)
	{
		circle.x = r * cos(i) - h;
		circle.y = r * sin(i) + k;
		glVertex3f(circle.x + k, circle.y - h, 0);

		circle.x = r * cos(i + 0.1) - h;
		circle.y = r * sin(i + 0.1) + k;
		glVertex3f(circle.x + k, circle.y - h, 0);
	}
	glEnd();
}

void MyDisplay(void){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	createcircle(100, 50, 100);
	//createrectangle(-0.2, 0.1, 0.4, 0.4);
	glRectf(-0.5f, 0.5f, 0.5f, -0.5f);

	//시계 시, 분, 초 눈금을 그리는 newLine함수를 호출하고
	//5간격마다 구별을 하기 위해 해당 눈금은 빨간색으로 그린다.
	glBegin(GL_LINES);
	for (i = 0; i<60; i++){
		//i가 5의 배수가 되면 5분씩의 눈금이다.
		if (i % 5){ 
			if (i % 5 == 1)
				glColor3f(0.0f, 0.0f, 0.0f);
			newLine(minStart, minEnd, i*angle1min);
		}
		else{
			glColor3f(1.0f, 0.0f, 0.0f);
			newLine(stepStart, stepEnd, i*angle1min);
		}
	}
	glEnd();

	//시간과 분을을 가르키는 시계바늘 그린다
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	newLine(0.0f, 0.5f, -angleHour + M_PI / 2);
	newLine(0.0f, 0.8f, -angleMin + M_PI / 2);
	glEnd();


	//초를 가르키는 시계바늘을 그린다.
	glLineWidth(1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	newLine(0.0f, 0.8f, -angleSec + M_PI / 2);
	glEnd();
	
	//더블버퍼링을 사용한다.
	glutSwapBuffers();
}

///////////////////////////////////////////////////////////
//Reshape함수를 정의한다
//Reshape함수를 정의한 이유는 창의 크기를 변경시 
//비율을 유지하기 위함이다.
void MyReshape(GLsizei w, GLsizei h){
	GLfloat aspectRatio;

	printf("가로창 크기 : %d 세로창 크기 :%d\n", w, h);
	// Prevent a divide by zero
	if (h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, h / 4, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	aspectRatio = (GLfloat)w / (GLfloat)h;
	if (w <= h)
		glOrtho(-clockVol, clockVol, -clockVol / aspectRatio, clockVol / aspectRatio, 1.0, -1.0);
	else
		glOrtho(-clockVol * aspectRatio, clockVol * aspectRatio, -clockVol, clockVol, 1.0, -1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("code 6-13 page 274");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();

	return 0;
}
