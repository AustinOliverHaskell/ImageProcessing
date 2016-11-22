#pragma once
#include <string>
#include "Defs.h"
#include "CImg.h"

using namespace cimg_library;

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

// Class to handle the edge detection proccesing
class Image
{
public:
	Image(std::string imagePath, std::string savePath = "result.jpg");
	~Image();

	// Colors
	// -------------------------------
	void makeGreyscale();
	void filterNoise(int threshold);
	void grabChannel(enum Colors color, std::string filename);
	void removeColor(enum Colors color);
	void shiftColor(uint shift, uint tolerance, enum Colors color);

	// Filters
	// -------------------------------
	void applySobel();
	void applyCanny();
	
	// Utility
	// -------------------------------
	void display();
	void display(std::string title); // Display with set title

private:
	CImg <Image_t> image;
	std::string outputPath;

	// Colors
	// -------------------------------
	void makeGreyscale(CImg <Image_t> &img);

	// Utility
	// -------------------------------
	int totalKernel(const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS]);
	unsigned char reduceIntToChar(int val);
	void commitChange(CImg <Image_t> &target, const CImg <Image_t> &source, uint channel);

	// Kernel Convolution
	// -------------------------------
	void applySobelKernel(CImg <Image_t> &img);
	void applyKernel(CImg <Image_t> &img, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor);
	void applyKernelOnChannel(CImg <Image_t> &img, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor, int channel);

};
