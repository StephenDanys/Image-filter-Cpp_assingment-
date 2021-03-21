//class FilterLinear
#ifndef FILTERLINEAR
#define FILTERLINEAR

#include "Filter.cpp"

class FilterLinear :
	public Filter
{
private:
	Vec3<float> newColor;
	Vec3<float> a;
	Vec3<float> c;
	
public:
	Image operator << (const Image & image) {
		Image filtered(image);

		for (unsigned int x = 0; x < image.getWidth(); x++) {
			for (unsigned int y = 0; y < image.getHeight(); y++) {
				newColor = image.getPoint(x, y);
				newColor = (a * newColor) + c;
				newColor = newColor.clampToLowerBound(0);
				newColor = newColor.clampToUpperBound(1);
				filtered.setPoint(x, y, newColor);
			}
		}

		return filtered;
	}

	FilterLinear(const Vec3<float>* first, const Vec3<float>* second) {
		a = *first;
		c = *second;
	}

	FilterLinear(const FilterLinear & filter) {
		this->a = filter.a;
		this->c = filter.c;
	}

	~FilterLinear() {

	}
};
#endif // !FILTERLINEAR