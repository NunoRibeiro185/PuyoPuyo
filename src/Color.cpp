#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Color.h"



/**
    Return a random color

    @param void
    @return A random color in HEX (Integet).
*/
Color::Color(){
	int color;

	srand (time(0));
	srand (time(0));
	color = rand() % 4;
	
	switch (color)
	{
	case 0: //RED
		r = 255;
		g = 0;
		b = 0;
		break;
	case 1: //Yellow
		r = 255;
		g = 255;
		b = 0;
		break;
	case 2: //Green
		r = 0;
		g = 204;
		b = 0;
		break;
	case 3: //Blue
		r = 0;
		g = 0;
		b = 153;
		break;
	default:
		break;
	}
}
Color::Color(int r, int g, int b){
	this->r = r;
	this->g = g;
	this->b = b;
}

