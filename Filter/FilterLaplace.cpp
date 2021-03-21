//class FilterLaplace
#ifndef FILTERLAPLACE
#define FILTERLAPLACE

#include "FilterBlur.cpp"

class FilterLaplace :
	public Filter, Array<float>
{
private:
	int N;
	Vec3<float> newColor;
	Vec3<float> tempColor;
public:
	Image operator << (const Image & image) {
		Image filtered(image);

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
				newColor = newColor.clampToLowerBound(0);
				newColor = newColor.clampToUpperBound(1);
				filtered.setPoint(x, y, newColor);
			}
		}
		return filtered;
	}

	FilterLaplace() {
		N = 3;
		float a = 0;
		float b = 1;
		float c = -4;
		width = N;
		height = N;
		buffer = vector<float>(9);
		setPoint(0, 0, a);
		setPoint(0, 2, a);
		setPoint(2, 0, a);
		setPoint(2, 2, a);
		setPoint(0, 1, b);
		setPoint(1, 0, b);
		setPoint(1, 2, b);
		setPoint(2, 1, b);
		setPoint(1, 1, c);
	}

	~FilterLaplace() {

	}
};
#endif // !FILTERLAPLACE