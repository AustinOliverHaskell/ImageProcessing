#include "CImg.h"
#include <iostream>
#include <string>
#include "Defs.h"
#include "Image.h"

using namespace cimg_library;

int main() {

	Image img("momdad.jpg");

	img.applySobel();

	img.display();

	// End
	return 0;
}