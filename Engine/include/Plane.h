#pragma once

#include "Model.h"

namespace GibEngine
{
	class Plane : public Model
	{
	public:
		Plane(unsigned int length, unsigned int width, unsigned int intervalSize);
	};
}