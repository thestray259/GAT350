#pragma once
#include "Renderer.h"
#include "ColorBuffer.h"
#include <string>

class Image
{
	friend class Framebuffer;
public: 
	~Image();

	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip(); 

private: 
	uint8_t* buffer; 
	int width = 0; 
	int height = 0; 

	ColorBuffer colorBuffer;
};