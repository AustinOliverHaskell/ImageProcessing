#pragma once
#include <string>
#include "Defs.h"
#include "CImg.h"

using namespace cimg_library;

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
	void shiftColor(uint shift, uint tolerance, enum Colors color);
	void grabChannel(enum Colors color, std::string filename);
	void removeColor(enum Colors color);
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
