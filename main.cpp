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

#include "ground.h"
#include "cottage.h"
#include "teapot.h"

float x = 0, y = 1, z = 20;
float lx = 0, ly = 0, lz = -1;
float angle = 0, delta_angle = 0;
float delta_move = 0;

float bred = 0.47, bgreen = 0.75, bblue = 0.76;
float gred = 0.9, ggreen = 0.9, gblue = 0.9;
char object;

Ground *ground;

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
void draw() {
	if (delta_move) move(delta_move);
	if (delta_angle) {
		angle += delta_angle;
		orientation(angle);
	}
	
	glClearColor(bred, bgreen, bblue, 1);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	ground->draw();
	
	Cottage *c = new Cottage();
	delete c;
	glutSwapBuffers();
}
void reshape(int width, int height) {
	if (height == 0) height = 1;
	GLfloat light_position[] = { 0, 0, 0, 1 };
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, width, height);
	
	gluPerspective(45, width/height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	gluLookAt(x, y, z,
			  x + lx, y + ly, z + lz,
			  0, 1, 0);
	draw();
}

// idle/refresh
void idle() {
	glutPostRedisplay();
}

// keyboard
void pressKeys(unsigned char key, int mx, int my) {
	switch (key) {
		case 'a' : delta_angle = -0.01;
			break;
		case 'd' : delta_angle = 0.01;
			break;
		case 'w' : delta_move = 1;
			break;
		case 's' : delta_move = -1;
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
	delta_angle = relx * 0.0001;
	delta_move = rely * 0.01;
	
}
void mouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON and state == GLUT_UP) {
		delta_angle = 0;
		delta_move = 0;
	}
}

// menu
void change_ground_color(int option) {
	switch (option) {
		case 1: 
			ground->set_color(1, 0, 0);
			break;
		case 2: 
			ground->set_color(0, 1, 0);
			break;
		case 3:
			ground->set_color(0, 0, 1);
			break;
		case 4:
			ground->set_color(0.9, 0.9, 0.9);
			break;
	}
}
void change_background_color(int option) {
	switch (option) {
		case 1 : bred = 1; bgreen = 0; bblue = 0;
			break;
		case 2 : bred = 0; bgreen = 1; bblue = 0;
			break;
		case 3 : bred = 0; bgreen = 0; bblue = 1;
			break;
		case 4 : bred = 0.47; bgreen = 0.75; bblue = 0.76;
			break;
	}
}
void change_shape (int option) {
	switch (option) {
		case 1 : object = 'c';
			break;
		case 2 : object = 't';
			break;
	}
}
void init_menu() {
	int submenu1 = glutCreateMenu(change_ground_color);
	int submenu2 = glutCreateMenu(change_background_color);
	int submenu3 = glutCreateMenu(change_shape);
	
	glutSetMenu(submenu1);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Reset", 4);
	glutSetMenu(submenu2);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Reset", 4);
	glutSetMenu(submenu3);
	glutAddMenuEntry("Cottage", 1);
	glutAddMenuEntry("Teapot", 2);
	glutCreateMenu(change_ground_color);
	glutCreateMenu(change_background_color);
	glutCreateMenu(change_shape);
	glutAddSubMenu("Ground color", submenu1);
	glutAddSubMenu("Background color", submenu2);
	glutAddSubMenu("Shape", submenu3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// objects
void init_objects() {
	ground = new Ground(gred, ggreen, gblue);
}

// lights
void init_lights() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
}

// main
int main(int argc, char *argv[]) {
	
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(300, 300);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Cottages");
	
	init_menu();
	init_objects();
	//	init_lights();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutKeyboardFunc(pressKeys);
	glutKeyboardUpFunc(releaseKeys);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutMainLoop();

	delete ground;
	return 0;
	
}