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

float dx = 0, dy = -60;
int index = -1;
const int jumEnd = 78;
const int jump = 3;

int valueOfX[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1 };
int valueOfY[] = { -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -41, -42, -43, -44, -45, -46, -47, -48, -49, -50, -51, -52, -53, -54, -55, -56, -57, -58, -59, -60, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -41, -42, -43, -44, -45, -46, -47, -48, -49, -50, -51, -52, -53, -54, -55, -56, -57, -58, -59, -60 };

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
	if (index + jump >= jumEnd)
		return 0;
	else index + jump;
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
		glVertex3f(cos(degInRad)*r + dx, sin(degInRad)*r + dy, 0);
	}
	glEnd();
	glPopMatrix();
	glColor3f(1.0, 0.3, 0.3);
}



//////////////////// UI 구성 모듈 ///////////////////////

void watchCircleofbottom()
{	
	index = getIndex(index);

	dx = valueOfX[index];
	dy = valueOfY[index];

	glLineWidth(10);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	glVertex2f(dx, watchTop);
	glVertex2f(0.0, watchBot);
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
	
	//시계추
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

	//콜백함수 등록
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutTimerFunc(30, TimerFunction, 1);
	glutMainLoop();

	return 0;
}

int h = 0.05;
float t, v;
const int x = 30 * M_PI / 180;
float pen_fm = 0.01, pen_m = 0.1, pen_l = 100 * 0.01, pen_j = 0.02, pen_g = 9.8;
int gndCenterX = 150, gndConterY = 20;
float penLoength = pen_l * 100 * 2;


float calcCodeFunc(float tVal, float xVal, float vVal)
{
	return -pen_fm / (pen_m*pen_l*pen_l + pen_j)*vVal - pen_m*pen_g*pen_l / (pen_m*pen_l*pen_l + pen_j)*xVal;
}

void GetPath(float t, float x, float v, float *ResultOfx, float *ResultOfy)
{
	float kx1 = v;
	float kv1 = calcCodeFunc(t, x, v);

	float kx2 = v + h*kv1 / 2;
	float kv2 = calcCodeFunc(t + h / 2, x + h*kx1 / 2, v + h*kv1 / 2);

	float kx3 = v + h*kv1 / 2;
	float kv3 = calcCodeFunc(t + h / 2, x + h*kx2 / 2, v + h*kv2 / 2);

	float kx4 = v + h*kv3;
	float kv4 = calcCodeFunc(t + h, x + h*kx3, v + h*kv3);

	*ResultOfx = h*(kx1 + 2 * kx2 + 2 * kx3 + kx4) / 6;
	*ResultOfy = h*(kv1 + 2 * kv2 + 2 * kv3 + kv4) / 6;
}

void loop()
{
	float DX = 0, DY = 0;
	t += h;

	GetPath(t, x, v, &DX, &DY);

	printf("%lf %lf\n", DX, DY);
}
