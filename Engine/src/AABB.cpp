#include "AABB.h"

GibEngine::AABB::AABB() : position(glm::vec3()), size(glm::vec3()) {}

GibEngine::AABB::AABB(glm::vec3 position, glm::vec3 size) : position(position), size(size) { }

bool GibEngine::AABB::operator==(const AABB& other) const
{
	auto a = position + size;
	auto b = position + size;
	return a.x == b.x && a.y == b.y && a.z == b.z;
}

bool GibEngine::AABB::Contains(const AABB& other) const
{
	auto max = GetMaxBounds();
	auto opos = other.GetPosition();
	auto omax = other.GetMaxBounds();
	return (
		position.x <= opos.x && max.x >= omax.x &&
		position.y <= opos.y && max.y >= omax.y &&
		position.z <= opos.z && max.z >= omax.z
		);
}

bool GibEngine::AABB::ContainsPoint(const glm::vec3 point) const
{
	auto max = position + size;
	return (
		position.x <= point.x && max.x >= point.x &&
		position.y <= point.y && max.y >= point.y &&
		position.z <= point.z && max.z >= point.z);
}

glm::vec3 GibEngine::AABB::GetPosition() const
{
	return position;
}

glm::vec3 GibEngine::AABB::GetSize() const
{
	return size;
}

glm::vec3 GibEngine::AABB::GetMaxBounds() const
{
	return position + size;
}

void GibEngine::AABB::SetPosition(const glm::vec3 position)
{
	this->position = position;
}

void GibEngine::AABB::SetSize(const glm::vec3 size)
{
	this->size = size;
}
