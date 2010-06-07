/*
 *  object.cpp
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "imageloader.h"
#include "object.h"


class Object {
	
protected:
	
	virtual GLuint load_texture(const char *name) {
		Image *texture_image = loadBMP(name);
		GLuint texture = this->load_texture_from_image(texture_image);
		delete texture_image;
		return texture;
	}
	
private:
	
	GLuint load_texture_from_image(Image* image) {
		GLuint texture_id;
		glGenTextures(1, &texture_id);
		glBindTexture(GL_TEXTURE_2D, texture_id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->width, image->height, 
					 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
		return texture_id;
	}
	
};
