#pragma once

#include <unistd.h>

#include "gtest/gtest.h"

#include "filesystem/UnixFileSystem.h"

using namespace GibEngine;
using namespace GibEngine::FileSystem;

class UnixFileSystemTest : public ::testing::Test
{
public:
	const std::string testText = R"(
		"Hey look, buddy, I'm an Engineer. That means I solve problems.
        Not problems like 'what is beauty?', because that would fall 
        within the purview of your conundrums of philosophy. 
        I solve practical problems.
	)"; // engineer is credit to team
};