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
	
	float mat_ambient[] = {0.02, 0.02, 0.02, 1};
	float mat_diffuse[] = {0.01, 0.01, 0.01, 1};
	float mat_specular[] = {0.4, 0.4, 0.4, 1};
	float high_shininess[] = {0.10};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	glPushMatrix();
	glColor3f(0, 0, 0);
	
	glScalef(0.4, 0.4, 0.4);
	glutSolidCube(0.3);
	glTranslated(0, 1.3, 0);
	glPushMatrix();
	glTranslated(0, 2, 0);
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1, 0.8, 0, 0.5);
	glutSolidSphere(0.1, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPushMatrix();
	glScalef(0.1, 3, 0.1);
	glutSolidCube(1);
	glPopMatrix();
	glTranslated(0, 2, 0);
	glScalef(1, 2, 1);
	glColor3f(1, 1, 1);
	glutWireCube(0.5);
	glPushMatrix();
	glTranslated(0, -0.10, 0);
	glScalef(0.35, 0.35, 0.35);
	glBegin(GL_TRIANGLES);	
	glNormal3f(0, 1, 1);
	glVertex3f(-1, 1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(0, 1.5, 0);	
	glNormal3f(1, 1, 0);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glVertex3f(0, 1.5, 0);	
	glNormal3f(0, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(0, 1.5, 0);	
	glNormal3f(-1, 1, 0);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glVertex3f(0, 1.5, 0);	
	glEnd();
	glPopMatrix();
	
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