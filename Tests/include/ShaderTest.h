#include "gtest/gtest.h"

using namespace GibEngine;

class ShaderTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    shader = new GibEngine::Shader()
  }
  
  Shader *shader;
};
}