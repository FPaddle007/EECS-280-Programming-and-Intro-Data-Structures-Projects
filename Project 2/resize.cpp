// Project UID af1f95f547e44c8ea88730dfb185559d

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <string>
#include "Matrix.h"
#include "processing.h"
#include "Image.h"
#include <ostream>

using namespace std;

int main(int argc, char* argv[]) {

	Image* image = new Image;

	ifstream fin;
	ofstream fout;
	
	string filenameIn = argv[1];
	string filenameOut = argv[2];
	fin.open(filenameIn.c_str());
	
	if (!fin.is_open()) {
		cout << "Error opening file: " << filenameIn << endl;
		return 1;
	}
	if (!fout.is_open()) {
		cout << "Error opening file: " << filenameOut << endl;
		return 1;
	}
	if (argc == 4 || argc == 5) {
	
		if (argc == 4) {
			int width = atoi(argv[3]);
			Image_init(image, fin);
			seam_carve(image, width, Image_height(image));
		}
		if (argc == 5) {
			int width = atoi(argv[3]);
			int height = atoi(argv[4]);
			Image_init(image, fin);
			seam_carve(image, width, height);
		}
		Image_print(image, fout);

		delete image;
	}
	else {
		cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
			<< "WIDTH and HEIGHT must be less than or equal to original" << endl;
	}

	return 1;
}



