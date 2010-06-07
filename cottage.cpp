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
#include "imageloader.h"

class cottage {
	
public:
	
	cottage() {
		this->draw();
	}
	
	~cottage() {}
	
	GLuint texture_wall, texture_roof;
	
private:
	
	GLuint loadTexture(Image* image) {
		GLuint textureId;
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
					 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		return textureId;
	}
	
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
		Image *texture1 = loadBMP("wall.bmp");
		this->texture_wall = this->loadTexture(texture1);
		delete texture1;
		
		Image *texture2 = loadBMP("roof.bmp");
		this->texture_roof = this->loadTexture(texture2);
		delete texture2;
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