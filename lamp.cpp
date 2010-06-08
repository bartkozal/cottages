/*
 *  lamp.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 08/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include "lamp.h"

Lamp::Lamp() {}

void Lamp::draw() {
	glPushMatrix();
	glColor3f(0, 0, 0);
	
	glScalef(0.4, 0.4, 0.4);
	glutSolidCube(0.3);
	glTranslated(0, 1.3, 0);
	glPushMatrix();
	glScalef(0.1, 3, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	glTranslated(0, 2, 0);
	glScalef(1, 2, 1);
	glutWireCube(0.5);
	
	// glass
	
	glColor3f(1, 0, 0);
	glScalef(0.25, 0.25, 0.25);
	glTranslated(0, -1, 0);
	glBegin(GL_QUADS);
	
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(-1, 0, -1);
	
	glVertex3f(-1, 2, 1);
	glVertex3f(1, 2, 1);
	glVertex3f(1, 2, -1);
	glVertex3f(-1, 2, -1);
	
	glVertex3f(-1, 0, 1);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 2, 1);
	glVertex3f(-1, 2, 1);
	
	glVertex3f(-1, 0, -1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 2, -1);
	glVertex3f(-1, 2, -1);
	
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 2, -1);
	glVertex3f(-1, 2, 1);
	
	glVertex3f(1, 0, 1);
	glVertex3f(1, 0, -1);
	glVertex3f(1, 2, -1);
	glVertex3f(1, 2, 1);
	
	glEnd();
	
	glPopMatrix();
	glFlush();
}