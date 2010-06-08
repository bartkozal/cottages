/*
 *  lamp.h
 *  cottages
 *
 *  Created by Bartlomiej Kozal on 08/06/2010.
 *  Copyright 2010 Bartlomiej Kozal. All rights reserved.
 *
 */

#ifndef LAMP
#define LAMP

#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include "object.h"

class Lamp : private Object {
	
public:
	
	Lamp();
	void draw();
	
};

#endif