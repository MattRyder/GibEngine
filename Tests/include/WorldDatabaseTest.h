#pragma once

#include <gtest/gtest.h>
#include <fstream>

#include "world/Database.h"
#include "mocks/MockGraphicsApi.h"

using namespace GibEngine;
using namespace GibEngine::World;
using namespace GibEngine::Renderer::API;
using testing::AtLeast;
using testing::_;
using testing::NiceMock;
using testing::Return;

class WorldDatabaseTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		light = std::unique_ptr<PointLight>(new PointLight(glm::vec3(), glm::vec3(0.5f), glm::vec3(0.75f), glm::vec3(0.25f), 0.800f, 1.0f));

#ifdef WIN32
		fs = std::shared_ptr<FileSystem::IFileSystem>(new FileSystem::WindowsFileSystem());
#elif __unix__
		fs = std::shared_ptr<FileSystem::IFileSystem>(new FileSystem::UnixFileSystem());
#endif
		auto ptr = std::shared_ptr<MeshUploadTicket>(new MeshUploadTicket());

		NiceMock<MockGraphicsApi>* mock = new NiceMock<MockGraphicsApi>();
		std::shared_ptr<NiceMock<MockGraphicsApi>> graphicsApi = std::shared_ptr<NiceMock<MockGraphicsApi>>(mock);

		EXPECT_CALL(*mock, UploadMesh(_, _))
			.Times(AtLeast(1))
			.WillOnce(Return(ptr));

		auto skyboxMesh = MeshService::Generate(graphicsApi, MeshService::CUBE_GENERATION_JSON);
		auto cubemap = MeshService::LoadCubemap(graphicsApi, fs->GetWorkingDirectory() + SKYBOX_NAME[0], SKYBOX_NAME[1]);

		database = std::unique_ptr<Database>(new Database(FILENAME, fs, graphicsApi, false));
		skybox = std::unique_ptr<Skybox>(new Skybox(skyboxMesh, cubemap));
	}

	virtual void TearDown()
	{
		if (database != nullptr)
		{
			database->Disconnect();
		}

		int res = std::remove(FILENAME.c_str());
	}

	const std::string FILENAME = "test.db";
	const std::string MESH_NAME = "/../../Assets/Models/brickwall/brickwall.obj";
	const std::string SKYBOX_NAME[2] = { "/../../Assets/Skybox/default", "png" };
	
	std::unique_ptr<Database> database;
	std::unique_ptr<Skybox> skybox;
	std::unique_ptr<PointLight> light;

	std::shared_ptr<FileSystem::IFileSystem> fs;
	std::shared_ptr<MockGraphicsApi> graphicsApi;
};