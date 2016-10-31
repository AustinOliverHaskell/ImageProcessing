#include <iostream>
#include <cmath>
#include <random>
#include <vector>
#include "CImg.h"
#include "KernelFunctions.h"
#include "Defs.h"

using namespace cimg_library;


// Baisc Color stuff
// --------------------------------------------------------------------------------------------------------------------------------------------------------------
void shiftColor(CImg <unsigned char> &image, unsigned int shift, unsigned int tolerance, enum Colors color)
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
void grabChannel(const CImg <unsigned char> &image, enum Colors color, std::string filename)
{
	// Will seperate the color into a new image of same dimentions
	CImg <unsigned char> retVal(image.width(), image.height(), image.depth(), image.spectrum());

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
void removeColor(CImg <unsigned char> &image, enum Colors color)
{
	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			image(x, y, 0, color) = 0;
		}
	}
}
void makeGreyscale(CImg <unsigned char> &image)
{
	CImg <unsigned char> greyScale(image.width(), image.height(), image.depth(), 1);

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			greyScale(x, y, 0, 0) = (0.21*(image(x, y, 0, RED)) + (0.72*image(x, y, 0, BLUE)) + (0.07*image(x, y, 0, GREEN))) / 3;
		}
	}

	image = greyScale;
}

// Kernel Convolution
// --------------------------------------------------------------------------------------------------------------------------------------------------------------
void applyKernel(CImg <unsigned char> &image, const unsigned char kernel[STANDARD_DIMENTIONS][STANDARD_DIMENTIONS], int devisor)
{
	/* Sudo code - curtesy of Wikipedia
	for each image row in input image:
		for each pixel in image row:

		set accumulator to zero

			for each kernel row in kernel:
				for each element in kernel row:

					if element position  corresponding* to pixel position then
					multiply element value  corresponding* to pixel value
					add result to accumulator
				endif

		set output image pixel to accumulator


	*/

	CImg <unsigned char> duplicate(image);

	for (int i = 0; i < image.spectrum(); i++)
	{
		applyKernelOnChannel(duplicate, kernel, devisor, i);
	}

	image = duplicate;
}
void applyLargeKernel(CImg <unsigned char> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor)
{
	for (int i = 0; i < image.spectrum(); i++)
	{
		applyLargeKernelOnChannel(image, kernel, devisor, i);
	}
}
void applyLargeKernelOnChannel(CImg <unsigned char> &image, const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS], int devisor, int channel)
{
	CImg <unsigned char> duplicate(image);

	// Starting at one and going to the height/width -dimentionOfKernel will keep us in bounds of the image
	for (int y = 2; y < image.height() - LARGE_DIMENTIONS; y++)
	{
		for (int x = 2; x < image.width() - LARGE_DIMENTIONS; x++)
		{
			int total = 0;

			for (int kr = -2; kr < LARGE_DIMENTIONS - 2; kr++)
			{
				for (int ke = -2; ke < LARGE_DIMENTIONS - 2; ke++)
				{
					total += (int)image(x + ke, y + kr, 0, channel) * kernel[ke + 2][kr + 2];
				}
			}

			total /= devisor;
			duplicate(x, y, 0, channel) = (unsigned char)total;
		}
	}

	duplicate.normalize(240, 250);
	image = duplicate;
}
void applyKernelOnChannel(CImg <unsigned char> & image, const unsigned char kernel[STANDARD_DIMENTIONS][STANDARD_DIMENTIONS], int devisor, int channel)
{
	CImg <unsigned char> duplicate(image);

	// Starting at one and going to the height/width -dimentionOfKernel will keep us in bounds of the image
	for (int y = 1; y < image.height() - STANDARD_DIMENTIONS; y++)
	{
		for (int x = 1; x < image.width() - STANDARD_DIMENTIONS; x++)
		{
			int total = 0;

			for (int kr = -1; kr < STANDARD_DIMENTIONS - 1; kr++)
			{
				for (int ke = -1; ke < STANDARD_DIMENTIONS - 1; ke++)
				{
					total += (int)image(x + ke, y + kr, 0, channel)   * kernel[kr + 1][ke + 1];
				}
			}

			total /= devisor;

			duplicate(x, y, 0, channel) = (unsigned char)total;
		}
	}

	image = duplicate;
}
void applySobel(CImg <unsigned char> &image)
{
	CImg <unsigned char> duplicate(image);

	applyLargeKernel(duplicate, intenseGaussian, totalKernel(intenseGaussian));
	makeGreyscale(duplicate);

	CImg <unsigned char> X(duplicate);
	CImg <unsigned char> Y(duplicate);

	applyKernel(X, Gx, 1);
	applyKernel(Y, Gy, 1);

	CImgDisplay main_disp(X, "GX");
	CImgDisplay second_disp(Y, "GY");

	// Check to make sure that the displays arnt closed, if so then our porgram will end
	while (!main_disp.is_closed()) {}

	for (int y = 0; y < duplicate.height(); y++)
	{
		for (int x = 0; x < duplicate.width(); x++)
		{
			duplicate(x, y, 0, GREYSCALE) = (unsigned char)sqrt(pow(X(x, y, 0, GREYSCALE), 2) + pow(Y(x, y, 0, GREYSCALE), 2));
		}
	}

	image = duplicate;
}

// Utility
// -------------------------------------------------------------------------------------------------------------------------------
int totalKernel(const unsigned char kernel[LARGE_DIMENTIONS][LARGE_DIMENTIONS])
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