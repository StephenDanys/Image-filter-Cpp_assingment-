#ifndef IMAGE
#define IMAGE

#include <iostream>
#include <string>
#include "ppm.h"
#include "Vec3.h"
#include "Image.h"


using namespace std;
using namespace math;
namespace imaging
{
		bool Image::load(const std::string & filename, const std::string & format) {
			int len = filename.length() - format.length();
			for (unsigned int i = len; i < len + format.length(); i++) {
				if (filename[i] != format[i - len]) {
					cout << "This is not a ppm file" << endl;
					return false;
				}
			}//this is a ppm file

			int wid = 0, hei = 0; //width, height
			float* data = ReadPPM(filename.data(), &wid, &hei);

			if (data == nullptr) {
				return false;
			}//float* data is not empty
			if (this != nullptr) {
				buffer.clear();
				width = 0;
				height = 0;
			}//Image properties are empty

			//Image initialisation
			this->width = wid;
			this->height = hei;
			
			float r, g, b;
			for (int i = 0; i < 3 * wid * hei; i += 3) { 
				r = data[i];
				g = data[i + 1];
				b = data[i + 2];

				this->buffer.push_back(Vec3<float>(r, g, b));
			}//buffer filled

			return true;
		}

		
		bool Image::save(const std::string & filename, const std::string & format) {
			int len = filename.length() - format.length();
			for (unsigned int i = len; i < len + format.length(); i++) {
				if (filename[i] != format[i - len]) {
					cout << "This is not a ppm file" << endl;
					return false;
				}
			}// file checked
			if (this == nullptr) {
				return false;
			}//Image object is initialized

			float* data = new float[3 * width*height];

			bool flag;
			for (unsigned int i = 0; i < width*height; i++) {
				//expand T [i]
				data[i * 3] = buffer[i][0];       //red
				data[i * 3 + 1] = (buffer[i])[1]; //green
				data[i * 3 + 2] = (buffer[i])[2]; //blue
			}

			flag = WritePPM(data, width, height, filename.data());

			return flag;
		}
	
		Vec3<float> Image::getPixel(unsigned int x, unsigned int y) const {
			return getPoint(x, y);
		}

		void Image::setPixel(unsigned int x, unsigned int y, Vec3<float> & value) {
			setPoint(x, y, value);
		}

}
#endif // !IMAGE
