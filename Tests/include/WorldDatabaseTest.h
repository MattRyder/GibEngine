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

		//level = database->CreateLevel(strdup(LEVEL_NAME));
		skybox = new Skybox(SKYBOX_NAME[0], SKYBOX_NAME[1]);

		File* meshFile = File::GetModelFile(MESH_NAME);
		mesh = MeshService::Load(meshFile, nullptr);
		light = new PointLight(
			glm::vec3(), glm::vec3(0.5f), glm::vec3(0.75f), glm::vec3(0.25f), 0.800f, 1.0f
		);
	}

	virtual void TearDown()
	{
		database->Disconnect();
		int res = std::remove(FILENAME);

		 delete database;
		 delete skybox;
		 delete mesh;
		 delete light;
	}

	const char* FILENAME = "test.db";
	const char* MESH_NAME = "brickwall/brickwall.obj";
	const char* SKYBOX_NAME[2] = { "default", "png" };
	
	Database* database = nullptr;
	Skybox* skybox = nullptr;
	Scene::Node* mesh = nullptr;
	PointLight* light = nullptr;
};