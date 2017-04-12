#pragma once

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "renderer/RenderPass.h"

// class MockRenderPass : public GibEngine::Renderer::RenderPass {
//   public:
//     MOCK_METHOD0(Render, void());
//     MOCK_METHOD1(AddDrawable, void(GibEngine::Entity *));
// };

// class RenderPassTest : public ::testing::Test 
// {
//   protected:
//     virtual void SetUp() 
//     {
//       pass = new MockRenderPass(nullptr);
//     }

//   MockRenderPass *pass;  
// };