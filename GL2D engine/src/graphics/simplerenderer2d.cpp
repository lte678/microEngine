#include "simplerenderer2d.h"
#include "renderable2d.h"

namespace sparky {
	namespace graphics {

		void SimpleRenderer2D::submit(const Renderable2D* renderable) {
			m_RenderQueue.push_back((StaticSprite*) renderable);
		}

		void SimpleRenderer2D::flush() {

			while (!m_RenderQueue.empty())
			{
				const StaticSprite* renderable = m_RenderQueue.front();
				renderable->getVAO()->bind();
				renderable->getIBO()->bind();

				renderable->getShader().setUniformMat4("ml_matrix", math::mat4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIBO()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getIBO()->unbind();
				renderable->getVAO()->unbind();

				m_RenderQueue.pop_front();
			}
		}

	}
}