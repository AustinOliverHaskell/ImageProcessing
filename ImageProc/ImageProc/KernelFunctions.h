#pragma once
#include "CImg.h"
#include "Defs.h"
#include <iostream>
#include <vector>

using namespace cimg_library;

// Colors
// -------------------------------------------------------------------------------------------------------------------------------
void shiftColor(CImg <Image_t> &image, uint shift, uint tolerance, enum Colors color);
void grabChannel(const CImg <Image_t> &image, enum Colors color, std::string filename);
void removeColor(CImg <Image_t> &image, enum Colors color);
void makeGreyscale(CImg <Image_t> &image);
void filterNoise(CImg <Image_t> &image, int threshold);

// Blurs
// -------------------------------------------------------------------------------------------------------------------------------
void applySobelKernel(CImg <Image_t> &image);
void applyKernel(CImg <Image_t> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor);
void applySobel(CImg <Image_t> &image);
void applyKernelOnChannel(CImg <Image_t> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor, int channel);

// Utility
// -------------------------------------------------------------------------------------------------------------------------------
int totalKernel(const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS]);
unsigned char reduceIntToChar(int val);
void commitChange(CImg <Image_t> &target, const CImg <Image_t> &source, uint channel);
unsigned char mapToValidValues(int val);