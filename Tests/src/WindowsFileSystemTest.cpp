#include "WindowsFileSystemTest.h"

TEST_F(WindowsFileSystemTest, ReadFile)
{
	const std::string filename = "testfile.txt";

	std::ofstream testFile(filename);
	testFile << testText;
	testFile.close();

	std::shared_ptr<std::string> fileBuffer = std::unique_ptr<std::string>(new std::string());
	WindowsFileSystem fs;

	fs.ReadFile(filename, fileBuffer);

	ASSERT_TRUE(fileBuffer->compare(testText));

	std::remove(filename.c_str());
}

TEST_F(WindowsFileSystemTest, CreateDir)
{
	const std::string newDirectory = "./WindowsFileSystemTest_CreateDir_TestDirectory";
	WindowsFileSystem fs;

	bool res = fs.CreateDir(newDirectory);

	ASSERT_TRUE(res);

	RemoveDirectory(newDirectory.c_str());
}

TEST_F(WindowsFileSystemTest, GetFileList)
{
	const std::string listDir = "./WindowsFileSystemTest_GetFileList_TestDirectory";
	const std::vector<std::string> files = { "FileA.txt", "FileB.txt", "FileC.txt" };
	WindowsFileSystem fs;

	std::shared_ptr<std::string> writeBuf = std::shared_ptr<std::string>(new std::string(testText));

	ASSERT_TRUE(fs.CreateDir(listDir));

	for (auto file : files)
	{
		fs.WriteFile((listDir + std::string("/") + file), writeBuf);
	}

	std::vector<std::string> flist = fs.GetFileList(listDir, "*");

	ASSERT_EQ(flist.at(0), listDir + "/" + files[0]);
	ASSERT_EQ(flist.at(1), listDir + "/" + files[1]);
	ASSERT_EQ(flist.at(2), listDir + "/" + files[2]);
}

TEST_F(WindowsFileSystemTest, WriteFile)
{
	const std::string testFile = "./WindowsFileSystemTest_WriteFile.txt";
	WindowsFileSystem fs;
	
	std::shared_ptr<std::string> writeBuf = std::shared_ptr<std::string>(new std::string(testText));

	fs.WriteFile(testFile, writeBuf);

	std::ifstream filestream(testFile);
	
	std::stringstream ss;
	ss << filestream.rdbuf();

	ASSERT_STREQ(testText.c_str(), ss.str().c_str());

}