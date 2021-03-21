//class Filter

#ifndef FILTER
#define FILTER

#include "Image.h"
using namespace imaging;

class Filter
{
public:

	virtual Image  operator << (const Image & image)= 0 ;
	
	Filter() {

	}

	Filter(const Filter & filter) {

	}

	virtual ~Filter() {

	}
	
};
#endif

