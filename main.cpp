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
#include "diamond.h"
#include "lamp.h"

float x = 0, y = 1.5, z = 20;
float lx = 0, ly = 0, lz = -1;
float angle = 0, delta_angle = 0;
float delta_move = 0;

float bred = 0, bgreen = 0.15, bblue = 0.15;
float gred = 0, ggreen = 0, gblue = 0;
char object = 'c';

int city_size = 2;

bool light_lamps_1 = false;
bool light_lamps_2 = false;
bool light_lamps_3 = false;

bool texture_switch = true;
bool texture_linear = true;

bool go_left = true;
bool go_backword = true;

float spot_direction_x = 0;
float spot_direction_z = 0;

Ground *ground;
Cottage *cottage;
Diamond *diamond;
Lamp *lamp;

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
	
	// ground
	ground->draw(texture_switch, texture_linear);
	
	// objects
	for (int i = -city_size; i < city_size; i++) {
		for (int j = -city_size; j < city_size; j++) {
			glPushMatrix();
			glTranslatef(i * 5, 0, j * 5);
			switch (object) {
				case 'c':
					cottage->draw(texture_switch, texture_linear);
					break;
				case 'd':
					diamond->draw();
					break;
			}
			glPopMatrix();
		}
	}
	
	// lamps
	for (int i = -2; i < 1; i++) {
		for (int j = -1; j < 1; j++) {
			glPushMatrix();
			glTranslatef(i * 5 + 2.5, 0, j * 7.5);
			lamp->draw();
			glPopMatrix();
		}
	}
	
	// lights
	
	float light_position_0[] = {-7.5, 1, -7.5, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light_position_0);
	float light_position_1[] = {-7.5, 1, 0, 1};
	glLightfv(GL_LIGHT1, GL_POSITION, light_position_1);
	float light_position_2[] = {-2.5, 1, -7.5, 1};
	glLightfv(GL_LIGHT2, GL_POSITION, light_position_2);
	float light_position_3[] = {-2.5, 1, 0, 1};
	glLightfv(GL_LIGHT3, GL_POSITION, light_position_3);
	float light_position_4[] = {2.5, 1, -7.5, 1};
	glLightfv(GL_LIGHT4, GL_POSITION, light_position_4);
	float light_position_5[] = {2.5, 1, 0, 1};
	glLightfv(GL_LIGHT5, GL_POSITION, light_position_5);
	
	float light_position_6[] = {0, 5, 0, 1};
	float spot_direction_6[] = {spot_direction_x, -1, spot_direction_z};
	glLightfv(GL_LIGHT6, GL_POSITION, light_position_6);
	glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spot_direction_6);

	float light_position_7[] = {0, 5, 0, 1};
	glLightfv(GL_LIGHT7, GL_POSITION, light_position_7);
	
	glutSwapBuffers();
}
void reshape(int width, int height) {
	if (height == 0) height = 1;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, width, height);
	
	gluPerspective(45, width/height, 1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(x, y, z,
			  x + lx, y + ly, z + lz,
			  0, 1, 0);
	draw();
}

// idle/refresh
void idle() {
	if (go_left == true && spot_direction_x > -7) {
		spot_direction_x -= 0.02;
	} else if (go_left == true) {
		go_left = false;
	} else if (go_left == false && spot_direction_x < 7) {
		spot_direction_x += 0.02;
	} else if (go_left == false) {
		go_left = true;
	}
	
	if (go_backword == true && spot_direction_z > -7) {
		spot_direction_z -= 0.05;
	} else if (go_backword == true) {
		go_backword = false;
	} else if (go_backword == false && spot_direction_z < 7) {
		spot_direction_z += 0.05;
	} else if (go_backword == false) {
		go_backword = true;
	}
	
	glutPostRedisplay();
}

