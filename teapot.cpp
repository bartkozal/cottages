/*
 *  teapot.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 08/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include "teapot.h"

Teapot::Teapot() {
	this->draw();
}

void Teapot::draw() {
	glPushMatrix();

	glColor3f(0, 1, 0);
	glTranslatef(0, 1, 0);
	glutSolidTeapot(1);
	
	glPopMatrix();
	glFlush();
}