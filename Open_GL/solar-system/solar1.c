#include <gl/glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

static int Day = 0, Time = 0;
void MyDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f(1.0, 0.3, 0.3);
	glutSolidSphere(0.2, 100, 16);
	glPushMatrix();
		glRotatef((GLfloat)Day, 0.0, 1.0, 0.0);
		glTranslatef(0.7, 0.0, 0.0);
		glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
		glColor3f(0.5, 0.6, 0.7);
		glutSolidSphere(0.1, 100, 8);
		glPushMatrix();
			glRotatef((GLfloat)Time, 0.0, 1.0, 0.0);
			glTranslatef(0.2, 0.0, 0.0);
			glColor3f(0.9, 0.8, 0.2);
			glutSolidSphere(0.04, 100, 8);
		glPopMatrix();
	glPopMatrix();

	glutSwapBuffers();
}

void Mykeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'd':
		Day = (Day + 10) % 360;
		glutPostRedisplay();
		break;
	case 't':
		Time = (Time + 5) % 360;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);
	
	glutCreateWindow("태양계 ver1");
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(Mykeyboard);
	glutMainLoop();

	return 0;
}
