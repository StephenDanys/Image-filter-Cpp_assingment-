#include <iostream>
#include "Image.h"
#include "Vec3.h"
#include "Filter.cpp"
#include "FilterLinear.cpp"
#include "FilterGamma.cpp"
#include "FilterBlur.cpp"
#include "FilterLaplace.cpp"

using namespace std;
using namespace imaging;

int main(int argc, char *argv[])
{
	bool flag = false;
	Image image;
	string filePath;
	string name;
	string path = "";

	filePath = argv[argc - 1]; //last argument
	name = filePath;

	size_t pos = filePath.rfind("\\");
	if (static_cast<int>(pos) >= 0) {
		path = filePath.substr(0,pos+1);
		name = filePath.substr(pos + 1);

	}
	cout << name << endl;

	flag = image.load(filePath, "ppm");
	int i = 0;
	while (i < argc) {
		if (strcmp(argv[i], "-f") == 0) {
			flag = true;
			i++;
			//FilterLinear
			if (strcmp(argv[i], "linear") == 0) {
				float a = atof(argv[++i]);
				float b = atof(argv[++i]);
				float c = atof(argv[++i]);
				Vec3<float> colorA = Vec3<float>(a, b, c);
				a = atof(argv[++i]); b = atof(argv[++i]); c = atof(argv[++i]);
				Vec3<float> colorB = Vec3<float>(a, b, c);
				FilterLinear filter = FilterLinear(&colorA, &colorB);
				image = filter << image;
			}
			//FilterGamma
			else if (strcmp(argv[i], "gamma") == 0) {
				FilterGamma filter = FilterGamma(atof(argv[++i]));
				image = filter << image;

			}
			//FilterBlur
			else if (strcmp(argv[i], "blur") == 0) {
				FilterBlur filter = FilterBlur(atof(argv[++i]));
				//Levelling filter = Levelling(5, pow(5, -2));
				image = filter << image;
			}
			//FilterLaplace
			else if (strcmp(argv[i], "laplace") == 0) {
				FilterLaplace filter = FilterLaplace();
				image = filter << image;
			}
		}

		i++;
	}

	if (!flag) return 0;
	if (!flag) {
		cout << "Problems with loading image!" << endl;
		system("pause");
		return 0;
	}

	cout << "Image dimensions are: " << image.getWidth() << " X " << image.getHeight() << endl;

	//new file name
	filePath = path + "filtered_" + name;

	flag = image.save(filePath, "ppm");


	cout << "Omg it's compiling!!!" << endl;
	system("pause");
	return 0;
}