/*
 *  cottage.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <string.h>
#include "object.cpp"

class Cottage : private Object {
	
public:
	
	Cottage() {
		this->draw();
	}
	
private:
	
	GLuint texture_wall, texture_roof;
	
	void draw() {
		glPushMatrix();
		glScaled(0.8, 0.8, 1.1);
		this->load_textures();
		this->draw_roof();
		this->draw_walls();
		glPopMatrix();
		glFlush();
	}
	
	void load_textures() {
		texture_roof = this->load_texture("roof.bmp");
		texture_wall = this->load_texture("wall.bmp");
	}
	
	void draw_roof() {
		glBindTexture(GL_TEXTURE_2D, texture_roof);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1, 1, 1);
		
		glBegin(GL_TRIANGLES);
		
		glTexCoord2f(0, 0);
		glVertex3f(-1, 1, 1);
		glTexCoord2f(5, 0);
		glVertex3f(1, 1, 1);
		glTexCoord2f(2.5, 5);
		glVertex3f(0, 2, 0);
		
		glTexCoord2f(0, 0);
		glVertex3f(1, 1, 1);
		glTexCoord2f(5, 0);
		glVertex3f(1, 1, -1);
		glTexCoord2f(2.5, 5);
		glVertex3f(0, 2, 0);
		
		glTexCoord2f(0, 0);
		glVertex3f(1, 1, -1);
		glTexCoord2f(5, 0);
		glVertex3f(-1, 1, -1);
		glTexCoord2f(2.5, 5);
		glVertex3f(0, 2, 0);
		
		glTexCoord2f(0, 0);
		glVertex3f(-1, 1, -1);
		glTexCoord2f(5, 0);
		glVertex3f(-1, 1, 1);
		glTexCoord2f(2.5, 5);
		glVertex3f(0, 2, 0);
		
		glEnd();
	}
	
	void draw_walls() {
		
		glBindTexture(GL_TEXTURE_2D, texture_wall);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glColor3f(1, 1, 1);
		
		glBegin(GL_QUADS);
		
		glTexCoord2f(0, 0);
		glVertex3f(-1, 0, 1);
		glTexCoord2f(1, 0);
		glVertex3f(1, 0, 1);
		glTexCoord2f(1, 1);
		glVertex3f(1, 1, 1);
		glTexCoord2f(0, 1);
		glVertex3f(-1, 1, 1);
		
		glTexCoord2f(0, 0);
		glVertex3f(1, 0, 1);
		glTexCoord2f(1, 0);
		glVertex3f(1, 0, -1);
		glTexCoord2f(1, 1);
		glVertex3f(1, 1, -1);
		glTexCoord2f(0, 1);
		glVertex3f(1, 1, 1);
		
		glTexCoord2f(0, 0);
		glVertex3f(1, 0, -1);
		glTexCoord2f(1, 0);
		glVertex3f(-1, 0, -1);
		glTexCoord2f(1, 1);
		glVertex3f(-1, 1, -1);
		glTexCoord2f(0, 1);
		glVertex3f(1, 1, -1);
		
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
	
};