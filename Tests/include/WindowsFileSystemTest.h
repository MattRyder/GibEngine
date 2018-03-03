#pragma once

#include "gtest/gtest.h"

#include "filesystem/WindowsFileSystem.h"

using namespace GibEngine;
using namespace GibEngine::FileSystem;

class WindowsFileSystemTest : public ::testing::Test
{
public:
	const std::string testText = R"(
		The right man in the wrong place can make all the difference in the world.
		So, wake up, Mister Freeman. Wake up and... *smell the ashes*...
	)";
};