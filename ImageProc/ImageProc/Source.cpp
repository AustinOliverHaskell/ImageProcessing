#include "CImg.h"
#include <iostream>
#include <string>
#include "Defs.h"
#include "Image.h"

using namespace cimg_library;

int main() {

	Image img("Bat.jpg");

	img.scale(0.25, LINEAR);

	img.display();

	// End
	return 0;
}