#include <gl/glut.h>
#include <gl/gl.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <stdlib.h>

#define M_PI 3.14

const float clockR    = 80.0f,
	clockVol  = 100.0f,

	angle1min = M_PI / 30.0f,

	minStart  = 0.9f,
	minEnd    = 1.0f,

	stepStart = 0.8f,
	stepEnd   = 1.0f;

const int windowWidth = 600,
	windowHeight = 600;

float angleHour = 0,
	angleMin  = 0,
	angleSec  = 0;


void newLine(float rStart, float rEnd, float angle){
	float c = cos(angle)/2, s = sin(angle)/2;
	glVertex2f( clockR*rStart*c, clockR*rStart*s);
	glVertex2f( clockR*rEnd*c, clockR*rEnd*s);
}

typedef struct
{
float x;
float y;
}CIRCLE;

CIRCLE circle;

void createcircle (int k, int r, int h) {
    glBegin(GL_LINES);
    for (float i = 0; i < 180; i++)
    {
    circle.x = r * cos(i) - h;
    circle.y = r * sin(i) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    
    circle.x = r * cos(i + 0.1) - h;
    circle.y = r * sin(i + 0.1) + k;
    glVertex3f(circle.x + k,circle.y - h,0);
    }
    glEnd();
}

void RenderScene(void){
	int i;

	glClear(GL_COLOR_BUFFER_BIT);	
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(2.0f);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);
	 
	createcircle(100,50,100);
	glBegin(GL_LINES);
	for(i=0; i<60; i++){
		if(i%5){ // normal minute
			if(i%5 == 1)
				glColor3f(0.0f, 0.0f, 0.0f);
			newLine(minStart, minEnd, i*angle1min);
		}else{
			glColor3f(1.0f, 0.0f, 0.0f);
			newLine(stepStart, stepEnd, i*angle1min);
		}
	}
	glEnd();

	glFlush();
}

///////////////////////////////////////////////////////////
// Called by GLUT library when the window has chanaged size
void ChangeSize(GLsizei w, GLsizei h){
  GLfloat aspectRatio;

  // Prevent a divide by zero
  if(h == 0)
    h = 1;

  // Set Viewport to window dimensions
  glViewport(0, h/4, w, h);
 
  // Reset coordinate system
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Establish clipping volume (left, right, bottom, top, near, far)
  aspectRatio = (GLfloat)w / (GLfloat)h ;
  if (w <= h)
    glOrtho (-clockVol, clockVol, -clockVol / aspectRatio, clockVol / aspectRatio, 1.0, -1.0);
  else
    glOrtho (-clockVol * aspectRatio, clockVol * aspectRatio, -clockVol, clockVol, 1.0, -1.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

int main(int argc, char* argv[]){
	glutInit(&argc,argv);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(0,0);

	glutCreateWindow("code 6-13 page 274");
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutMainLoop();

	return 0;
}
