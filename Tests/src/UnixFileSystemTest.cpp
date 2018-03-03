#include "UnixFileSystemTest.h"

TEST_F(UnixFileSystemTest, ReadFile)
{
	const std::string filename = "testfile.txt";

	std::ofstream testFile(filename);
	testFile << testText;
	testFile.close();

	std::shared_ptr<std::string> fileBuffer = std::unique_ptr<std::string>(new std::string());
	UnixFileSystem fs;

	fs.ReadFile(filename, fileBuffer);

	ASSERT_TRUE(fileBuffer->compare(testText));

	std::remove(filename.c_str());
}

TEST_F(UnixFileSystemTest, CreateDir)
{
	UnixFileSystem fs;

	const std::string newDirectory = fs.GetWorkingDirectory() + "/UnixFileSystemTest_CreateDir_TestDirectory";
	bool res = fs.CreateDir(newDirectory);

	ASSERT_TRUE(res);

	std::remove(newDirectory.c_str());
}

TEST_F(UnixFileSystemTest, GetFileList)
{
	UnixFileSystem fs;
	const std::vector<std::string> files = { "FileA.txt", "FileB.txt", "FileC.txt" };
	const std::string listDir = fs.GetWorkingDirectory() + "/UnixFileSystemTest_GetFileList_TestDirectory";

	std::shared_ptr<std::string> writeBuf = std::shared_ptr<std::string>(new std::string(testText));

	ASSERT_TRUE(fs.CreateDir(listDir));

	for (auto file : files)
	{
		fs.WriteFile((listDir + std::string("/") + file), writeBuf);
	}

	std::vector<std::string> flist = fs.GetFileList(listDir, "*");

	for(auto file : files)
	{
		auto filePos = std::find(flist.begin(), flist.end(), listDir + "/" + file);
		ASSERT_NE(filePos, flist.end());

	}

	std::remove(listDir.c_str());
}

TEST_F(UnixFileSystemTest, WriteFile)
{
	const std::string testFile = "./UnixFileSystemTest_WriteFile.txt";
	UnixFileSystem fs;
	
	std::shared_ptr<std::string> writeBuf = std::shared_ptr<std::string>(new std::string(testText));

	fs.WriteFile(testFile, writeBuf);

	std::ifstream filestream(testFile);
	
	std::stringstream ss;
	ss << filestream.rdbuf();

	ASSERT_STREQ(testText.c_str(), ss.str().c_str());

	std::remove(testFile.c_str());
}