#include "texture.h"

namespace sparky {
	namespace graphics {
		Texture::Texture(const std::string& filename) : m_Filename(filename) {
			load();
		}

		Texture::~Texture() {

		}

		GLuint Texture::load() {
			BYTE* pixels = load_image(m_Filename.c_str(), &m_Width, &m_Height, &m_BBP);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			if (m_BBP == 24) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
			}
			else if (m_BBP == 32) {
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
			} else {
				std::cout << m_Filename << ": " << m_BBP << " is an unsupported bit-depth!" << std::endl;
			}
			
			glBindTexture(GL_TEXTURE_2D, 0);

			m_TID = result;
			
			return result;
		}

		void Texture::bind() const {
			glBindTexture(GL_TEXTURE_2D, m_TID);
		}

		void Texture::unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

	}
}