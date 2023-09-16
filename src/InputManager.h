#pragma once

namespace GameEngine {
	namespace Input {

		void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
				glfwSetWindowShouldClose(window, true);
			}
		}

		void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
		{
			
		}
	}

	class InputManager {

	};
}