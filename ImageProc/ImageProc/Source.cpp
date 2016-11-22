#include "CImg.h"
#include <iostream>
#include <string>
#include "KernelFunctions.h"
#include "Defs.h"
#include "Image.h"

using namespace cimg_library;

int main() {

	Image img("Bat.jpg");

	img.applySobel();

	img.display("Bat.jpg");

	// End
	return 0;
}