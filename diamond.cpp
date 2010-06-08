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
	
	glColor3f(0, 0, 1);
	glTranslatef(0, 1, 0);
	glutSolidOctahedron();
	
	glPopMatrix();
	glFlush();
}