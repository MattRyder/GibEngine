#pragma once

#include "Mesh.h"

namespace GibEngine
{
	class Plane : public Mesh
	{
	public:
		Plane(unsigned int length, unsigned int width, unsigned int intervalSize);
	};
}