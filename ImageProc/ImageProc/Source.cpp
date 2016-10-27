#include "CImg.h"
using namespace cimg_library;

void shiftColor(CImg <unsigned char> &image, unsigned int shift, unsigned int tolerance,enum Colors color);
void grabChannel(const CImg <unsigned char> &image, enum Colors color);

enum Colors
{
	RED = 0,
	GREEN,
	BLUE
};

int main() {

	// Open image
	CImg<unsigned char> image("Bat.jpg");

	// Tutorial from the CImg library website
	int width = image.width();
	int height = image.height();
	int size = image.size();

	grabChannel(image, BLUE);


	shiftColor(image, 10, 0, BLUE);

	// Create two displays (Windows)
	CImgDisplay main_disp(image, "Stenography");


	// Check to make sure that the displays arnt closed, if so then our porgram will end
	while (!main_disp.is_closed())
	{
	}


	// End
	return 0;
}

void shiftColor(CImg <unsigned char> &image, unsigned int shift, unsigned int tolerance,enum Colors color)
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

void grabChannel(const CImg <unsigned char> &image, enum Colors color)
{
	// Will seperate the color into a new image of same dimentions
	CImg <unsigned char> retVal (image.width(), image.height(), image.depth(), image.spectrum());

	for (int y = 0; y < image.height(); y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			retVal(x, y, 0, color) = image(x, y, 0, color);
		}
	}

	//retVal.fill(100);

	retVal.normalize(0, 255);
	retVal.save("channel.jpg");

}

