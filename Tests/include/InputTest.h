#pragma once

#include "gtest/gtest.h"

#include "Input.h"

using namespace GibEngine;

class InputTest : public ::testing::Test
{
  protected:
    virtual void SetUp()
    {
      input = new Input(1);
    }

    virtual void TearDown() 
    {
      delete input;
    }

  public:
    Input *input;
};