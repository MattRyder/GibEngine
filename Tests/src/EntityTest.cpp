#include "EntityTest.h"

TEST_F(EntityTest, GetID)
{
	ASSERT_EQ(0, entity->GetID());
}

TEST_F(EntityTest, AssertIncrementalId)
{
	// the default one created for this test uses 1, so from:
	for (int i = 2; i < 10; i++)
	{
		auto entity = MockEntity(ENTITY_NAME);
		ASSERT_EQ(entity.GetID(), i);
	}
}

TEST_F(EntityTest, GetPosition)
{
	glm::vec3 trajectory = glm::vec3(04.1975, 02.1991, 12.1998);
	
	entity->SetPosition(trajectory);
	ASSERT_EQ(entity->GetPosition(), trajectory);
}

TEST_F(EntityTest, GetName)
{
	// Set the name of the mock:
	entity->SetName(EntityTest::ENTITY_NAME);

	ASSERT_STREQ(entity->GetName().c_str(), EntityTest::ENTITY_NAME.c_str());
}

TEST_F(EntityTest, GetType)
{
	ASSERT_EQ(entity->GetType(), Entity::Type::ENTITY);
}

TEST_F(EntityTest, GetTypeName)
{
	ASSERT_STREQ(entity->GetTypeName().c_str(), EntityTest::ENTITY_TYPE.c_str());
}