#include <gl/glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#define WINDOWSIZE 300 //윈도우 사이즈
#define TIMER 50 //Timer 주기
				 //50milisecond 이후에는 끊김현상이 일어난다.

//8개 정점위치
GLfloat MyVertices[8][3] = { { -0.25, -0.25, 0.25 }, { -0.25, 0.25, 0.25 }, { 0.25, 0.25, 0.25 },
{ 0.25, -0.25, 0.25 }, { -0.25, -0.25, -0.25 }, { -0.25, 0.25, -0.25 }, { 0.25, 0.25, -0.25 },
{ 0.25, -0.25, -0.25 } };

//정점색
GLfloat MyColors[8][3] = { { 0.2, 0.2, 0.2 }, { 1.0, 0.0, 0.0 }, { 1.0, 1.0, 0.0 }, { 0.0, 1.0, 0.0 },
{ 0.0, 0.0, 1.0 }, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 }, { 0.0, 1.0, 1.0 } };

GLubyte MyVertexList[24] = { 0, 3, 2, 1, 2, 3, 7, 6, 0, 4, 7, 3, 1, 2, 6, 5, 4, 5, 6, 7, 0, 1, 5, 4 };

//회전 각도
GLfloat Angle = 0.0;

//타이머 함수
//회전 각도를 TIMERmilisecond마다 1.0씩 증가
void MyTimer(int Value)
{
	Angle = Angle + 1.0f; // 회전각도 증가
	glutPostRedisplay(); // 화면을 다시 그려줌
	glutTimerFunc(TIMER, MyTimer, 1);
}

void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFrontFace(GL_CCW); //표면을 반시계방향 순서로 나열
	glEnable(GL_CULL_FACE); // 눈에보이지 않은 면을 제거
	glEnableClientState(GL_COLOR_ARRAY); // 칼라배열 활성화
	glEnableClientState(GL_VERTEX_ARRAY); // 정점배열 활성화
	glColorPointer(3, GL_FLOAT, 0, MyColors);
	glVertexPointer(3, GL_FLOAT, 0, MyVertices);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(Angle, 1.0, 1.0, 1.0); //Angle만큼 회전
	
	//정육면체를 그린다
	for (GLint i = 0; i < 6; i++)
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_BYTE, &MyVertexList[4 * i]);

	//작업했던 내용을 실행
	glFlush();
}


int main(int argc, char** argv)
{
	//Window 초기화 과정
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB);
	glutInitWindowSize(WINDOWSIZE, WINDOWSIZE);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("20094422 최성욱");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	//콜백함수 등록
	glutTimerFunc(TIMER, MyTimer, 1);
	glutDisplayFunc(MyDisplay);

	//Loop실행
	glutMainLoop();

	return 0;
}
