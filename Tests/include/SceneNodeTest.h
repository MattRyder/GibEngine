#pragma once

#include <gtest/gtest.h>

#include "scene/Node.h"

using namespace GibEngine;

class SceneNodeTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		root = new Scene::Node("");
	};

	virtual void TearDown()
	{
		delete root;
	};

	Scene::Node* root;
};