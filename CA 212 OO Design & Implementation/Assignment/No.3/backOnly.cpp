#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

bool loadPPM(vector<int>& image, int& w, int& h, char* filename, int first);
bool writePPM(const char* filename, vector<int>& image, int w, int h);

int main(int argc, char *argv[])
{
	//check for pictures
	if(argc < 5)
	{
		cout << "not enough data for correct result" << endl;
		return 0;
	}

	//create assorted variables
	bool error = false;
	const char* fileOutput = "Solution.ppm";
	vector<int> new_Image;
	int no_Images = argc-1;

	//vector of images
	vector<vector<int> > gallery(no_Images);

	//image format
	int width, height;
	int pixelCount;
	cout << "argc: " << argc << endl; 

	//getting images
	for (int image = 0; image < no_Images; image++)
	{
		error = loadPPM(gallery[image], width, height, argv[image+1], image);
		if(error)
		{
			cout << "error While reading image: " << image+1 << endl;
			return 0;
		}
	}
	pixelCount = width * height;

	new_Image.resize(pixelCount* 3); //same size as input images

	vector<vector<int> > rgb(3, vector<int>(no_Images));//store the current pixels

	//work on each pixel
	for (int pixel = 0; pixel < pixelCount; pixel++)
	{
		//for rgb
		for(int colour = 0, location = pixel*3; colour < 3; colour++, location++)
		{
			//each image
			for(int image = 0; image < no_Images; image++)
			{
				rgb[colour][image] = gallery[image][location];
				
			}

			/*_______MEDIAN_______*/
			sort(rgb[colour].begin(), rgb[colour].end());
			new_Image[location] = rgb[colour][no_Images/2];
			/*____________________*/

		}

		//status on completion
		if(pixel % (pixelCount/100) == 0)
		{
			cout << "\b\b\b\b\b\b\b\b\b"; //overwrite line
			cout << (pixel/(pixelCount/100)) << "% Done"; //print current percentage

		}
	}

	error = writePPM(fileOutput, new_Image, width, height);
	if(error)
	{
		cout << "error While writing image: " << fileOutput << endl;
		return 0;
	}

	//end status
	cout << endl << "---------------" << endl
		 << "Output file: " << fileOutput << endl;

	return 0;
}

bool loadPPM(vector<int>& image, int& w, int& h, char* filename, int first)
{
	//open file
	ifstream input;
	input.open(filename);

	if(input.fail())
	{
		cout << "decoder error " << ": " << filename << endl;
		return true;
	}

	//Read Header
	string type;
	int max;
	input >> type >> w >> h >> max;

	//print header of first file
	if(first == 0)
		cout << "File Type:" << endl 
		 	 << type << endl 
		 	 << w <<" "<< h << endl
		 	 << max << endl 
		 	 << "---------------" << endl;

	//resize vector to fit file pixels
	image.resize(w * h * 3);

	//getting pixels of ppm file
	for (int i = 0; i <(w*h*3); )
	{
		input>>image[i]>>image[i+1]>>image[i+2];
		i+=3;
	}
	input.close();

	return false;
}

bool writePPM(const char* filename, vector<int>& image, int w, int h)
{
	//Open output file
	ofstream output;
	output.open(filename);

	if(output.fail())
	{
		cout << "encoder error " << ": " << filename << endl;
		return true;
	}

	//write header
	output << "P3\n" << w << " " << h << "\n255\n";

	//write pixels
	for (int i = 0; i < (w * h * 3); i+=3)
	{
		output << image[i] << " " << image[i+1] << " " << image[i+2] << "\n";
	}
	output.close();
	return false;
}