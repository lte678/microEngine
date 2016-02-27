#pragma once 

#include "renderable2d.h"

namespace sparky {
	namespace graphics {
		class Label : public Renderable2D {
		private:
			math::vec2 m_TextSize;
		public:
			std::string text;
			math::vec3& position;
			float x, y;
		public:
			Label(std::string text, float x, float y, math::vec4 color);

			void submit(Renderer2D* renderer) const override;
			inline float getWidth() { return m_TextSize.x; };
			inline float getHeight() { return m_TextSize.y; };
		};
	}
}