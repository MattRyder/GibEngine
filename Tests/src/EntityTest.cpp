#include "EntityTest.h"

TEST_F(EntityTest, GetID)
{
	ASSERT_EQ(0, entity->GetID());
}

TEST_F(EntityTest, AssertIncrementalId)
{
	auto entity = MockEntity(ENTITY_NAME);
	unsigned int lastId = entity.GetID();

	for (int i = lastId; i < lastId + 5; i++)
	{
		auto entity = MockEntity(ENTITY_NAME);
		ASSERT_EQ(entity.GetID(), i+1);
	}
}

TEST_F(EntityTest, GetPosition)
{
	glm::vec3 trajectory = glm::vec3(04.1975, 02.1991, 12.1998);
	
	entity->SetPosition(trajectory);
	ASSERT_EQ(entity->GetLocalTransform().GetPosition(), trajectory);
}

TEST_F(EntityTest, GetName)
{
	// Set the name of the mock:
	entity->SetName(EntityTest::ENTITY_NAME);

	ASSERT_STREQ(entity->GetName().c_str(), EntityTest::ENTITY_NAME.c_str());
}

TEST_F(EntityTest, GetType)
{
	ASSERT_EQ(entity->GetType(), BaseEntity::Type::ENTITY);
}

TEST_F(EntityTest, GetTypeName)
{
	ASSERT_STREQ(entity->GetTypeName().c_str(), EntityTest::ENTITY_TYPE.c_str());
}