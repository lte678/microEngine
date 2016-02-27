#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>

#include <iostream>

#include "../utils/imageloader.h"

namespace sparky {
	namespace graphics {

		class Texture {
		private:
			std::string m_Filename;
			GLuint m_TID;
			GLsizei m_Width, m_Height;
			int m_BBP;
		public:
			Texture(const std::string& filename);
			~Texture();
			
			void bind() const;
			void unbind() const;

			inline const unsigned int getWidth() const { return m_Width; }
			inline const unsigned int getHeight() const { return m_Height; }
			inline const unsigned int getID() const { return m_TID; }
		private:
			GLuint load();
		};

	}
}