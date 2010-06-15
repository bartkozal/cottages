/*
 *  diamonds.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 08/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include "diamond.h"

Diamond::Diamond() {}

void Diamond::draw() {
	glPushMatrix();
	
	float mat_ambient[] = {0.17, 0.01, 0.01, 0.55};
	float mat_diffuse[] = {0.61, 0.04, 0.04, 0.55};
	float mat_specular[] = {0.72, 0.62, 0.62, 0.55};
	float high_shininess[] = {0.55};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	glColor3f(0, 0, 1);
	glTranslatef(0, 1, 0);
	glutSolidOctahedron();
	
	glPopMatrix();
	glFlush();
}