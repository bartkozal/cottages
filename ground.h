/*
 *  ground.h
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 07/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#ifndef GROUND
#define GROUND

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "object.h"

class Ground : private Object {
	
public:
	
	Ground();
	Ground(float red, float green, float blue);
	void draw(bool texture_switch, bool texture_linear);
	void set_color(float red, float green, float blue);
	
private:
	
	float red, green, blue;
	GLuint texture_ground;
	
};

#endif