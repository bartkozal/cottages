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

float x = 0, y = 1.5, z = 5;
float lx = 0, ly = 0, lz = -1;
float angle = 0, delta_angle = 0;
float delta_move = 0;

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
	glColor3f(0, 0, 1);
	glutSolidCube(1);
	glFlush();
}

void draw() {
	if (delta_move) move(delta_move);
	if (delta_angle) {
		angle += delta_angle;
		orientation(angle);
	}
	
	glClearColor(1, 1 ,1 , 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// ground
	glColor3f(0.9, 0.9, 0.9);
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
			cottage();
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

// main

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 300);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Cottages");
	glutReshapeFunc(&reshape);
	glutDisplayFunc(&draw);
	glutIdleFunc(&idle);
	glutKeyboardFunc(&pressKeys);
	glutKeyboardUpFunc(&releaseKeys);
	glutMotionFunc(&motion);
	glutMouseFunc(&mouse);
	glutMainLoop();
	return 0;
}