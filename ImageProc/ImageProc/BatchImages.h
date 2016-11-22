#pragma once
#include <vector>
#include <string>
#include "CImg.h"
#include "Defs.h"

using namespace cimg_library;

class BatchImages
{
public:
	// ---- Constructors ----
	BatchImages();
	BatchImages(std::string in, std::string out);
	// ---- Destructor ----
	~BatchImages();

	// ---- Setters ----
	void setOutputFolder(std::string out);
	void setInputFolder(std::string in);



private:
	// List of all images that will be processed
	vector <CImg <Image_t>> ImageList;

	// Folder that all the images will be dumped into post proccesing or loaded from
	std::string outputFolder;
	std::string inputFolder;


};