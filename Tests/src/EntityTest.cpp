#include "EntityTest.h"

TEST_F(EntityTest, GetID)
{
	ASSERT_EQ(0, entity->GetID());
}

TEST_F(EntityTest, GetPosition)
{
	// Sparks the next entity on trajectory:
	glm::vec3 trajectory = glm::vec3(04.1975, 02.1991, 12.1998);
	
	entity->SetPosition(trajectory);
	ASSERT_EQ(entity->GetPosition(), trajectory);
}

TEST_F(EntityTest, GetName)
{
	// Set the name of the mock:
	entity->SetName(EntityTest::ENTITY_NAME);

	ASSERT_STREQ(entity->GetName(), EntityTest::ENTITY_NAME);
}

TEST_F(EntityTest, GetType)
{
	ASSERT_EQ(entity->GetType(), GibEngine::EntityType::ENTITY);
}

TEST_F(EntityTest, GetTypeName)
{
	ASSERT_STREQ(entity->GetTypeName(), "Entity");
}