#pragma once

#include "gtest/gtest.h"

#include "Entity.h"

class MockEntity : public GibEngine::Entity
{
public:
	MockEntity(const char* name) : Entity(GibEngine::EntityType::ENTITY, name) { }

	virtual void Update(double deltaTime)
	{
		return;
	}
};

class EntityTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		entity = new MockEntity(ENTITY_NAME);
	}

	MockEntity* entity;

	const char* ENTITY_NAME = "MockEntityName";
};