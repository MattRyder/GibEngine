#pragma once

#include "GL/gl3w.h"
#include <GLFW/glfw3.h>
#include "Logger.h"

namespace GibEngine
{
	namespace Input
	{
		class Controller
		{
			int controllerId;
			bool connected;

			int axisCount;
			int buttonCount;

			float* axis;
			unsigned char* buttons;

		public:
			Controller(int controllerId);
			Controller(int controllerId, bool connected);
			void Poll(float deltaTime);

			bool IsConnected() const;
			int GetControllerId() const;

			void SetConnected(bool value);
		};
	}
}