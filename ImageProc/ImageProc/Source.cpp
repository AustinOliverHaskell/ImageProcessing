#include "CImg.h"
#include <iostream>
#include <string>
#include "KernelFunctions.h"
#include "Defs.h"

using namespace cimg_library;

int main() {

	// Open image
	CImg <unsigned char> image("flower.jpg");

	applySobel(image);

	// Create two displays (Windows)
	CImgDisplay main_disp(image, "Stenography");

	// Check to make sure that the displays arnt closed, if so then our porgram will end
	while (!main_disp.is_closed()) {}

	image.save("result.jpg");

	// End
	return 0;
}