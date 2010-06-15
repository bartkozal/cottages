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
	
void Ground::draw(bool texture_switch, bool texture_linear) {
	
	glPushMatrix();
	
	float mat_ambient[] = {this->red, this->green, this->blue};
	float mat_diffuse[] = {0.5, 0.5, 0.5, 1};
	float mat_specular[] = {0, 0, 0, 0};
	float high_shininess[] = {0};
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient); 
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse); 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	
	if (texture_switch == true) {
		glEnable(GL_TEXTURE_2D);
	}
	
	glBindTexture(GL_TEXTURE_2D, this->texture_ground);

	if (texture_linear == true) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexGeni(GL_S,GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
	
	glPushMatrix();
	GLUquadricObj * su = gluNewQuadric();
	glRotatef(-90, 1, 0, 0);
	gluDisk(su, 0, 100, 50, 50);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}

void Ground::set_color(float red, float green, float blue) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->draw(true, true);
}