#pragma once


#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>


namespace sparky {
	namespace graphics {

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window {
		private:
			const char *m_Title;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;

			bool m_Keys[MAX_KEYS];
			bool m_Buttons[MAX_BUTTONS];
			bool m_KeyState[MAX_KEYS];
			bool m_ButtonState[MAX_BUTTONS];
			bool m_KeyTouched[MAX_KEYS];
			bool m_ButtonTouched[MAX_BUTTONS];

			double mx, my;
		public:
			Window(const char *name, int width, int height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidth() { return m_Width; };
			inline int getHeight() { return m_Height; };

			bool isKeyPressed(unsigned int keycode) const;
			bool isKeyTouched(unsigned int keycode) const;
			bool isKeyReleased(unsigned int keycode) const;

			bool isButtonPressed(unsigned int button) const;
			bool isButtonTouched(unsigned int button) const;
			bool isButtonReleased(unsigned int button) const;

			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend static void window_resize(GLFWwindow *window, int width, int height);
			friend static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
			friend static void button_callback(GLFWwindow *window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
		};
	}
}