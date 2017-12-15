#pragma once

#include <gtest/gtest.h>
#include <fstream>

#include "world/Database.h"

using namespace GibEngine;
using namespace GibEngine::World;

class WorldDatabaseTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		database = new Database(FILENAME);

		level = database->CreateLevel(strdup(LEVEL_NAME));
		skybox = new Skybox(SKYBOX_NAME[0], SKYBOX_NAME[1]);

		model = new Model(MODEL_NAME);
		modelMatrix = glm::mat4();
	}

	virtual void TearDown()
	{
		database->Disconnect();
		int res = std::remove(FILENAME);

		// delete database;
		// delete level;
		// delete model;
	}

	const char* FILENAME = "test.db";
	const char* LEVEL_NAME = "E1M1: At Doom's Gate";
	const char* MODEL_NAME = "brickwall/brickwall.obj";
	const char* SKYBOX_NAME[2] = { "default", "png" };
	
	Database* database;
	Level* level;
	Skybox* skybox;

	Model* model;
	glm::mat4 modelMatrix;
};