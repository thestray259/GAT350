#include "Image.h"
#include "SDL_image.h"
#include <iostream>

Image::~Image()
{
	delete[] buffer;
}

bool Image::Load(const std::string& filename, uint8_t alpha)
{
	// Open bmp file and set it to read in the file as binary data (not text)
	SDL_Surface* surface = IMG_Load(filename.data()); // probably wrong 

	//std::ifstream stream(filename, std::ios::binary);
	//if (stream.fail())
	//{
	//	std::cout << "Error: Cannot open file: " << filename << std::endl;
	//	return false;
	//}

	//stream.read((char*)header, 54);

	uint16_t id = *((uint16_t*)(header));
	if (id != 'MB')
	{
		std::cout << "Error: Invalid file format: " << filename << std::endl;
		return false;
	}

	//width = *((int*)(&header[])); 
	//height = *((int*)(&header[])); 

	size_t size = width * height * bytesPerPixel;

	//stream.read(< ? ? ? >);

	uint8_t* data = new uint8_t[size];

	for (int i = 0; i < width * height; i++)
	{
		color_t color;

		// colors in bmp data are stored (BGR)
		int index = i * bytesPerPixel;
		color.b = data[index];
		color.g = data[index + 1];
		color.r = data[index + 2];
		color.a = alpha;

		((color_t*)(buffer))[i] = color;
	}
		
	delete[] data;
	return true;
}

void Image::Flip()
{
	// set the pitch (width * number of bytes per pixel)
	int pitch = width * sizeof(color_t);

	// create temporary line to store data
	uint8_t* temp = new uint8_t[pitch];

	for (int i = 0; i < height / 2; i++)
	{
		uint8_t* line1 = &((buffer)[i * pitch]);
		uint8_t* line2 = &((buffer)[((height - 1) - i) * pitch]);
		memcpy(temp, line1, pitch);
		memcpy(line1, line2, pitch);
		memcpy(line2, temp, pitch);
	}
	delete[] temp;

}

