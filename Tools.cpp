#include <Tools.h>




Tools::Tools() {
	debug = false;
	if(debug) cout << "Tools are being created" << endl;
}

//This function will take in an img (making a copy of it) and replace all of its
// pixel values with scaled values, so that all pixels have range of 0-255
Image Tools::scaleImage(Image img) {
	int scaleTo = 255;
	//Walk through each pixel in img vector and replace oldValue with newValue
	// newValue = (255 - (oldValue - img.min)) / (img.max - img.min)
	for(unsigned int i = 0; i < img.mainData.size(); i++) {

		
		int intNewValue = scalePixel(img.mainData.at(i), img.min, img.max, scaleTo);
		if(debug) cout << "Scaling origPixel(" << img.mainData.at(i) 
				<< ") -> (" << scaleTo << " * (" << img.mainData.at(i)
				<< " - " << img.min << ")) / (" << img.max << " - " 
				<< img.min << ") = " << intNewValue << endl;
		
		img.mainData.at(i) = intNewValue;	
		
	}
	//Here we will want to change the maxPixelValue to be 255
	img.maxPixelValue = scaleTo;
	//also lets change the max / min to be 255 / 0 resepctivley
	img.max = scaleTo;
	img.min = 0;
	return img;

}

//This function will be used by scaleImage to convert to scaled 0-scaleTo (default 255) pixel
int Tools::scalePixel(int val, int min, int max, int scaleTo) {
	//This double value will hold newPixel value	
	double newValue = (scaleTo * (double(val) - min)) / (double(max) - min);
	return doubleToInt(newValue);
}

int Tools::writeImageToFile(Image img, string filename)
{
	//Creating myFile and checking that it is open correctly
	ofstream myFile;
	myFile.open(filename.c_str());
	if(myFile.is_open()) {
		myFile << "P2 ";
		myFile << img.width << " ";
		myFile << img.height << " ";
		myFile << img.maxPixelValue << endl;

		for(unsigned int i = 0; i < img.mainData.size(); i++) {
			myFile << img.mainData.at(i) << " ";
			//After adding pixelValue to file lets add spaces between values
			if(img.mainData.at(i) < 10) {
				myFile << "  ";
			}
			else if(img.mainData.at(i) < 100) {
				myFile << " ";
			}
			
			
			if((i+1) % img.width == 0 && i>0) {
				myFile << endl;
			}
		}
		myFile.close();
	}
	else {
		cerr << "Error writing to file named '" << filename << "'!" << endl;
		return -1;
	}
	return 0;
}

int Tools::doubleToInt(double val) {
	//By adding 0.5 to my static cast it will round correctly
	int result = static_cast<int>(val + 0.5);	
	if(debug && double(result) != val) 
			cout << "Rounding difference! from " << val 
				<< " to " << result << endl;
	return result;
}
