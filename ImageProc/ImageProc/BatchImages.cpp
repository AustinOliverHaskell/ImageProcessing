#include "BatchImages.h"

using namespace cimg_library;

// Constructors/Destructors
// -----------------------------------------------------------------------------------------------------------------------
BatchImages::BatchImages()
{

}
BatchImages::BatchImages(std::string in, std::string out)
{
	inputFolder = in;
	outputFolder = out;
}
BatchImages::~BatchImages()
{

}

// Setters/Getters
// -----------------------------------------------------------------------------------------------------------------------
void BatchImages::setOutputFolder(std::string out)
{
	outputFolder = out;
}
void BatchImages::setInputFolder(std::string in)
{
	inputFolder = in;
}
