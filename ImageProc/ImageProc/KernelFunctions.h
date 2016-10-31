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
void applyKernel(CImg <unsigned char> &image, const unsigned char kernel[STANDARD_DIMENTIONS][STANDARD_DIMENTIONS], int devisor);
void applyLargeKernel(CImg <unsigned char> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor);
void applySobel(CImg <unsigned char> &image);
void applyLargeKernelOnChannel(CImg <unsigned char> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor, int channel);
void applyKernelOnChannel(CImg <unsigned char> & image, const unsigned char kernel[STANDARD_DIMENTIONS][STANDARD_DIMENTIONS], int devisor, int channel);

// Utility
// -------------------------------------------------------------------------------------------------------------------------------
int totalKernel(const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS]);