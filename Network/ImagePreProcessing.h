#pragma once

#include "qimage.h"
#include "qpixmap.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class ImagePreProcessing {

private:
	QImage processingimage;
	QRgb qrgb;
	QSize processingimage_size;
	
	int width, height;
	int newwidth, newheight;
	int vectornumber;

	void arrayprint(vector<vector<int>>);
	void coverImage(QImage &im,int a, int b);
	
public:
	vector<vector<int>> imagearray;
	vector<vector<int>> retimagearray;

	
	ImagePreProcessing(int a) { newheight = a; newwidth = a; };
	ImagePreProcessing(string fullpath); 
	void maskCreation(string name, string path, string format, string newname);

	void scaledImage(string name, string path, string format,string newname);
	void convertImageToMatrix(string name, string path, string format);
	void retreievingImage(string name);
	void noiseFunction(string fullpath,int pr,int c);
	void mudFunction(string fullpath,int c, int tryb);

	int scaledSize() { return newwidth*newheight; };
	

};
