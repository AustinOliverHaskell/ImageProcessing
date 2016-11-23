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

enum ScalingModes
{
	LINEAR,
	BILINEAR,
	NEAREST
};

// Standard dimentions for most 3x3 arrays
const int STANDARD_DIMENTIONS = 3;

// Larger arrays 
const int LARGE_DIMENTIONS = 5;

// Average blur
const unsigned char average[3][3] = {
	{ 1, 1, 1 },
	{ 1, 1, 1 },
	{ 1, 1, 1 }
};

// Gaussian Blur 3x3
const unsigned char gaussian[3][3] = {
	{ 2, 4, 2 },
	{ 4, 8, 4 },
	{ 2, 4, 2 }
};

// Sharpen Filter
const unsigned char sharpen[3][3] = {
	{ 0, -1, 0 },
	{ -1, 5, -1 },
	{ 0, -1, 0 }
};

// Identity Filter
const unsigned char identity[3][3] = {
	{ 0, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 0 }
};

// Emboss Filter
const unsigned char emboss[3][3] = {
	{ -2 , -1, 0 },
	{ -1,   1, 1 },
	{ 0,   1, 2 }
};

// 5x5 Gaussian
const unsigned char largeGaussian[5][5] = {
	{ 0, 1, 2, 1, 0 },
	{ 1, 2, 4, 2, 1 },
	{ 2, 4, 8, 4, 2 },
	{ 1, 2, 4, 2, 1 },
	{ 0, 1, 2, 1, 0 }
};

// 5x5 gaussian with a heigher distribution
const unsigned char intenseGaussian[5][5] = {
	{ 1, 2,  4, 2, 1 },
	{ 2, 4,  8, 4, 2 },
	{ 4, 8, 16, 8, 4 },
	{ 2, 4,  8, 4, 2 },
	{ 1, 2,  4, 2, 1 }
};

// Sobel X
const char Gx[3][3] = {
	{ -1 , 0, 1 },
	{ -2,  0, 2 },
	{ -1,  0, 1 }
};

// Sobel Y
const char Gy[3][3] = {
	{ 1,  2,  1 },
	{ 0,  0,  0 },
	{ -1, -2, -1 }
};