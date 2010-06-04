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
#include <stdio.h>

float angle = 0, delta_angle = 0, ratio;
float x = 0, y = 1.75, z = 5;
float lx = 0, ly = 0, lz = -1;
float delta_move = 0;

float sky[] = {1, 1, 1, 1};

void cottage() {
	glColor3f(0, 0, 1);
	glutSolidCube(1);
	glFlush();
}

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
			  0, 0, 0);
}

void draw() {
	if (delta_move) move(delta_move);
	if (delta_angle) {
		angle += delta_angle;
		orientation(angle);
	}
	
	glClearColor(sky[0], sky[1], sky[2], sky[3]);
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
	for (int i = -2; i < 2; i++) {
		for (int j = -2; j < 2; j++) {
			glPushMatrix();
			glTranslatef(i * 10, 0, j * 10);
			cottage();
			glPopMatrix();
		}
	}
	glutSwapBuffers();
}

void reshape(int width, int height) {
	if (height == 0) height = 1;
	ratio = 1 * width / height;
	
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

void pressArrows(int key, int mx, int my) {
	switch (key) {
		case GLUT_KEY_LEFT : delta_angle = -0.001;
			break;
		case GLUT_KEY_RIGHT : delta_angle = 0.001;
			break;
		case GLUT_KEY_UP : delta_move = 0.1;
			break;
		case GLUT_KEY_DOWN : delta_move = -0.1;
			break;
	}
}

void releaseArrows(int key, int mx, int my) {
	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : delta_angle = 0.0;
			break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : delta_move = 0;
			break;	
	}
}

void pressKeys(unsigned char key, int mx, int my) {
	if (key == 'q') exit(0);
}

void motion(int mx, int my) {
	int relx = 0, rely = 0;
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	
	relx = mx - width/2;
	rely = -1 * (my - height/2);
	delta_angle = relx * 0.00005;
	
	printf("Absolute: %ix%i, Relative: %ix%i\n", mx, my, relx, rely);
}

void mouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_UP) {
		delta_angle = 0.0;
	}
}

void idle() {
	reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 300);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Cottages");
	glutReshapeFunc(&reshape);
	glutDisplayFunc(&draw);
	glutKeyboardFunc(&pressKeys);
	glutSpecialFunc(&pressArrows);
	glutSpecialUpFunc(&releaseArrows);
	glutMotionFunc(&motion);
	glutMouseFunc(&mouse);
	glutIdleFunc(&idle);
	glutMainLoop();
	return 0;
}