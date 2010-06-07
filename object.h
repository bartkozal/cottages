/*
 *  object.h
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#ifndef OBJECT
#define OBJECT

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "imageloader.h"

class Object {
	
protected:
	
	virtual GLuint load_texture(const char *name);
	
private:
	
	GLuint load_texture_from_image(Image* image);
	
};

#endif