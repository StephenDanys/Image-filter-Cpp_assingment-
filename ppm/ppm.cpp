#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "xiosbase"
#include "ppm.h"

using namespace std;
float * imaging::ReadPPM(const char * filename, int * w, int * h)
{
	ifstream iFile;
	iFile.open(filename, ios::binary);
	if (!iFile.is_open()) {
		cout << "Cannot open file" << endl;
		return nullptr;
	}

	//Read Header
	string head;
	int width, height, mvc;
	char ctrf;
	iFile >> head >> width >> height >> mvc;
	iFile.get(ctrf);


	if (head.compare("P6") != 0) {
		cout << "This is not a P6" << endl;
		return nullptr;
	}//this is a P6 file

	if (width == NAN || height == NAN) {
		cout << "Could not read height and/or width" << endl;
		return nullptr;
	}
	if (mvc == NAN) {
		cout << "Could not read MVC" << endl; // maximum value of the color = MVC
		return nullptr;
	}
	if (mvc > 255) {
		cout << "MVC is ivalid" << endl; // maximum value of the color = MVC
		return nullptr;
	}
	*w = width;
	*h = height;
	//search for comments!!!!!!!!!!!!!!!!

	float* tempColor = new float[3 * *w**h];
	unsigned char* arrrr = new unsigned char[3 * *w * *h];

	iFile.read((char*)arrrr, 3 * *w * *h);
	for (int i = 0; i < 3 * *w * *h; i++) {
		tempColor[i] = (float)arrrr[i] / 255.0f;
	}

	iFile.clear();
	iFile.close();
	delete[] arrrr;

	return tempColor;
}//end of ReadPPM


bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	if (data == nullptr)
	{
		cout << "data parameter null" << endl;
		return false;
	}//float* is not empty

	ofstream oFile(filename, ios::binary);
	if (!oFile.is_open())
	{
		cout << "Could not create file" << endl;
		return false;
	}

	oFile << "P6 " << w << " " << h << " 255" << endl;

	for (int i = 0; i < 3 * w*h; i++)
	{
		int bin = (data[i]) * 255;
		oFile.write((char*)(&bin), 1);
	}

	oFile.clear();
	oFile.close();

	return true;
} //end of WritePPM