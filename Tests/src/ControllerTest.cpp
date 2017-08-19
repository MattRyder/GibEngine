#include "ControllerTest.h"

TEST_F(ControllerTest, GetControllerId)
{
	int actualControllerId = controller->GetControllerId();
	int expectedControllerId = 1;

	ASSERT_EQ(actualControllerId, expectedControllerId);
}

TEST_F(ControllerTest, GetIsConnected)
{
	bool actuallyConnected = controller->IsConnected();
	bool expectedlyConnected = true;

	ASSERT_EQ(actuallyConnected, expectedlyConnected);
}

TEST_F(ControllerTest, SetIsConnected)
{
	controller->SetConnected(false);

	ASSERT_EQ(controller->IsConnected(), false);
}