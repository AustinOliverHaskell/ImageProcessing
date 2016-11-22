#include <iostream>
#include <cmath>
#include <omp.h>
#include <random>
#include <vector>
#include <string>
#include "CImg.h"
#include "Image.h"
#include "Defs.h"
#include "assert.h"

using namespace cimg_library;

// Constructor/Destructor
// --------------------------------------------------------------------------------------------------------------------------------------------------------------
Image::Image(std::string imagePath, std::string savePath)
{
	// Create image with the default constructor
	CImg <Image_t> init(imagePath.c_str());

	image = init;

	// Save the path to save to
	outputPath = savePath;
}
Image::~Image()
{
	// Save the image
	image.save(outputPath.c_str());
}

// Baisc Color stuff
// --------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::shiftColor(uint shift, uint tolerance, enum Colors color)
{
	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			if (image(x, y, 0, color) > tolerance)
			{
				image(x, y, 0, color) += shift;
			}
		}
	}
}
void Image::grabChannel(enum Colors color, std::string filename)
{
	// Will seperate the color into a new image of same dimentions
	CImg <Image_t> retVal(image.width(), image.height(), image.depth(), image.spectrum());

	std::cout << "Image Depth: " << image.spectrum() << std::endl;

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			retVal(x, y, 0, color) = image(x, y, 0, color);
		}
	}

	//retVal.fill(100);
	retVal.save(filename.c_str());
}
void Image::removeColor(enum Colors color)
{
	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			image(x, y, 0, color) = 0;
		}
	}
}
void Image::makeGreyscale()
{
	CImg <Image_t> greyScale(image.width(), image.height(), image.depth(), 1);

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			greyScale(x, y, 0, 0) = (image(x, y, 0, RED) + image(x, y, 0, BLUE) + image(x, y, 0, GREEN)) / 3;
		}
	}

	image = greyScale;
}
void Image::makeGreyscale(CImg <Image_t> &img)
{
	CImg <Image_t> greyScale(img.width(), img.height(), img.depth(), 1);

	for (int y = 0; y < img.height(); y++)
	{
		for (int x = 0; x < img.width(); x++)
		{
			greyScale(x, y, 0, 0) = (img(x, y, 0, RED) + img(x, y, 0, BLUE) + img(x, y, 0, GREEN)) / 3;
		}
	}

	img = greyScale;
}
void Image::filterNoise(int threshold)
{
	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			if (image(x, y, 0, GREYSCALE) < threshold)
			{
				image(x, y, 0, GREYSCALE) = 0;
			}
		}
	}
}

// Kernel Convolution
// --------------------------------------------------------------------------------------------------------------------------------------------------------------
void Image::applyKernel(CImg <Image_t> &img, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor)
{
    #pragma omp parallel for
	for (int i = 0; i < img.spectrum(); i++)
	{
		// Apply the kernel to each channel
		applyKernelOnChannel(img, kernel, devisor, i);
	}
}
void Image::applyKernelOnChannel(CImg <Image_t> &img, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor, int channel)
{
	CImg <Image_t> duplicate(img);

	// Starting at one and going to the height/width -dimentionOfKernel will keep us in bounds of the image
	// Not Optimized
	for (int y = 2; y < img.height() - 2; y++)
	{
		for (int x = 2; x < img.width() - 2; x++)
		{
			int total = 0;

			for (int kr = -2; kr <= 2; kr++)
			{
				for (int ke = -2; ke <= 2; ke++)
				{
					total += (img(x + ke, y + kr, 0, channel) * kernel[ke + 2][kr + 2]);
				}
			}
			// Divide, some kernels (like gaussian have to be divided by the total)
			total /= devisor;

			// reduceIntToChar should keep overflows in check
			duplicate(x, y, 0, channel) = (Image_t)total;
		}
	}

	#pragma omp critical
	{
		commitChange(img, duplicate, channel);
	}
}
void Image::applySobelKernel(CImg <Image_t> &img)
{
	// Optimization
	// N(x,y) = Sum of { K(i,j).P(x-i,y-j)}

	CImg <Image_t> duplicate(img);

	// Starting at one and going to the height/width -1 will keep us in bounds of the image
	for (int y = 1; y < img.height() - 1; y++)
	{
		for (int x = 1; x < img.width() - 1; x++)
		{
			int totalX = 0;
			int totalY = 0;

			for (int i = -1; i <= 1; i++)
			{
				for (int q = -1; q <= 1; q++)
				{
					totalX += img(x + q, y + i, 0, 0) * Gx[q + 1][i + 1];
					totalY += img(x + q, y + i, 0, 0) * Gy[q + 1][i + 1];

				}
			}

			duplicate(x, y, 0, 0) = sqrt(abs(pow(totalX, 2) + pow(totalY, 2)));
		}
	}

	img = duplicate;
}
void Image::applySobel()
{
	// Make a duplicate
	CImg <Image_t> duplicate(image);

	// Blur to reduce noise
	applyKernel(duplicate, intenseGaussian, 100);

	// Make it greyscale
	makeGreyscale(duplicate);

	applySobelKernel(duplicate);

	image = duplicate;
}
void Image::applyCanny()
{

}

// Utility
// -------------------------------------------------------------------------------------------------------------------------------
int Image::totalKernel(const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS])
{
	int retVal = 0;

	for (int y = 0; y < LARGE_DIMENTIONS; y++)
	{
		for (int x = 0; x < LARGE_DIMENTIONS; x++)
		{
			retVal += kernel[x][y];
		}
	}

	return retVal;
}
unsigned char Image::reduceIntToChar(int val)
{
	return (unsigned char)val;
}
void Image::commitChange(CImg <Image_t> &target, const CImg <Image_t> &source, uint channel)
{
	for (uint y = 0; y < target.height(); y++)
	{
		for (uint x = 0; x < target.width(); x++)
		{
			target(x, y, 0, channel) = source(x, y, 0, channel);
		}
	}
}
void Image::display()
{
	CImgDisplay main_disp(image, "Display");

	while (!main_disp.is_closed());

}
void Image::display(std::string title)
{
	CImgDisplay main_disp(image, title.c_str());

	while (!main_disp.is_closed());
}

