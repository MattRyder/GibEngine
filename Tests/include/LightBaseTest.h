#pragma once

#include "gtest/gtest.h"

#include "LightBase.h"


class LightBaseTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
        lightBase = new GibEngine::LightBase(GibEngine::Entity::Type::LIGHT,
            position, ambientColor, diffuseColor, specularColor);
    }

    virtual void TearDown()
    {
        delete lightBase;
    }

    glm::vec3 position = glm::vec3(10.0f, 15.0f, 20.0f);
    glm::vec3 ambientColor = glm::vec3(0.33f);
    glm::vec3 diffuseColor = glm::vec3(1.0f);
    glm::vec3 specularColor = glm::vec3(0.5f);
	GibEngine::LightBase* lightBase;
};