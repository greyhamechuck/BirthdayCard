#define FREEGLUT_STATIC
#include <math.h>
#include <GL/freeglut.h>
#include <iostream>
#include "windows.h"
#define MAX_CHAR 128
#define PI 3.1415926

GLfloat step = 1;
int time_interval = 16;
float r = 0;
float R = 20.0;
int n = 360;
float l = 0;
float f = 1;
float a1 = 0, s1 = 0, d = 1;

void when_in_mainloop() {
	glutPostRedisplay(); // force OpenGL to redraw the current window
}
void OnTimer(int value) {
	r += step;
	if (r >= 360)
		r = 0;
	else if (r <= 0)
		r = 359;
	f += step;
	if (f >= 1.5)
		f = 0;
	else if (f <= 0)
		f = 1.4;
	glutTimerFunc(time_interval, OnTimer, 1);
} //Timer
void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;
	if (isFirstCall) {
		isFirstCall = 0;
		lists = glGenLists(MAX_CHAR);
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	for (; *str != '\0'; ++str) {
		glCallList(lists + *str);
	}
}
void selectFont(int size, int charset, const char* face) {
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0, charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}   //Which draw strings("Happy Birthday")


void mouse_input(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON && step >= -15)
		step -= 1; // decrement step
	else if (state == GLUT_DOWN && button == GLUT_RIGHT_BUTTON && step <= 15)
		step += 1; // increment step
}

void keyboard_input(unsigned char key, int x, int y) {// keyboard interaction
	if (key == 'q' || key == 'Q')
		exit(0);
	else if (key == 'a' || key == 'A')
		l += 5;
	else if (key == 'd' || key == 'D')
		l -= 5;
	else if (key == 'z' || key == 'Z')
		a1 += 10;
	else if (key == 'x' || key == 'X')
		a1 -= 10;
	else if (key == 'c' || key == 'C')
		s1 += 10;
	else if (key == 'v' || key == 'V')
		s1 -= 10;
	else if (key == 'b' || key == 'B')
		d += 0.05;
	else if (key == 'n' || key == 'N')
		d -= 0.05;


}

