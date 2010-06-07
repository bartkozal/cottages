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

class Cottage : private Object {
	
public:
	
	Cottage();
	
private:
	
	GLuint texture_wall, texture_roof;
	
	void draw();	
	void load_textures();	
	void draw_roof();	
	void draw_walls();

};

#endif