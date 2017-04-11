#include "gtest/gtest.h"

#include "Shader.h"

// using namespace GibEngine;

class ShaderTest : public ::testing::Test
{
public:
  virtual void SetUp()
  {
    vertexShaderStr ="\
      #version 330\
      layout(location = 0)in vec4 vert;\
      uniform mat4 projection;\
      uniform mat4 view;\
      uniform mat4 model;\
      void main()\
      {\
          gl_Position = projection * view * model * vert;\
      })";

    fragmentShaderStr = "\
      #version 410\
      out vec4 frag_colour;\
      void main () {\
        frag_colour = vec4 (1.0, 1.0, 0.0, 1.0);\
      }";  
  }
  
  GibEngine::Shader *shader;
  const char *vertexShaderStr, *fragmentShaderStr;
};