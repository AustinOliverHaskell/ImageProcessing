#pragma once
#include "CImg.h"
#include <iostream>

using namespace cimg_library;



void shiftColor(CImg <unsigned char> &image, unsigned int shift, unsigned int tolerance, enum Colors color);
void grabChannel(const CImg <unsigned char> &image, enum Colors color, std::string filename);
void removeColor(CImg <unsigned char> &image, enum Colors color);

// Blurs
void averageBlur(CImg <unsigned char> &image, float magnitude);
void applyKernel(CImg <unsigned char> &image, const unsigned char* kernel, unsigned int kernelSize);


