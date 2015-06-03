#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <stdio.h>
#define M_PI 3.14

const int windowWidth = 600, windowHeight = 600;
const int scaleX = 0, scaleY = 40;

const float clockR = 80.0f, clockVol = 100.0f, angle1min = M_PI / 30.0f,
			minStart = 0.9f, minEnd = 1.0f, stepStart = 0.8f, stepEnd = 1.0f;


//시, 분, 초 시계바늘 변수
float angleHour = 0, angleMin = 0, angleSec = 0;


//시, 분, 초 눈금을 그리는데 사용되는 함수
//이 함수는 동쪽부터 시작해서 북, 서, 남, 동으로 반시계방향으로
//회전하면서 눈금을 그린다.
void newLine(float rStart, float rEnd, float angle){
	float c = cos(angle) / 2, s = sin(angle) / 2;

	glVertex2f(clockR*rStart*c + scaleX, clockR*rStart*s + scaleY);
	glVertex2f(clockR*rEnd*c + scaleX, clockR*rEnd*s + scaleY);
}

typedef struct
{
	float x;
	float y;
}CIRCLE;

CIRCLE circle;

//원을 그리는 함수
//cos, sin함수를 이용해 1,2,3,4분면을 각각 그린다.
void createcircle(int k, int r, int h) {	
	//glBegin(GL_LINES);
	glBegin(GL_QUADS);
	for (float i = 0; i < 180; i++)
	{
		circle.x = r * cos(i) - h + scaleX;
		circle.y = r * sin(i) + k + scaleY;
		glVertex3f(circle.x + k , circle.y - h, 0);

		circle.x = r * cos(i + 0.1) - h + scaleX;
		circle.y = r * sin(i + 0.1) + k + scaleY;
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

	//시계테두리 원을 그린다
	createcircle(100, 50, 100);	
	glColor3f(0.0f, 0.0f, 0.0f);
	glRectf(-0.5f, -50.0f, 0.5f, -100.0f);

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

	//시간과 분을 가르키는 시계바늘 그린다
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


//시, 분, 초 시계바늘이 현재시간을 가르키게 하는 타이머 함수이다.

void TimerFunction(int value){
	struct timeb tb;
	time_t tim = time(0);
	struct tm* t;

	//표준함수인 localtime을 이용해 time_t 구조체 변수에 시간을 저장한다.
	t = localtime(&tim);
	//timeb 구조체 구조에 맞게 변경한다.
	ftime(&tb);

	angleSec = (float)(t->tm_sec + (float)tb.millitm / 1000.0f) / 30.0f * M_PI;
	angleMin = (float)(t->tm_min) / 30.0f * M_PI + angleSec / 60.0f;
	angleHour = (float)(t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour) / 6.0f * M_PI +
		angleMin / 12.0f;

	//MyDisplay함수를 호출한 후 Timer을 재 호출한다.
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

int main(int argc, char* argv[]){
	GLfloat aspectRatio = (GLfloat)windowWidth / (GLfloat)windowHeight;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("20094422 최성욱 시계바늘 레포트");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-clockVol, clockVol, -clockVol / aspectRatio, clockVol / aspectRatio, 1.0, -1.0);

	//콜백함수 등록
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(30, TimerFunction, 1);
	glutMainLoop();

	return 0;
}
