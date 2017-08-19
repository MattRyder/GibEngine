#pragma once

#include "gtest/gtest.h"

#include "input/InputManager.h"

using namespace GibEngine;

class InputManagerTest : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
		inputManager = new Input::InputManager(nullptr);
    }

    virtual void TearDown() 
    {
      delete inputManager;
    }

  public:
    Input::InputManager* inputManager;
};