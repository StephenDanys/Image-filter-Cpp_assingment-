//class Levelling
#ifndef LEVELLING
#define LEVELLING

#include "Filter.cpp"

class Levelling :
	public Filter, Array<float>
{
protected:
	int N;
	float weight;
	Array<float> f;
	Vec3<float> newColor;
	Vec3<float> tempColor;

public:
	Image operator << (const Image & image) {
		Image filtered(image);
		cout << "default constructor executed" << endl;
		for (unsigned int x = 0; x < image.getWidth(); x++) { //for each collumn of pixels
			for (unsigned int y = 0; y < image.getHeight(); y++) { //for each row of pixels

				newColor = Vec3<float>(); //default color (0,0,0)
				//for NXN grid
				for (int m = floor(-N / 2); m <= floor(N / 2); m++) {
					for (int n = floor(-N / 2); n <= floor(N / 2); n++) {
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
				//cout <<"("<< x << "," << y <<")"<< endl;
				filtered.setPoint(x, y, newColor);
			}
		}
		return filtered;
	}

	Levelling() {}

	Levelling(int N, Array<float> f) {
		this->N = N;
		width = N;
		height = N;
		buffer = vector<float>(width*height);
		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int j = 0; j < height; j++) {
				weight = f.getPoint(i, j);
				cout << "setPoint constructorf " << i << "," << j << endl;
				setPoint(i, j, weight);
			}
		}
	}

	Levelling(int N, float weight) {
		this->N = N;
		width = N;
		height = N;
		buffer = vector<float>(width*height);
		for (unsigned int i = 0; i < width; i++) {
			for (unsigned int j = 0; j < height; j++) {
				setPoint(i, j, weight);
				cout << "setPoint constructorw " << i << "," << j << endl;
			}
		}
	}

	~Levelling() {

	}
};
#endif