#pragma once

#include <gtest/gtest.h>
#include "Transform.h"

using namespace GibEngine;
using namespace ::testing;

class TransformTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
		tMatrix = glm::mat4();
		tMatrix[0][0] = 1.1f;
		tMatrix[1][1] = 2.2f;
		tMatrix[2][2] = 3.3f;
		tMatrix[3] = glm::vec4(4.4f, 5.5f, 6.6f, 1.0f);
	}

public:
	glm::mat4 tMatrix;
};