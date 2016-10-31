#pragma once
#include "CImg.h"
#include "Defs.h"
#include <iostream>
#include <vector>

using namespace cimg_library;

// Colors
// -------------------------------------------------------------------------------------------------------------------------------
void shiftColor(CImg <unsigned char> &image, unsigned int shift, unsigned int tolerance, enum Colors color);
void grabChannel(const CImg <unsigned char> &image, enum Colors color, std::string filename);
void removeColor(CImg <unsigned char> &image, enum Colors color);
void makeGreyscale(CImg <unsigned char> &image);

// Blurs
// -------------------------------------------------------------------------------------------------------------------------------
void averageBlur(CImg <unsigned char> &image, float magnitude);
void applyKernel(CImg <unsigned char> &image, const unsigned char kernel[STANDARD_DIMENTIONS][STANDARD_DIMENTIONS], int devisor);
void applyLargeKernel(CImg <unsigned char> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor);


// Maths
// -------------------------------------------------------------------------------------------------------------------------------
std::vector <std::vector <unsigned char>> MatrixSD(int intensity, int width);

// Utility
// -------------------------------------------------------------------------------------------------------------------------------
