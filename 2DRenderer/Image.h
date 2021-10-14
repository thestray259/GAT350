#pragma once
#include "Renderer.h"
#include <string>

class Image
{
	friend class Framebuffer;
public: 
	~Image();

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip(); 

private: 
	// pointer to uint_t8 buffer 
	uint8_t* buffer; 
	int width = 0; 
	int height = 0; 

	uint8_t header[54]; 
	int pitch = width * sizeof(color_t); 
	//buffer = new uint8_t[height * pitch]; 
	uint16_t bitsPerPixel = *((uint16_t*)(&header[28])); 
	uint16_t bytesPerPixel = bitsPerPixel / 8;

};