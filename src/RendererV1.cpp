#include "RendererV1.h"
#include "WindowV2.h"
#include "GLV1.h"
#include "ErrorV1.h"

using namespace std;

namespace o2
{
	namespace v1
	{
		v3::Shader* Renderer::ensureDefaultShader()
		{
			static bool loaded = false;
			if (!loaded)
			{
				_defaultShader.loadDefaultShader();
				loaded = true;
			}

			return &_defaultShader;
		}

		void Renderer::draw(const std::vector<Vertex>& vertices, PrimitiveType primitiveType, v3::Shader* shader) 
		{
			if (vertices.empty())
				return;

			if (shader == NULL)
				shader = ensureDefaultShader();

			shader->setupDraw(vertices);

			GL_CHECK(glDrawArrays((GLenum)primitiveType, 0, vertices.size()));

			shader->cleanupDraw();
		}
	}
}