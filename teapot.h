/*
 *  teapot.h
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 08/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#ifndef TEAPOT
#define TEAPOT

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "object.h"

class Teapot : private Object {
	
public:
	
	Teapot();
	
private:
	
	void draw();
	
};

#endif