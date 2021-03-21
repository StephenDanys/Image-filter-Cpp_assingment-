//class FilterBlur
#ifndef FILTERBLUR
#define FILTERBLUR

#include "Levelling.cpp"
#include "Array.cpp"
#include <vector>
#include <math.h>

class FilterBlur :
	public Filter, Array<float>
{
private:
	int N;
	float weight;
	Vec3<float> newColor;
	Vec3<float> tempColor;

public:
	Image operator << (const Image & image) {
		Image filtered(image);

		for (unsigned int x = 0; x < image.getWidth(); x++) { //for each collumn of pixels
			for (unsigned int y = 0; y < image.getHeight(); y++) { //for each row of pixels

				newColor = Vec3<float>(); //default color (0,0,0)
				//for NXN grid
				for (int m = -N / 2; m <= N / 2; m++) {
					for (int n = -N / 2; n <= N / 2; n++) {
						if (x + m < 0) continue;
						if (x + m >= image.getWidth()) continue;
						if (y + n < 0) continue;
						if (y + n >= image.getHeight()) continue;
						tempColor = image.getPoint(x + m, y + n);                     //pixel in NXN grid
						tempColor = tempColor * this->getPoint(m + N / 2, n + N / 2); //multiplied by its filter weight
						newColor = newColor + tempColor; //sum of NXN grid

					}
				}
				//set fixed Pixel
				filtered.setPoint(x, y, newColor);
			}
		}
		return filtered;
	}

	FilterBlur(int N) {
		if (N % 2 == 0) N--;
		this->N = N;
		weight = (float)(pow(N, -2));
		width = N;
		height = N;
		buffer = vector<float>(width*height);
		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int j = 0; j < height; j++) {
				setPoint(i, j, weight);
			}
		}
	}

	~FilterBlur() {
	}
};
#endif