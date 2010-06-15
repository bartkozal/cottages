/*
 *  cottage.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include "cottage.h"

Cottage::Cottage() {
	this->load_textures();
}

void Cottage::draw(bool texture_switch, bool texture_linear) {
	glPushMatrix();
	glScaled(0.8, 0.8, 1.1);
	
	float mat_ambient[] = {0.10, 0.05, 0.11, 1};
	float mat_diffuse[] = {0.42, 0.47, 0.54, 1};
	float mat_specular[] = {0.33, 0.33, 0.52, 1};
	float high_shininess[] = {9.84};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	if (texture_switch == true) {
		glEnable(GL_TEXTURE_2D);
	}
	this->draw_roof(texture_linear);
	this->draw_walls(texture_linear);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glFlush();
}

void Cottage::load_textures() {
	texture_roof = this->load_texture("roof.bmp");
	texture_wall = this->load_texture("wall.bmp");
}

void Cottage::draw_roof(bool texture_linear) {
	glBindTexture(GL_TEXTURE_2D, texture_roof);
	if (texture_linear == true) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glColor3f(1, 1, 1);
	
	glBegin(GL_TRIANGLES);
	
	glNormal3f(0, 1, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(5, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(2.5, 5);
	glVertex3f(0, 2, 0);

	glNormal3f(1, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, 1);
	glTexCoord2f(5, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(2.5, 5);
	glVertex3f(0, 2, 0);
	
	glNormal3f(0, 1, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 1, -1);
	glTexCoord2f(5, 0);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(2.5, 5);
	glVertex3f(0, 2, 0);

	glNormal3f(-1, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(5, 0);
	glVertex3f(-1, 1, 1);
	glTexCoord2f(2.5, 5);
	glVertex3f(0, 2, 0);
	
	glEnd();
}

void Cottage::draw_walls(bool texture_linear) {
	
	glBindTexture(GL_TEXTURE_2D, texture_wall);
	if (texture_linear == true) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	glColor3f(1, 1, 1);
	
	glBegin(GL_QUADS);
	
	glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, 1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 1);

	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(1, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(1, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, 1);
	
	glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3f(1, 0, -1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(1, 1, -1);
	
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-1, 0, 1);
	glTexCoord2f(1, 0);
	glVertex3f(-1, 0, -1);
	glTexCoord2f(1, 1);
	glVertex3f(-1, 1, -1);
	glTexCoord2f(0, 1);
	glVertex3f(-1, 1, 1);
	
	glEnd();
}
