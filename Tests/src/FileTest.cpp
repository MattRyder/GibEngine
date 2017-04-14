#include "FileTest.h"

TEST_F(FileTest, GetModelPath)
{
  File *fp = File::GetModelFile("AssetFile");

  std::string expectedTail = "/Assets/Models/AssetFile";
  std::string path = std::string(fp->GetPath());

  // Check we get a path back:
  ASSERT_TRUE(path.length() > 0);

  auto actualTail = path.substr(path.length() - expectedTail.length(), expectedTail.length());
  // And check that the tail ends with a reference to the Assets folder, to the Asset
  ASSERT_EQ(expectedTail, actualTail);
}

TEST_F(FileTest, GetShaderPath)
{
  File *fp = File::GetShaderFile("foo.glsl");

  std::string expectedTail = "/Assets/Shaders/foo.glsl";
  std::string path = std::string(fp->GetPath());

  // Check we get a path back:
  ASSERT_TRUE(path.length() > 0);

  auto actualTail = path.substr(path.length() - expectedTail.length(), expectedTail.length());
  // And check that the tail ends with a reference to the Assets folder, to the Asset
  ASSERT_EQ(expectedTail, actualTail);
}

TEST_F(FileTest, GetDirectory)
{
  std::string fullFilePath = "/ParentDir/ChildDir/File";
  std::string expectedPath = "/ParentDir/ChildDir";
  File *file = new File(fullFilePath.c_str());

  std::string actualPath = file->GetDirectory();
  ASSERT_EQ(expectedPath, actualPath);
}

TEST_F(FileTest, GetPath)
{
  std::string fullFilePath = "/ParentDir/ChildDir/File";
  File *fp = new File(fullFilePath.c_str());
  
  std::string actualFilePath = fp->GetPath();
  ASSERT_EQ(fullFilePath, actualFilePath);
}

TEST_F(FileTest, ReadFile) 
{
  const char *expectedFileContent = "Hello World";
  const char *fileName = "testfile.txt";

  // Gonna obviously want to create a file here:
  std::ofstream testFile;
  testFile.open(fileName);
  testFile << expectedFileContent;
  testFile.close();
  
  // Then it might be an idea to read it back:
  File *file = new File(fileName);
  
  const char *actualFileContent = file->ReadFile();
  
  ASSERT_STREQ(expectedFileContent, actualFileContent);
}