void firstdisplay() {
	/*glMatrixMode(GL_PROJECTION); //projection transformation
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	glClear(GL_COLOR_BUFFER_BIT);*/
	glPushMatrix();
	glTranslatef(280, 70, 0);
	glColor3f(1, 0.3, 0.6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(35 * cos(2 * PI * i / n), 35 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();

	glPopMatrix();

	//Curtain

	glPushMatrix();
	glColor3f(0.4, 0.6, 1);
	glBegin(GL_POLYGON);
	glVertex2f(0, 600);
	glVertex2f(0, 350);
	glVertex2f(800, 350);
	glVertex2f(800, 600);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 400, 0);
	glColor3f(1, 0.5, 0.83);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 200);
	glVertex2f(240, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(800, 400, 0);
	glColor3f(1, 0.5, 0.83);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(0, 400);
	glVertex2f(-240, 200);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.6, 1, 0.83);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 350);
	glVertex2f(800, 350);
	glVertex2f(800, 0);
	glEnd();
	glPopMatrix();


	//Table
	glPushMatrix();
	glTranslatef(200, 0, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 140);
	glVertex2f(0, 170);
	glVertex2f(400, 170);
	glVertex2f(400, 140);
	glEnd();
	glPopMatrix();

	//Cake
	glPushMatrix();
	glTranslatef(200, 0, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_POLYGON);
	glVertex2f(100, 190);
	glVertex2f(100, 240);
	glVertex2f(300, 240);
	glVertex2f(300, 190);
	glEnd();
	glColor3f(0.5, 0.25, 0.1);
	glBegin(GL_POLYGON);
	glVertex2f(100, 170);
	glVertex2f(100, 190);
	glVertex2f(300, 190);
	glVertex2f(300, 170);
	glEnd();
	glPopMatrix();

	//Candles
	glPushMatrix();
	glTranslatef(200, 0, 0);
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(195, 240);
	glVertex2f(195, 280);
	glVertex2f(205, 280);
	glVertex2f(205, 240);
	glEnd();
	glPopMatrix();

	//Fire
	glPushMatrix();
	glTranslatef(394.5, 283, 0);
	glScalef(f, f, f);
	glColor3f(1, 0.55, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(0, 0);
	glVertex2f(10, 0);
	glVertex2f(5, 10);
	glEnd();
	glPopMatrix();

	//Trees
	glPushMatrix();
	glTranslatef(100, 80, 0);
	glColor3f(0.4, 0.35, 0.17);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 150);
	glVertex2f(50, 150);
	glVertex2f(50, 0);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(100, 80, 0);
	glColor3f(0, 0.5, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(-100, 150);
	glVertex2f(150, 150);
	glVertex2f(24, 300);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex2f(-25, 240);
	glVertex2f(75, 240);
	glVertex2f(24, 340);
	glEnd();
	glPopMatrix();

	//Tree needs to be moved

	glPushMatrix();
	glTranslatef(l, 0, 0);
	glTranslatef(400, 80, 0);
	glColor3f(0.4, 0.35, 0.17);
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(0, 150);
	glVertex2f(50, 150);
	glVertex2f(50, 0);
	glEnd();
	glPushMatrix();
	glColor3f(0, 0.5, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(-100, 150);
	glVertex2f(150, 150);
	glVertex2f(24, 300);
	glEnd();
	glColor3f(0, 0.5, 0.35);
	glBegin(GL_TRIANGLES);
	glVertex2f(-25, 240);
	glVertex2f(75, 240);
	glVertex2f(24, 340);
	glEnd();
	glPopMatrix();
	glPopMatrix();



	//Ballon
	glPushMatrix();
	glTranslatef(640, 200, 0);
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2f(0, 50);
	glVertex2f(0, 230);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(640, 430, 0);
	glColor3f(1, 0.3, 0.6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(R * cos(2 * PI * i / n), R * sin(2 * PI * i / n));   //Ball
	}
	glEnd();
	glPopMatrix();

	//SmileFace;
	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(644, 432);
	glVertex2f(644, 435);
	glVertex2f(648, 435);
	glVertex2f(648, 432);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(0, 0, 0);
	glBegin(GL_POLYGON);
	glVertex2f(636, 432);
	glVertex2f(636, 435);
	glVertex2f(632, 435);
	glVertex2f(632, 432);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(621.5, 420, 0);
	float x;
	float factor = 0.1f;
	glColor3f(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (x = 4 * PI; x < 8 * PI; x += 0.1f) {
		glVertex2f(x, 4 * sin(x / 4));

	}
	glEnd();
	glPopMatrix();


	//Draw 2D text;
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	selectFont(48, ANSI_CHARSET, "Comic Sans MS");
	glRasterPos2f(200, 460);
	drawString("Happy Birthday!");
	glPopMatrix();

	//WindandFLower
	glPushMatrix();
	glTranslatef(280, 70, 0);
	glColor3f(0.3, 1, 0.6);
	glRotated(r, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 * cos(2 * PI * i / n) - 45, 20 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();
	glPushMatrix();
	glColor3f(0.3, 1, 0.6);
	glRotated(72, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 * cos(2 * PI * i / n) - 45, 20 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();
	glColor3f(0.3, 1, 0.6);
	glRotated(72, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 * cos(2 * PI * i / n) - 45, 20 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();
	glColor3f(0.3, 1, 0.6);
	glRotated(72, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 * cos(2 * PI * i / n) - 45, 20 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();
	glColor3f(0.3, 1, 0.6);
	glRotated(72, 0, 0, 1);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(20 * cos(2 * PI * i / n) - 45, 20 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();
	glPopMatrix();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(280, 70, 0);
	glColor3f(1, 0.3, 0.6);
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex2f(35 * cos(2 * PI * i / n), 35 * sin(2 * PI * i / n));   //Ball
	}
	glEnd();

	glPopMatrix();

	glFlush();
}
void display() {
	glMatrixMode(GL_PROJECTION); //projection transformation
	glLoadIdentity();
	gluOrtho2D(0, 800, 0, 600);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	//Draw reference axes
	glPushMatrix();
	glTranslatef(a1, s1, 0);
	glScalef(d, d, 0);
	firstdisplay();
	glPopMatrix();
	glFlush();

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Birthday Card");
	glutDisplayFunc(display);
	glutIdleFunc(when_in_mainloop);
	glutTimerFunc(time_interval, OnTimer, 1);
	glutKeyboardFunc(keyboard_input);
	glutMouseFunc(mouse_input);
	glutMainLoop();
}