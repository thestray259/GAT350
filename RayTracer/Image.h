#pragma once
#include "Renderer.h"
#include "ColorBuffer.h"
#include <string>

class Image
{
	friend class Framebuffer;
public: 
	bool Load(const std::string& filename, uint8_t alpha = 255);
	void Flip(); 

	ColorBuffer colorBuffer;
};