#include "LightBaseTest.h"

TEST_F(LightBaseTest, GetAmbientColor)
{
    ASSERT_EQ(lightBase->GetAmbientColor(), ambientColor);
}

TEST_F(LightBaseTest, GetDiffuseColor)
{
    ASSERT_EQ(lightBase->GetDiffuseColor(), diffuseColor);
}
TEST_F(LightBaseTest, GetSpecularColor)
{
    ASSERT_EQ(lightBase->GetSpecularColor(), specularColor);
}