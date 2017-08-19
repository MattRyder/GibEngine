#pragma once

#include <gtest/gtest.h>

#include "input/Controller.h"

using namespace GibEngine;

class ControllerTest : public ::testing::Test
{
public:
	virtual void SetUp()
	{
		controller = new Input::Controller(1, true);
	}

	virtual void TearDown()
	{
		delete controller;
	}

	Input::Controller* controller;
};