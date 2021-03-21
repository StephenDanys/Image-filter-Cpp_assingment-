//class FilterGamma
#ifndef FILTERGAMMA
#define FILTERGAMMA

#include "Filter.cpp"

class FilterGamma :
	public Filter
{
private:
	Vec3<float> newColor;
	float gamma, r, g, b;

public:
	Image operator << (const Image & image) {
		Image filtered(image);

		for (unsigned int x = 0; x < image.getWidth(); x++) {
			for (unsigned int y = 0; y < image.getHeight(); y++) {
				newColor = image.getPoint(x, y);
				newColor.r = powf(newColor.r, gamma);
				newColor.g = powf(newColor.g, gamma);
				newColor.b = powf(newColor.b, gamma);
				newColor = newColor.clampToLowerBound(0);
				newColor = newColor.clampToUpperBound(1);
				filtered.setPoint(x, y, newColor);
			}
		}
		
		return filtered;
	}

	FilterGamma(float gamma) {
		this->gamma = gamma;
	}

	FilterGamma(const FilterGamma & filter) {
		this->gamma = filter.gamma;
	}

	~FilterGamma() {

	}
};
#endif