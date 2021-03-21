#ifndef ARRAY
#define ARRAY

#include <iostream>
#include "Vec3.h"
#include <vector>

using namespace std;

namespace math {
	
	template <typename T>
	class Array
	{
	protected:
		vector<T> buffer;

		unsigned int width, 
					height;

	public:
		// metric accessors

		/*! Returns the width of the array
		 */
		const unsigned int getWidth() const { return width; }

		/*! Returns the height of the array
		 */
		const unsigned int getHeight() const { return height; }

		vector<T>  getRawDataPtr()
		{
			return buffer;
		}

		T getPoint(unsigned int x, unsigned int y) const
		{
			if ((x > getWidth()) | (y > getHeight())) {
				cout << "Point out-of-bounds!" << endl;
				return  T();
			}
			return this->buffer[getWidth()*(y)+x];
		}
		
		void setPoint(unsigned int x, unsigned int y, T & value) {
			if ((x > getWidth()) | (y > getHeight())) {
				cout << "Point out-of-bounds!" << endl;
				return;
			}
			buffer[this->getWidth()*y + x] = value;
		}

		void setData(const std::vector<T>  & data_ptr) {
			if ((width <= 0) | (height <= 0) | (data_ptr.empty())) {
				cout << "Could not find data!" << endl;
				cout << data_ptr.empty();
				return;
			}
			buffer.clear();
			for (unsigned int i = 0; i < getWidth()*getHeight(); i++) {
				buffer.push_back(data_ptr[i]);
			}
		}

		Array() {
			buffer.clear();
			width = 0;
			height = 0;
		}

		Array(unsigned int width, unsigned int height) {
			this->width = width;
			this->height = height;
		}

		Array(unsigned int width, unsigned int height, const std::vector<T>  data_ptr) {
			Array(width, height);
			setData(data_ptr);
		}

		Array(const Array &src) :  width(src.width), height(src.height) {
			setData(src.buffer); 
		}

		~Array() { 
			buffer.clear();
		}

		Array & operator = (const Array & right) {
			if (&right == this) {
				return *this;
			}
			if (!buffer.empty()) { 
				buffer.clear();
			}
			width = right.getWidth();
			height = right.getHeight();
			setData(right.buffer);
			return *this;
		}

		//getPoint
		T operator () (const int i, const int j) {
			return getPoint(i, j);
		}

	};
}
#endif // !ARRAY