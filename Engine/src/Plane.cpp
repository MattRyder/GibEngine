#include "Plane.h"

GibEngine::Plane::Plane(unsigned int length, unsigned int width, unsigned int intervalSize) : Model()
{
	assert(intervalSize > 0);

	const int widthEnd = width / intervalSize;
	const int lengthEnd = length / intervalSize;

	std::vector<Vertex> vertices;

	Vertex v;
	for (unsigned int x = 0; x < width; x += intervalSize)
	{
		for (unsigned int y = 0; y < length; y += intervalSize)
		{
			if (y == 0)
			{
				v = {};
				v.Position = glm::vec3(x, 0, y);
				vertices.push_back(v);

				v = {};
				v.Position = glm::vec3(x, 0, length);
				vertices.push_back(v);
			}

			v = {};
			v.Position = glm::vec3(x, 0, y);
			vertices.push_back(v);

			v = {};
			v.Position = glm::vec3(width, 0, y);
			vertices.push_back(v);

		}
	}

	v = {};
	v.Position = glm::vec3(widthEnd, 0, lengthEnd);
	vertices.push_back(v);

	v = {};
	v.Position = glm::vec3(0, 0, lengthEnd);
	vertices.push_back(v);

	v = {};
	v.Position = glm::vec3(widthEnd, 0, lengthEnd);
	vertices.push_back(v);

	v = {};
	v.Position = glm::vec3(widthEnd, 0, 0);
	vertices.push_back(v);


	Mesh* mesh = new Mesh(vertices);

	Mesh::Flags flags = static_cast<Mesh::Flags>(Mesh::Flags::RENDER_ENABLED | Mesh::Flags::RENDER_ARRAYS);
	mesh->SetFlags(flags);
	meshes.push_back(mesh);
}
