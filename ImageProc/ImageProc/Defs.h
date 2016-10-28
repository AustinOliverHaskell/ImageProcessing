#pragma once
enum Colors
{
	RED = 0,
	GREEN,
	BLUE
};

const unsigned char average[9] = {
	1, 1, 1,
	1, 1, 1,
	1, 1, 1
};

const unsigned char sharpen[9] = {
	0, -1, 0,
	-1, 5, -1,
	0, -1, 0
};

const unsigned char identity[9] = {
	0, 0, 0,
	0, 1, 0,
	0, 0, 0
};

