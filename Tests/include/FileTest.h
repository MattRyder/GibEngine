#pragma once

#include "gtest\gtest.h"

#include "File.h"

class FileTest : public ::testing::Test
{
protected:
    virtual void SetUp() 
    {
      filePath = new std::string("/");
    }

public:
  std::string *filePath;

};

