#pragma once
#include "Types.h"
#include "ColorBuffer.h"
#include <string>

class Tracer
{
public: 
	void Trace(struct Buffer* buffer, class Scene* scene, class Camera* camera, const std::string& message);

public: 
	int samples = 1; 
	int depth = 50; 
};