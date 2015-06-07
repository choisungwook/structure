#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#define SPEED 10
#pragma warning(disable:4996)

#define M_PI 3.14
#define DEGINRAD 3.14 / 180

typedef struct{
	float x;
	float y;
}CIRCLE;

const int windowWidth = 600, windowHeight = 600;
const int dx = 0, dy = -60;
const int scaleX = 0, scaleY = 40;
const float  watchTop = -50.0, watchBot = -10.0f;
const int watchline = watchTop - watchBot;
const float clockR = 80.0f, clockVol = 100.0f, angle1min = M_PI / 30.0f,
minStart = 0.975f, minEnd = 1.0f, stepStart = 0.9f, stepEnd = 1.0f;

CIRCLE circle;

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


//원을 그리는 함수
//cos, sin함수를 이용해 1,2,3,4분면을 각각 그린다.
void createcircle(int k, int r, int h) {
	//glBegin(GL_LINES);
	glBegin(GL_QUADS);
	for (float i = 0; i < 180; i++)   {
		glColor3f(0.5, 0.0, 0.0);
		circle.x = r * cos(i) - h + scaleX;
		circle.y = r * sin(i) + k + scaleY;
		glVertex3f(circle.x + k, circle.y - h, 0);

		circle.x = r * cos(i + 0.1) - h + scaleX;
		circle.y = r * sin(i + 0.1) + k + scaleY;
		glVertex3f(circle.x + k, circle.y - h, 0);
	}
	glEnd();
}
// 시계추의 원
void drawCircle(){
	const float r = 10;
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i<360; i++){
		float degInRad = i*DEGINRAD;
		glVertex3f(cos(degInRad)*r + dx, 0, sin(degInRad)*r + dy);
		glVertex3f(cos(degInRad)*r + dx, sin(degInRad)*r + dy, 0);
	}
	glEnd();
	glPopMatrix();
	glColor3f(1.0, 0.3, 0.3);
}


//시계추
void watchBottom(){
	glLineWidth(10);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, watchTop);
	glVertex2f(0.0, watchBot);
	glEnd();
	glLineWidth(2.0f);
}

void watchCircle(){
	drawCircle();
}

int start_time = timeGetTime();

float l = 1, g = 3000;
int T = 360 * sqrt(l / g);

void action(int value){
	float t = (timeGetTime() - start_time % T);
	float theta = 30 * sin(sqrt((g / l)*t));

	glColor3f(1.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(0.0, 1.8, 0.0);
	glRotatef(theta, 0.0, 0.0, 1.0);

	//시계줄
	watchBottom();

	//시계추 공
	watchCircle();

	glPopMatrix();

	//glutTimerFunc(SPEED, action, 1);
}

void MyDisplay(void){


	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	//시계테두리 원을 그린다
	createcircle(100, 50, 100);
	glColor3f(0.0f, 1.0f, 0.0f);
	//glRectf(-0.5f, -50.0f, 0.5f, -100.0f);

	action(1);



	// 시계 시, 분, 초 눈금을 그리는 newLine함수를 호출하고
	// 5간격마다 구별을 하기 위해 해당 눈금은 빨간색으로 그린다.
	glBegin(GL_LINES);

	for (int i = 0; i<60; i++){
		//i가 5의 배수가 되면 5분씩의 눈금이다.
		glColor3f(0.0, 0.0, 0.0);
		if (i % 5 == 0)
			newLine(stepStart, stepEnd, i*angle1min);
		newLine(minStart, minEnd, i*angle1min);
	}
	glEnd();

	// 시침, 분침
	glLineWidth(2.5f);
	glColor3f(0.0, .0, 1.0);
	glBegin(GL_LINES);
	newLine(0.0f, 0.5f, -angleHour + M_PI / 2);
	newLine(0.0f, 0.8f, -angleMin + M_PI / 2);
	glEnd();

	// 초침
	glLineWidth(1.0f);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	newLine(0.0f, 0.8f, -angleSec + M_PI / 2);
	glEnd();

	//더블버퍼링을 사용한다.
	glutSwapBuffers();
}

void MyReshape(GLsizei w, GLsizei h){
	GLfloat aspectRatio;
	// Prevent a divide by zero
	if (h == 0)
		h = 1;
	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

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
	angleHour = (float)(t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour) / 6.0f * M_PI + angleMin / 12.0f;

	//MyDisplay함수를 호출한 후 Timer을 재 호출한다.
	glutPostRedisplay();
	glutTimerFunc(SPEED, TimerFunction, 1);
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("괘종시계");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//콜백함수 등록
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(SPEED, TimerFunction, 1);	
	glutMainLoop();

	return 0;
}
