#include "AABBTest.h"

TEST_F(AABBTest, ConstructorDefault)
{
	AABB* aabb = new AABB();

	ASSERT_TRUE(
		aabb->GetPosition().x == 0 &&
		aabb->GetPosition().y == 0 &&
		aabb->GetPosition().z == 0);

	ASSERT_TRUE(
		aabb->GetSize().x == 0 &&
		aabb->GetSize().y == 0 &&
		aabb->GetSize().z == 0);

	delete aabb;
}

TEST_F(AABBTest, ConstructorWithValues)
{
	AABB* aabb = new AABB(pos, size);

	ASSERT_TRUE(
		aabb->GetPosition().x == 10 &&
		aabb->GetPosition().y == 0  &&
		aabb->GetPosition().z == 10);

	ASSERT_TRUE(
		aabb->GetSize().x == 10 &&
		aabb->GetSize().y == 10 &&
		aabb->GetSize().z == 10);

	delete aabb;
}

TEST_F(AABBTest, Contains)
{
	AABB* aabb = new AABB(pos, size);

	glm::vec3 othPos = glm::vec3(11, 1, 11);
	glm::vec3 othSize = glm::vec3(5, 5, 5);
	AABB* other = new AABB(othPos, othSize);

	bool res = aabb->Contains(*other);

	ASSERT_TRUE(res);
}

TEST_F(AABBTest, DoesntContain)
{
	AABB* aabb = new AABB(pos, size);

	glm::vec3 othPos = glm::vec3(500, 500, 500);
	glm::vec3 othSize = glm::vec3(5, 5, 5);
	AABB* other = new AABB(othPos, othSize);

	bool res = aabb->Contains(*other);

	ASSERT_FALSE(res);

	delete aabb;
	delete other;
}

TEST_F(AABBTest, ContainsPoint)
{
	AABB* aabb = new AABB(pos, size);
	glm::vec3 point = glm::vec3(15, 5, 15);

	bool res = aabb->ContainsPoint(point);

	ASSERT_TRUE(res);

	delete aabb;
}

TEST_F(AABBTest, DoesntContainPoint)
{
	AABB* aabb = new AABB(pos, size);
	glm::vec3 point = glm::vec3(100, 50, 150);

	bool res = aabb->ContainsPoint(point);

	ASSERT_FALSE(res);

	delete aabb;
}

TEST_F(AABBTest, Equals)
{
	AABB* aabb = new AABB(pos, size);
	AABB* other = new AABB(pos, size);

	bool res = *aabb == *other;

	ASSERT_TRUE(res);

	delete aabb;
	delete other;
}