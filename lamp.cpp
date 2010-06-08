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
	glTranslated(0, 2, 0);
	glutSolidSphere(0.1, 10, 10);
	glPopMatrix();
	glPushMatrix();
	glScalef(0.1, 3, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	glTranslated(0, 2, 0);
	glScalef(1, 2, 1);
	glColor3f(1, 1, 1);
	glutWireCube(0.5);
	
	
	// glass
	
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glColor4f(0, 0.5, 0.5, 0.5);
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
	glEnable(GL_LIGHTING);
	
	glPopMatrix();
	glFlush();
}