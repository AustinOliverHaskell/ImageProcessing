#pragma once

#include <vector>

using namespace std;

enum Colors
{
	RED = 0,
	GREEN,
	BLUE
};

const int STANDARD_DIMENTIONS = 3;
const int LARGE_DIMENTIONS = 5;

const unsigned char average[3][3] = {
	{1, 1, 1},
	{1, 1, 1},
	{1, 1, 1}
};

const unsigned char gaussian[3][3] = {
	{2, 4, 2},
	{4, 8, 4},
	{2, 4, 2}
};

const unsigned char sharpen[3][3] = {
	{0, -1, 0},
	{-1, 5, -1},
	{0, -1, 0 }
};

const unsigned char identity[3][3] = {
	{0, 0, 0},
	{0, 1, 0},
	{0, 0, 0}
};

const unsigned char emboss[3][3] = {
	{-2 , -1, 0},
	{-1,   1, 1},
	{ 0,   1, 2}
};

const unsigned char unique[3][3] = {
	{0, 1, 2},
	{0, 1, 2},
	{0, 1, 2}
};

const unsigned char largeGaussian[5][5] = {
	{0, 1, 2, 1, 0},
	{1, 2, 4, 2, 1},
	{2, 4, 8, 4, 2},
	{1, 2, 4, 2, 1},
	{0, 1, 2, 1, 0}
};