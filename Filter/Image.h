//------------------------------------------------------------
//
// C++ course assignment code 
//
// G. Papaioannou, 2017 - 2018
//
//

#ifndef _IMAGE
#define _IMAGE

//#include "Color.h"
#include <string>
#include "Array.cpp"
#include "Vec3.h"

/*! The imaging namespace contains every class or function associated with the image storage, compression and manipulation. 
 */ 
namespace imaging
{

//------------------------------------ class Image ------------------------------------------------

	/*! It is the class that represents a generic data container for an image.
	 * 
	 * It holds the actual buffer of the pixel values and provides methods for accessing them, 
	 * either as individual pixels or as a memory block. The Image class alone does not provide 
	 * any functionality for loading and storing an image, as it is the result or input to such a procedure. 
	 *
	 * The internal buffer of an image object stores the actual bytes (data) of the color image as
	 * a contiguous sequence of Color structures. Hence, the size of the buffer variable holding these data is 
	 * width X height X sizeof(Color) bytes.
	 *
	 * All values stored in the Color data type components are assumed to be floating point values and for typical (normalized)
	 * intensity ranges, each color component is within the range [0.0, 1.0].
	 */ 
	using namespace math;
	class Image: public Array<Vec3<float>>
	{
	public:

		/*!
		 * Loads the image data from the specified file, if the extension of the filename matches the format string.
		 *
		 * Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the 
		 * Image object is initialized, its contents are wiped out before initializing it to the width, height and data
		 * read from the file.
		 * 
		 * \param filename is the string of the file to read the image data from.
		 * \param format specifies the file format according to which the image data should be decoded from the file.
		 * Only the "ppm" format is a valid format string for now.
		 * 
		 * \return true if the loading completes successfully, false otherwise.
		 */
		bool load(const std::string & filename, const std::string & format);

		/*!
		* Stores the image data to the specified file, if the extension of the filename matches the format string.
		*
		* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
		* Image object is not initialized, the method should return immediately with a false return value.
		*
		* \param filename is the string of the file to write the image data to.
		* \param format specifies the file format according to which the image data should be encoded to the file.
		* Only the "ppm" format is a valid format string for now.
		*
		* \return true if the save operation completes successfully, false otherwise.
		*/
		bool save(const std::string & filename, const std::string & format);

		Vec3<float> getPixel(unsigned int x, unsigned int y) const;
			
		void setPixel(unsigned int x, unsigned int y, Vec3<float> & value);

	};

} //namespace imaging

#endif