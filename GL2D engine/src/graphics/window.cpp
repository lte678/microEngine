#include "window.h"


namespace sparky {
	namespace graphics {

		void window_resize(GLFWwindow *window, int width, int height);
		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
		void button_callback(GLFWwindow *window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height) {
			m_Title = title;
			m_Width = width;
			m_Height = height;
			if (!init()) glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
				m_KeyState[i] = false;
				m_KeyTouched[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_Buttons[i] = false;
				m_ButtonState[i] = false;
				m_ButtonTouched[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed!" << std::endl;
				return false;
			}
			else {
				std::cout << "GLFW Initilized!" << std::endl;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) {
				glfwTerminate();
				std::cout << "Failed to create window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetFramebufferSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			glfwSwapInterval(0.0f);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			return true;
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void Window::update() {
			for (int i = 0; i < MAX_KEYS; i++) {
				m_KeyTouched[i] = m_Keys[i] && !m_KeyState[i];
			}

			memcpy(m_KeyState, m_Keys, MAX_KEYS);

			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_ButtonTouched[i] = m_Buttons[i] && !m_ButtonState[i];
			}

			memcpy(m_ButtonState, m_Buttons, MAX_BUTTONS);

			GLenum error = glGetError();
			if (error != GL_NO_ERROR) {
				std::cout << "OpenGL error: " << error << std::endl;
			}

			glfwPollEvents();
			//glfwGetFramebufferSize(m_Window, &m_Width, &m_Height);
			glfwSwapBuffers(m_Window);
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		//
		//Getters
		//

		bool Window::isKeyPressed(unsigned int keycode) const {
			if (keycode >= MAX_KEYS) return false;
			return m_Keys[keycode];
		}

		bool Window::isKeyTouched(unsigned int keycode) const {
			if (keycode >= MAX_KEYS) return false;
			return m_KeyTouched[keycode];
		}

		bool Window::isKeyReleased(unsigned int keycode) const {
			if (keycode >= MAX_KEYS) return false;
			return !m_Keys[keycode];
		}

		bool Window::isButtonPressed(unsigned int button) const {
			if (button >= MAX_BUTTONS) return false;
			return m_Buttons[button];
		}

		bool Window::isButtonTouched(unsigned int button) const {
			if (button >= MAX_BUTTONS) return false;
			return m_ButtonTouched[button];
		}

		bool Window::isButtonReleased(unsigned int button) const {
			if (button >= MAX_BUTTONS) return false;
			return !m_Buttons[button];
		}

		void Window::getMousePosition(double& x, double& y) const {
			x = mx;
			y = my;
		}

		//
		// GLFW callbacks for window resize, key presses, mouse presses, etc.
		//

		void window_resize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_Width = width;
			win->m_Height = height;
		}

		void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);

 			if (action != GLFW_RELEASE) {
				win->m_Keys[key] = true;
			} else {
				win->m_Keys[key] = false;
			}
		}

		void button_callback(GLFWwindow *window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			if (action != GLFW_RELEASE) {
				win->m_Buttons[button] = true;
			} else {
				win->m_Buttons[button] = false;
			}
		}

		void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->mx = xpos;
			win->my = ypos;
		}
	}
}