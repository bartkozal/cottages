/*
 *  main.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 04/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */


#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <math.h>
#include <stdlib.h>

float x = 0, y = 1.75, z = 5;
float lx = 0, ly = 0, lz = -1;
float angle = 0, delta_angle = 0;
float delta_move = 0;

float background[] = {1, 1, 1, 0};
float ground[] = {0.9, 0.9, 0.9};
char object = 'c';

// camera

void orientation(float angle) {
	lx = sin(angle);
	lz = -cos(angle);
	glLoadIdentity();
	gluLookAt(x, y, z,
			  x + lx, y + ly, z + lz,
			  0, 1, 0);
}

void move(float i) {
	x = x + i * lx * 0.1;
	z = z + i * lz * 0.1;
	glLoadIdentity();
	gluLookAt(x, y, z,
			  x + lx, y + ly, z + lz,
			  0, 1, 0);
}

// draw

void cottage() {
	glPushMatrix();
	glScaled(0.8, 0.8, 1.1);
	glTranslatef(0, 1, 0);
	// walls
	glColor3f(0, 0, 1);
	glBegin(GL_QUADS);
		glVertex3f(-1, 0, 1);
		glVertex3f(1, 0, 1);
		glVertex3f(1, 1, 1);
		glVertex3f(-1, 1, 1);

		glVertex3f(1, 0, 1);
		glVertex3f(1, 0, -1);
		glVertex3f(1, 1, -1);
		glVertex3f(1, 1, 1);
	
		glVertex3f(1, 0, -1);
		glVertex3f(-1, 0, -1);
		glVertex3f(-1, 1, -1);
		glVertex3f(1, 1, -1);
	
		glVertex3f(-1, 0, 1);
		glVertex3f(-1, 0, -1);
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, 1, 1);
	glEnd();
	// roof
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, 1, 1);
		glVertex3f(1, 1, 1);
		glVertex3f(0, 2, 0);
	
		glVertex3f(1, 1, 1);
		glVertex3f(1, 1, -1);
		glVertex3f(0, 2, 0);
	
		glVertex3f(1, 1, -1);
		glVertex3f(-1, 1, -1);
		glVertex3f(0, 2, 0);
	
		glVertex3f(-1, 1, -1);
		glVertex3f(-1, 1, 1);
		glVertex3f(0, 2, 0);
	glEnd();
	glPopMatrix();
	glFlush();
}

void teapot() {
	glPushMatrix();
	glColor3f(0, 1, 0);
	glTranslatef(0, 1, 0);
	glutSolidTeapot(1);
	glPopMatrix();
	glFlush();
}

void draw() {
	if (delta_move) move(delta_move);
	if (delta_angle) {
		angle += delta_angle;
		orientation(angle);
	}
	
	glClearColor(background[0], background[1], background[2], background[3]);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ground
	glColor3f(ground[0], ground[1], ground[2]);
	glBegin(GL_QUADS);
		glVertex3f(-100, 0, -100);
		glVertex3f(-100, 0, 100);
		glVertex3f(100, 0, 100);
		glVertex3f(100, 0, -100);
	glEnd();
	
	// cottages
	for (int i = -3; i < 3; i++) {
		for (int j = -3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 5, 0, j * 5);
			switch (object) {
				case 'c' : cottage();
					break;
				case 't' : teapot();
					break;
			}
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}

void reshape(int width, int height) {
	if (height == 0) height = 1;
	float ratio = width / height;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, width, height);
	
	gluPerspective(45, ratio, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
			  x + lx, y + ly, z + lz,
			  0, 1, 0);
	draw();
}

void idle() {
	glutPostRedisplay();
}

// keyboard

void pressKeys(unsigned char key, int mx, int my) {
	switch (key) {
		case 'a' : delta_angle = -0.003;
			break;
		case 'd' : delta_angle = 0.003;
			break;
		case 'w' : delta_move = 0.5;
			break;
		case 's' : delta_move = -0.5;
			break;
		case 'q' : exit(0);
			break;

	}
}

void releaseKeys(unsigned char key, int mx, int my) {
	switch (key) {
		case 'a' :
		case 'd' : delta_angle = 0;
			break;
		case 'w' :
		case 's' : delta_move = 0;
			break;	
	}
}

// mouse

void motion(int mx, int my) {
	int relx = 0, rely = 0;
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	relx = mx - width/2;
	rely = -1 * (my - height/2);
	delta_angle = relx * 0.00001;
	delta_move = rely * 0.001;
	
}

void mouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_UP) {
		delta_angle = 0;
		delta_move = 0;
	}
}

void ground_color(int option) {
	switch (option) {
		case 1 : ground[0] = 1; ground[1] = 0; ground[2] = 0;
			break;                                           
		case 2 : ground[0] = 0; ground[1] = 1; ground[2] = 0;
			break;                                           
		case 3 : ground[0] = 0; ground[1] = 0; ground[2] = 1;
			break;
	}
}
void background_color(int option) {
	switch (option) {
		case 1 : background[0] = 1; background[1] = 0; background[2] = 0; background[3] = 1;
			break;
		case 2 : background[0] = 0; background[1] = 1; background[2] = 0; background[3] = 1;
			break;
		case 3 : background[0] = 0; background[1] = 0; background[2] = 1; background[3] = 1;
			break;
	}
}

void shape (int option) {
	switch (option) {
		case 1 : object = 'c';
			break;
		case 2 : object = 't';
			break;
	}
}

// menu
void createMenu() {
	int submenu1 = glutCreateMenu(ground_color);
	int submenu2 = glutCreateMenu(background_color);
	int submenu3 = glutCreateMenu(shape);
	
	glutSetMenu(submenu1);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutSetMenu(submenu2);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutSetMenu(submenu3);
	glutAddMenuEntry("Cottage", 1);
	glutAddMenuEntry("Teapot", 2);
	glutCreateMenu(shape);
	glutCreateMenu(ground_color);
	glutCreateMenu(background_color);
	glutCreateMenu(shape);
	glutAddSubMenu("Ground color", submenu1);
	glutAddSubMenu("Background color", submenu2);
	glutAddSubMenu("Shape", submenu3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// main

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 300);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Cottages");
	createMenu();
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutKeyboardFunc(pressKeys);
	glutKeyboardUpFunc(releaseKeys);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}