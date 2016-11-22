#pragma once

using namespace std;

// Shorthand 
typedef unsigned int uint;

// Type used by images and for casting to correct pixel data types
typedef unsigned char Image_t;

// Channel Colors including greyscale
enum Colors
{
	GREYSCALE = 0,
	RED = 0,
	GREEN,
	BLUE
};