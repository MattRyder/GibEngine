#include "FileTest.h"

TEST_F(FileTest, GetAssetPath)
{
  File *fp = File::GetAssetPath("AssetFile");

  std::string expectedTail = std::string("/Assets/AssetFile");
  std::string path = std::string(fp->GetPath());

  // Check we get a path back:
  ASSERT_TRUE(path.length() > 0);

  auto sub = path.substr(path.length() - expectedTail.length(), expectedTail.length());
  // And check that the tail ends with a reference to the Assets folder, to the Asset
  ASSERT_EQ(expectedTail, sub);
}