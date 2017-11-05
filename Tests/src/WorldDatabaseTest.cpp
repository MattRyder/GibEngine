#include "WorldDatabaseTest.h"

TEST_F(WorldDatabaseTest, Constructor_DatabaseCreated)
{
    std::ifstream databaseFile(FILENAME);

    bool dbCreated = databaseFile.good();

    ASSERT_TRUE(dbCreated);
}

TEST_F(WorldDatabaseTest, CreateLevel)
{
    ASSERT_EQ(level->GetId(), 1);
}

TEST_F(WorldDatabaseTest, SaveModelToLevel)
{
    int levelId = level->GetId();
    int modelId = database->SaveModel(levelId, model);

    ASSERT_TRUE(modelId > 0);
}

TEST_F(WorldDatabaseTest, SaveInstanceToModel)
{
    int levelId = level->GetId();
    int modelId = database->SaveModel(levelId, model);
    glm::vec3 v = glm::vec3();
    int instanceId = database->SaveInstance(modelId, v, v, 0.0f, v);

    ASSERT_TRUE(instanceId > 0);
}

TEST_F(WorldDatabaseTest, FindLevel)
{
    level->SetSkybox(skybox);
    database->SaveLevel(level);

    Level* level = database->FindLevel(1);
    
    ASSERT_TRUE(level != nullptr);
    ASSERT_EQ(level->GetId(), 1);
    ASSERT_STREQ(level->GetName(), LEVEL_NAME);
}