/*
 *  ground.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "object.cpp"

class Ground : private Object {
	
public:
	
	Ground() {}
	
	Ground(int red, int green, int blue) {
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->draw();
	}
	
	
private:
	
	int red, green, blue;
	GLuint texture_ground;
	
	void draw() {
		glPushMatrix();
		glEnable(GL_TEXTURE_2D);
		texture_ground = this->load_texture("ground.bmp");
		this->draw_ground();
		glDisable(GL_TEXTURE_2D);
		glPopMatrix();
		glFlush();
	}
	
	void draw_ground() {
		glBindTexture(GL_TEXTURE_2D, texture_ground);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(red, green, blue);
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(0, 0);
		glVertex3f(-100, 0, -100);
		glTexCoord2f(0, 100);
		glVertex3f(-100, 0, 10);
		glTexCoord2f(100, 100);
		glVertex3f(100, 0, 100);
		glTexCoord2f(100, 0);
		glVertex3f(100, 0, -100);
		
		glEnd();
	}
	
};