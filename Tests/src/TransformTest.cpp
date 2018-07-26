#include "TransformTest.h"

TEST_F(TransformTest, DefaultConstructor)
{
	auto transform = Transform();
	ASSERT_EQ(transform.GetTransformMatrix(), glm::mat4(1.0));
}

TEST_F(TransformTest, SetTransform)
{
	auto transform = Transform();
	transform.SetTransform(tMatrix);

	ASSERT_EQ(transform.GetTransformMatrix(), tMatrix);
}

TEST_F(TransformTest, GetPosition)
{
	auto transform = Transform(tMatrix);
	auto expectedPosition = glm::vec3(tMatrix[3]);

	ASSERT_EQ(expectedPosition, transform.GetPosition());
}

TEST_F(TransformTest, GetScale)
{
	auto transform = Transform(tMatrix);
	auto expectedScale = glm::vec3(tMatrix[0][0], tMatrix[1][1], tMatrix[2][2]);

	ASSERT_EQ(expectedScale, transform.GetScale());
}

TEST_F(TransformTest, Scale)
{
	auto transform = Transform(tMatrix);
	auto expectedScale = glm::vec3(
		tMatrix[0][0] * 2,
		tMatrix[1][1] * 2,
		tMatrix[2][2] * 2);

	transform.Scale(glm::vec3(2.0));

	ASSERT_EQ(expectedScale, transform.GetScale());
}

TEST_F(TransformTest, SetPosition)
{
	auto expectedPos = glm::vec4(1.0f, 2.0f, 9.99f, tMatrix[3][3]);
	auto transform = Transform(tMatrix);
	auto expectedMatrix = tMatrix;
	expectedMatrix[3] = expectedPos;

	transform.SetPosition(glm::vec3(expectedPos));

	ASSERT_EQ(expectedMatrix, transform.GetTransformMatrix());
}