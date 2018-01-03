#include "WorldDatabaseTest.h"

TEST_F(WorldDatabaseTest, Constructor_DatabaseCreated)
{
    std::ifstream databaseFile(FILENAME);

    bool dbCreated = databaseFile.good();

    ASSERT_TRUE(dbCreated);
}

TEST_F(WorldDatabaseTest, SaveSkybox)
{
	Scene::Node* sbNode = new Scene::Node("Skybox Node");
	sbNode->GetDatabaseRecord()->SetEntityState(DatabaseRecord::State::NEW);
	sbNode->SetEntity(skybox);

	bool res = database->SaveSkybox(sbNode);

	ASSERT_TRUE(res);
	ASSERT_EQ(sbNode->GetDatabaseRecord()->GetEntityId(), 1);
	ASSERT_EQ(sbNode->GetDatabaseRecord()->GetEntityState(), DatabaseRecord::State::CLEAN);
}

TEST_F(WorldDatabaseTest, SaveMesh)
{
	auto meshRootNode = *mesh->GetChildNodesBegin();
	bool res = database->SaveMesh(meshRootNode);

	ASSERT_TRUE(res);
	ASSERT_EQ(meshRootNode->GetDatabaseRecord()->GetEntityId(), 1);
	ASSERT_EQ(meshRootNode->GetDatabaseRecord()->GetEntityState(), DatabaseRecord::State::CLEAN);
}

TEST_F(WorldDatabaseTest, SavePointLight)
{
	Scene::Node* lNode = new Scene::Node("Light Node");
	lNode->SetEntity(light);

	bool res = database->SavePointLight(lNode);

	ASSERT_TRUE(res);
	ASSERT_EQ(lNode->GetDatabaseRecord()->GetEntityId(), 1);
	ASSERT_EQ(lNode->GetDatabaseRecord()->GetEntityState(), DatabaseRecord::State::CLEAN);
}

TEST_F(WorldDatabaseTest, SaveNode)
{
	Scene::Node* node = new Scene::Node("New Node");

	bool res = database->SaveLevel(node);

	ASSERT_TRUE(res);
	ASSERT_EQ(node->GetDatabaseRecord()->GetId(), 1);
	ASSERT_EQ(node->GetDatabaseRecord()->GetState(), DatabaseRecord::State::CLEAN);
}

TEST_F(WorldDatabaseTest, UpdateSkybox)
{
	const char* NEW_NAME = "AffrontedClimate";

	Scene::Node* node = new Scene::Node("Skybox Node");
	node->SetEntity(skybox);

	bool res = database->SaveSkybox(node);

	ASSERT_TRUE(res);

	node->ModifyEntity()->SetName(NEW_NAME);

	ASSERT_EQ(node->GetDatabaseRecord()->GetEntityState(), DatabaseRecord::State::DIRTY);

	bool res2 = database->SaveSkybox(node);

	ASSERT_TRUE(res2);

	delete node;
}

TEST_F(WorldDatabaseTest, UpdatePointLight)
{
	Scene::Node* lNode = new Scene::Node("Light Node");
	lNode->SetEntity(light);

	bool res = database->SavePointLight(lNode);

	ASSERT_TRUE(res);

	auto modifiedLight = reinterpret_cast<PointLight*>(lNode->GetEntity());
	modifiedLight->SetDiffuseColor(glm::vec3(0.64f));

	bool res2 = database->SavePointLight(lNode);

	ASSERT_TRUE(res2);
	ASSERT_EQ(lNode->GetDatabaseRecord()->GetEntityState(), DatabaseRecord::State::CLEAN);
}

TEST_F(WorldDatabaseTest, UpdateNode)
{
	Scene::Node* node = new Scene::Node("New Node");

	bool res = database->SaveLevel(node);
	ASSERT_TRUE(res);

	node->SetLocalTransform(glm::translate(node->GetLocalTransform(), glm::vec3(2.0f)));

	bool res2 = database->SaveLevel(node);
	ASSERT_TRUE(res2);

	ASSERT_EQ(node->GetDatabaseRecord()->GetId(), 1);
	ASSERT_EQ(node->GetDatabaseRecord()->GetState(), DatabaseRecord::State::CLEAN);
}

TEST_F(WorldDatabaseTest, DeleteNode)
{
	Scene::Node* node = new Scene::Node("New Node");

	bool res = database->SaveLevel(node);
	ASSERT_TRUE(res);

	node->GetDatabaseRecord()->SetState(DatabaseRecord::State::DELETED);
	bool res2 = database->SaveLevel(node);
	ASSERT_TRUE(res2);

	Scene::Node* readback = database->LoadLevel(1);
	ASSERT_EQ(readback, nullptr);

}