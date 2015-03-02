/*! \file main.cpp: main function for complex number calculator */
#include <Image.h>
#include <Tools.h>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
#include <fstream>

int main(int argc, char* argv[])
{
	bool debug = false;
	Image img;
	if(argc > 3 || argc < 3) {
		cerr << "Improper number of args, should be 3 but is " << argc << "!" << endl;
		return -1;
	}
	string input(argv[1]);
	if(input.compare("print") == 0) {
		//This means we are using pa2 to print an image
		img.parseFile(argv[2]);	
		img.printImage();
		return -1;	
	}

	int imgResult = img.parseFile(argv[1]);	
	if(imgResult < 0) {
		
		if(debug) cerr << "image Read failed, returned code " << imgResult << endl;
		if(imgResult == -2) cerr << "First element is NOT P2!" << endl;
		else if(imgResult == -3) cerr << "Height / Width are not Positive Integers!" << endl;
		else if(imgResult == -4) cerr << "MaxPixelValue found is not valid!" << endl;
		else if(imgResult == -5) cerr << "one of the pixel values found is INVALID!" << endl;
		else if(imgResult == -6) cerr << "All pixels are same value! max = min!" << endl;
		else if(imgResult == -7) cerr << "file permissions issues, cannot write to file!" 
						<< endl;
		else if(imgResult == -8) cerr << "Error with height / width" << endl;

		return -1;
	}

	//Img should be safely read at this point
	Tools tools;
	
	Image scaledImage = tools.scaleImage(img);

	int toolResult = tools.writeImageToFile(scaledImage, argv[2]);

	//img.printImage();
	//cout << "returning " << result;
	if(scaledImage.goodImage == false || toolResult < 0) {
		return -1;
	}
	//Succes case
	return 0;
}


