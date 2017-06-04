#include "Main.h"

int main(int argc, char *argv[])
{
	GibEngine::Game* game = new GibEngine::Game("GibTest OpenGL Initialization");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}