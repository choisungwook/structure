#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#define M_PI 3.14
#define DEGINRAD 3.14 / 180

int dx = 0, dy = -60;
int moveX, moveY = -60, p;
int moveDirection = 0;
int rightX[10000], rightXIndex;
int rightY[10000], rightYIndex;
int index = -1;
int standX = 10;

typedef struct
{
	float x;
	float y;
}CIRCLE;


const int windowWidth = 600, windowHeight = 600;
const int scaleX = 0, scaleY = 40;
const float  watchTop = -50.0f, watchBot = -10.0f;
const int watchline = 40;
const float clockR = 80.0f, clockVol = 100.0f, angle1min = M_PI / 30.0f,
minStart = 0.9f, minEnd = 1.0f, stepStart = 0.8f, stepEnd = 1.0f;

CIRCLE circle;

//시, 분, 초 시계바늘 변수
float angleHour = 0, angleMin = 0, angleSec = 0;

int getIndex(int index)
{
	if (index + 4 >= rightXIndex)
		return 0;
	else index + 4;
}
/////////////////// 그리기 함수에 관련 모듈 ////////////////////////////
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
	for (float i = 0; i < 180; i++)
	{
		circle.x = r * cos(i) - h + scaleX;
		circle.y = r * sin(i) + k + scaleY;
		glVertex3f(circle.x + k, circle.y - h, 0);

		circle.x = r * cos(i + 0.1) - h + scaleX;
		circle.y = r * sin(i + 0.1) + k + scaleY;
		glVertex3f(circle.x + k, circle.y - h, 0);
	}
	glEnd();
}

void drawCircle(const float r){
	glColor3f(0.0, 0.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i<360; i++){
		float degInRad = i*DEGINRAD;
		glVertex3f(cos(degInRad)*r + dx, 0, sin(degInRad)*r + dy);
		glVertex3f(cos(degInRad)*r + dx, sin(degInRad)*r + dy ,0);
	}
	glEnd();
	glPopMatrix();
	glColor3f(1.0, 0.3, 0.3);
}

void GetpathRight()
{
	int x1, y1;

	if (moveX >= moveY)
		return;

	rightX[rightXIndex++] = standX + moveX;
	rightY[rightYIndex++] = -moveY;

	moveX++;
	if (p<0)
		p += 2 * moveX + 1;
	else
	{
		moveY--;
		p += 2 * (moveX - moveY) + 1;
	}

	x1 = moveX;
	y1 = moveY;

	GetpathRight();
	rightX[rightXIndex++] = standX  - x1;
	rightY[rightYIndex++] = -y1;
}

//////////////////// UI 구성 모듈 ///////////////////////

/*
//시계추
void watchBottom()
{
	glLineWidth(10);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(0.0, watchTop);
	glVertex2f(0.0, watchBot);
	glEnd();
	glLineWidth(2.0f);
}
*/

void watchCircleofbottom()
{
	index = getIndex(index);
	dx = rightX[index];
	dy = rightY[index];

	glLineWidth(10);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(dx, watchTop);
	glVertex2f(0,watchBot);
	glEnd();
	glLineWidth(2.0f);

	drawCircle(10);
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
	//glRectf(-0.5f, -50.0f, 0.5f, -100.0f);

	//시계줄
	//watchBottom();

	//시계라인
	watchCircleofbottom();

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
	angleHour = (float)(t->tm_hour > 12 ? t->tm_hour - 12 : t->tm_hour) / 6.0f * M_PI +
		angleMin / 12.0f;

	//MyDisplay함수를 호출한 후 Timer을 재 호출한다.
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}

int main(int argc, char* argv[]){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("20094422 최성욱 시계바늘 레포트");
	glClearColor(1.0, 1.0, 1.0, 1.0);

	//오른쪽값 구하기
	moveY = 70;
	p = 1 + 70;
	GetpathRight();

	//콜백함수 등록
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(30, TimerFunction, 1);
	glutMainLoop();

	return 0;
}
