#include <iostream>
#include <cmath>
#include "CImg.h"
#include "KernelFunctions.h"
#include "Defs.h"

using namespace cimg_library;

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

void averageBlur(CImg <unsigned char> &image, float magnitude)
{
	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			// Not on an edge
			if ((y != 0 && y != (image.height() - 1)) &&
			    (x != 0 && x != (image.width()  - 1)))
			{
				int red = 0;
				int green = 0;
				int blue = 0;

				// Gather adjacent pixels
				for (int i = -1; i <= 1; i++)
				{
					for (int k = -1; k <= 1; k++)
					{
						red += (int)image(x + k, y + i, 0, RED) * magnitude;
						green += (int)image(x + k, y + i, 0, GREEN) * magnitude;
						blue += (int)image(x + k, y + i, 0, BLUE) * magnitude;
					}
				}

				red = red / 9;
				green = green / 9;
				blue = blue / 9;

				image(x, y, 0, RED) = (unsigned char)red;
				image(x, y, 0, GREEN) = (unsigned char)green;
				image(x, y, 0, BLUE) = (unsigned char)blue;

			}
		}
	}
}
void applyKernel(CImg <unsigned char> &image, const unsigned char* kernel, unsigned int kernelSize)
{
	/*
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

	int dimentionOfKernel = sqrt(kernelSize);

	// Starting at one and going to the height/width -dimentionOfKernel will keep us in bounds of the image
	for (int y = 1; y < image.height()- dimentionOfKernel; y++)
	{
		for (int x = 1; x < image.width()- dimentionOfKernel; x++)
		{
			int red = 0;
			int green = 0;
			int blue = 0;

			for (int kr = 0; kr < dimentionOfKernel; kr++)
			{
				for (int ke = 0; ke < dimentionOfKernel; ke++)
				{
					red += (int)image(x + ke, y + kr, 0, RED) * kernel[kr*ke];
					green += (int)image(x + ke, y + kr, 0, GREEN) * kernel[kr*ke];
					blue += (int)image(x + ke, y + kr, 0, BLUE) * kernel[kr*ke];
				}
			}


			image(x, y, 0, RED) = (unsigned char)red;
			image(x, y, 0, GREEN) = (unsigned char)green;
			image(x, y, 0, BLUE) = (unsigned char)blue;
		}
	}
}

