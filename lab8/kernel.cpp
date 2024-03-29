/**
Author: Tony Liu
Course: CSCI-135
Instructor: Genady Maryash
Assignment: Lab 8 G

Horizontal Edge detection
**/
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;

// Reads a PGM file.
// Notice that: height and width are passed by reference!
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	// read the header P2
	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	// skip the comments (if any)
	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;
}


// Writes a PGM file
// Need to provide the array data and the image dimensions
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	// print the header
	ostr << "P2" << endl;
	// width, height
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' ';
			ostr << endl;
		}
	}
	ostr.close();
	return;
}

int func(int a, int b, int c, int d, int e, int f, int g, int h, int i){
    if(a > 255){
        a = 0;
    }
    if(b > 255){
        b = 0;
    }
    if(c > 255){
        c = 0;
    }
    if(d > 255){
        d = 0;
    }
    if(e > 255){
        e = 0;
    }
    if(f > 255){
        f = 0;
    }
    if(g > 255){
        g = 0;
    }
    if(h > 255){
        h = 0;
    }
    if(i > 255){
        i = 0;
    }
    return ((g+(2*h)+i)-(a+(2*b)+c));
}

int main() {

	int img[MAX_H][MAX_W];
	int h, w;

	readImage(img, h, w); // read it from the file "inImage.pgm"
	// h and w were passed by reference and
	// now contain the dimensions of the picture
	// and the 2-dimesional array img contains the image data

	// Now we can manipulate the image the way we like
	// for example we copy its contents into a new array
	int out[MAX_H][MAX_W];

	for(int row = 0; row < h; row++) {
		for(int col = 0; col < w; col++) {
            int f = func(img[row-1][col-1],img[row-1][col],img[row-1][col+1],img[row][col-1],img[row][col],img[row][col+1],img[row+1][col-1],img[row+1][col],img[row+1][col+1]);
            if(f < 0){
                f = 0;
            }else if(f > 255){
                f = 255;
            }
            out[row][col] = f;
		}
	}

	// and save this new image to file "outImage.pgm"
	writeImage(out, h, w);

}
