#include "CImg.h"
using namespace cimg_library;

int main() {

	// Open image
	CImg<unsigned char> image("Bat.jpg");

	// Tutorial from the CImg library website
	int width = image.width();
	int height = image.height();
	int size = image.size();

	// Image functions (Basic)
	// image.blur(2.5);
	// Blur on axis
	// image.blur(0, 1); 
	// image.noise(12);
	
	
	// Create two displays (Windows)
	CImgDisplay main_disp(image, "Stenography");


	// Check to make sure that the displays arnt closed, if so then our porgram will end
	while (!main_disp.is_closed()) 
	{
		cimg_for(image, ptr, unsigned char)
		{ 
			*ptr = 0; 
		}       
	}

	// End
	return 0;
}
