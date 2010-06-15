/*
 *  ground.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include "ground.h"

Ground::Ground(float red, float green, float blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->texture_ground = this->load_texture("ground.bmp");
}
	
void Ground::draw() {
	
	glPushMatrix();
	
//	float mat_ambient[] = {1, 1, 1, 1};
//	float mat_diffuse[] = {1, 1, 1, 1};
//	float mat_specular[] = {1, 1, 1, 1};
//	float high_shininess[] = {1};
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texture_ground);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glColor3f(this->red, this->green, this->blue);
	
//	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
//	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
//	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex3f(-100, 0, -100);
	glTexCoord2f(0, 100);
	glVertex3f(-100, 0, 100);
	glTexCoord2f(100, 100);
	glVertex3f(100, 0, 100);
	glTexCoord2f(100, 0);
	glVertex3f(100, 0, -100);
	
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
}

void Ground::set_color(float red, float green, float blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->draw();
}