//class FilterBlur
#ifndef FILTERBLUREX
#define FILTERBLUREX

#include "Levelling.cpp"
#include "Array.cpp"
#include <vector>
#include <math.h>

class FilterBlurEx :
	public Filter , Array<float>
{
private:
	float N;
	int dif;
	float weight;
	Vec3<float> newColor;
	Vec3<float> tempColor;

public:
	Image operator << (const Image & image) {
		Image filtered(image);

		for (unsigned int x = 0; x < image.getWidth(); x++) { //for each collumn of pixels
			for (unsigned int y = 0; y < image.getHeight(); y++) { //for each row of pixels

				newColor = Vec3<float>(); //default color (0,0,0)

				//if out of NXN grid
				if ((x < N / 2) || (x >= image.getWidth() - N / 2) || (y < N / 2) || (y >= image.getHeight() - N / 2)) {
					dif = 0;
					for (int m = -N / 2; m <= N / 2; m++) {
						for (int n = -N / 2; n <= N / 2; n++) {
							if ((x + m < 0) || (x + m >= image.getWidth()) || (y + n < 0) || (y + n >= image.getHeight())) {
								dif++;
							}
						}
					}
					int remaining = N*N - dif;
					FilterBlurEx edges = FilterBlurEx(pow(remaining,0.5));
					
					for (int m = -N / 2; m <= N / 2; m++) {
						for (int n = -N / 2; n <= N / 2; n++) {
							if ((x >= N / 2) && (x < image.getWidth() - N / 2) && (y >= N / 2) && (y < image.getHeight() - N / 2)) {
								tempColor = image.getPoint(x + m, y + n);                      //pixel in NXN grid
								tempColor = tempColor * edges.getPoint(m + N / 2, n + N / 2); //multiplied by its filter weight
								newColor = newColor + tempColor; //sum of NXN grid
							}
						}
					}
				}
				else {
					//for NXN grid
					for (int m = -N / 2; m <= N / 2; m++) {
						for (int n = -N / 2; n <= N / 2; n++) {
							tempColor = image.getPoint(x + m, y + n);                     //pixel in NXN grid
							tempColor = tempColor * this->getPoint(m + N / 2, n + N / 2); //multiplied by its filter weight
							newColor = newColor + tempColor; //sum of NXN grid
						}
					}

				}
				//set fixed Pixel
				filtered.setPoint(x, y, newColor); 
			}
		}
		return filtered;
	}

	void setWeight(float weight) {
		this->weight = weight;
	}

	FilterBlurEx(float N) {
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

	~FilterBlurEx() {

	}
};
#endif