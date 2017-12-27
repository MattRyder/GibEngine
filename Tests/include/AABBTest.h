#pragma once

#include <gtest/gtest.h>

#include "AABB.h"

using namespace GibEngine;

class AABBTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		pos = glm::vec3(10, 0, 10);
		size = glm::vec3(10, 10, 10);
	};

	glm::vec3 pos;
	glm::vec3 size;
};