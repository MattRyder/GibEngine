#include "WorldDatabaseTest.h"

//TEST_F(WorldDatabaseTest, Constructor_DatabaseCreated)
//{
//    std::ifstream databaseFile(FILENAME);
//
//    bool dbCreated = databaseFile.good();
//
//    ASSERT_TRUE(dbCreated);
//}
//
//TEST_F(WorldDatabaseTest, CreateLevel)
//{
//    ASSERT_EQ(level->GetId(), 1);
//}
//
//TEST_F(WorldDatabaseTest, SaveModelToLevel)
//{
//    int levelId = level->GetId();
//
//	World::DatabaseEntity<Model>* modelDbEntity = new World::DatabaseEntity<Model>(0, model);
//
//    bool success = database->SaveModel(levelId, modelDbEntity);
//
//	ASSERT_TRUE(success);
//    ASSERT_TRUE(modelDbEntity->GetId() > 0);
//
//	delete modelDbEntity;
//}
//
//TEST_F(WorldDatabaseTest, SaveInstanceToModel)
//{
//    int levelId = level->GetId();
//
//	World::DatabaseEntity<Model>* modelDbEntity = new World::DatabaseEntity<Model>(0, model);
//    int modelId = database->SaveModel(levelId, modelDbEntity);
//
//	Mesh::Instance* meshInstance = new Mesh::Instance();
//	World::DatabaseEntity<Mesh::Instance>* newDbInstance = new World::DatabaseEntity<Mesh::Instance>(0, meshInstance);
//
//	database->SaveInstance(modelId, newDbInstance);
//
//    ASSERT_TRUE(newDbInstance->GetId() > 0);
//
//	delete newDbInstance;
//	delete modelDbEntity;
//}
//
//TEST_F(WorldDatabaseTest, FindLevel)
//{
//	World::DatabaseEntity<Skybox>* skyInstance = new World::DatabaseEntity<Skybox>(0, skybox);
//    level->SetSkybox(skyInstance);
//
//    database->SaveLevel(level);
//
//    Level* level = database->FindLevel(1);
//    
//    ASSERT_TRUE(level != nullptr);
//    ASSERT_EQ(level->GetId(), 1);
//    ASSERT_STREQ(level->GetName(), LEVEL_NAME);
//}