// keyboard
void pressSpecialKeys(int key, int kx, int ky) {
	switch (key) {
		case GLUT_KEY_LEFT : delta_angle = -0.01;
			break;
		case GLUT_KEY_RIGHT : delta_angle = 0.01;
			break;
		case GLUT_KEY_UP : delta_move = 1;
			break;
		case GLUT_KEY_DOWN : delta_move = -1;
			break;
	}
}
void releaseSpecialKeys(int key, int kx, int ky) {
	switch (key) {
		case GLUT_KEY_LEFT :
		case GLUT_KEY_RIGHT : delta_angle = 0;
			break;
		case GLUT_KEY_UP :
		case GLUT_KEY_DOWN : delta_move = 0;
			break;
	}
}
void releaseKeys(unsigned char key, int kx, int ky) {
	switch (key) {
		case 'q' : exit(0);
			break;
		case 'z' : city_size += 1;
			break;
		case 'x' : if (city_size != 2) city_size -= 1;
			break;
		case 'c' : texture_switch == true ? texture_switch = false : texture_switch = true;
			break;
		case 'v' : texture_linear == true ? texture_linear = false : texture_linear = true;
			break;
		case '1' :
			if (light_lamps_1 == true) {
				glDisable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
				glDisable(GL_LIGHT2);
				glDisable(GL_LIGHT3);
				glDisable(GL_LIGHT4);
				glDisable(GL_LIGHT5);
				light_lamps_1 = false;
			} else {
				glEnable(GL_LIGHT0);
				glEnable(GL_LIGHT1);
				glEnable(GL_LIGHT2);
				glEnable(GL_LIGHT3);
				glEnable(GL_LIGHT4);
				glEnable(GL_LIGHT5);
				light_lamps_1 = true;
			}
			break;
		case '2' :
			if (light_lamps_2 == true) {
				glDisable(GL_LIGHT6);
				light_lamps_2 = false;
			} else {
				glEnable(GL_LIGHT6);
				light_lamps_2 = true;
			}
			break;
		case '3' :
			if (light_lamps_3 == true) {
				glDisable(GL_LIGHT7);
				light_lamps_3 = false;
			} else {
				glEnable(GL_LIGHT7);
				light_lamps_3 = true;
			}
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
			ground->set_color(gred, ggreen, gblue);
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
		case 4 : bred = 0; bgreen = 0.15; bblue = 0.15;
			break;
	}
}
void change_shape (int option) {
	switch (option) {
		case 1: 
			object = 'c';
			break;
		case 2: 
			object = 'd';
			break;
	}
}

// inits - menu, objects, lights
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
	glutAddMenuEntry("Diamonds", 2);
	glutCreateMenu(change_ground_color);
	glutCreateMenu(change_background_color);
	glutCreateMenu(change_shape);
	glutAddSubMenu("Ground color", submenu1);
	glutAddSubMenu("Background color", submenu2);
	glutAddSubMenu("Shape", submenu3);
	
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void init_objects() {
	ground = new Ground(gred, ggreen, gblue);
	cottage = new Cottage();
	diamond = new Diamond();
	lamp = new Lamp();
}
void init_lights() {
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	float light_ambient_1[] = {0.9, 0.9, 0.6, 1};
	float light_diffuse_1[] = {1, 1, 0.5, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient_1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse_1);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse_1);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient_1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse_1);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient_1);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse_1);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient_1);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse_1);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT4, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.1);
	glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient_1);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse_1);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 0.1);
	glLightf(GL_LIGHT5, GL_LINEAR_ATTENUATION, 0.1);
	glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.1);
	
	float light_ambient_2[] = {1, 1, 1, 1};
	float light_diffuse_2[] = {0.8, 0.8, 0.2, 1};
	glLightfv(GL_LIGHT6, GL_AMBIENT, light_ambient_2);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, light_diffuse_2);
	glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, 25);
    glLightf(GL_LIGHT6, GL_SPOT_EXPONENT, 10);
	
	float light_ambient_3[] = {0.9, 0.9, 0.2, 1};
	float light_diffuse_3[] = {0.9, 0.9, 0.5, 1};
	float light_specular_3[] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT7, GL_AMBIENT, light_ambient_3);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, light_diffuse_3);
	glLightfv(GL_LIGHT7, GL_SPECULAR, light_specular_3);
	
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
	init_lights();
	
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutSpecialFunc(pressSpecialKeys);
	glutSpecialUpFunc(releaseSpecialKeys);
	glutKeyboardUpFunc(releaseKeys);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	glutMainLoop();

	delete cottage;
	delete diamond;
	delete lamp;
	delete ground;
	return 0;
	
}