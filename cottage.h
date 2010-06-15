/*
 *  cottage.h
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#ifndef COTTAGE
#define COTTAGE

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "object.h"

class Cottage : private Object {
	
public:
	
	Cottage();
	void draw(bool texture_switch, bool texture_linear);
	
private:
	
	GLuint texture_wall, texture_roof;
		
	void load_textures();	
	void draw_roof(bool texture_linear);	
	void draw_walls(bool texture_linear);

};

#endif