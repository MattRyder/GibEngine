#pragma once

#include "gtest/gtest.h"

#include "Entity.h"

class MockEntity : public GibEngine::Entity
{
public:
	MockEntity() : Entity(GibEngine::EntityType::ENTITY) { }

	// Inherited via Entity
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
		entity = new MockEntity();
	}

	MockEntity* entity;

	const char* ENTITY_NAME = "MockEntityName";
};