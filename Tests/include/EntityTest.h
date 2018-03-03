#pragma once

#include <memory>

#include "gtest/gtest.h"

#include "Entity.h"

using namespace GibEngine;

class MockEntity : public Entity
{
public:
	MockEntity(std::string name) : Entity(Entity::Type::ENTITY, name) { }

	virtual void Update(double deltaTime) { }
};

class EntityTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		entity = std::unique_ptr<MockEntity>(new MockEntity(ENTITY_NAME));
	}

	std::unique_ptr<MockEntity> entity;

	const std::string ENTITY_NAME = "MockEntityName";
	const std::string ENTITY_TYPE = "Entity";
};