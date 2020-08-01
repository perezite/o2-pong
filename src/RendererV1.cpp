#include "RendererV1.h"
#include "ShaderV2.h"
#include "GLV1.h"

namespace o2
{
	namespace v1
	{
		namespace
		{
			void ensureDefaultShader(v2::Shader& shader) 
			{
				static bool defaultShaderInitialized = false;
				if (!defaultShaderInitialized)
				{
					shader.loadDefaultShader();
					defaultShaderInitialized = true;
				}
			}

		}

		void Renderer::draw(const std::vector<Vertex>& vertices, PrimitiveType primitiveType)
		{
			if (vertices.empty())
				return;

			ensureDefaultShader(_defaultShader);
			glUseProgram(_defaultShader.getGlShaderProgram());

			
			GL_CHECK(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), &(vertices[0])));
			GL_CHECK(glEnableVertexAttribArray(0));

			GL_CHECK(glDrawArrays((GLenum)primitiveType, 0, vertices.size()));

			GL_CHECK(glDisableVertexAttribArray(0));


			//const GLfloat myVertices[] =
			//{
			//	-.5f,  -.5f,
			//	 .5f, -0.5f,
			//	   0,  0.5f
			//};

			//glClear(GL_COLOR_BUFFER_BIT);

			//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, myVertices);
			//glEnableVertexAttribArray(0);

			//glDrawArrays(GL_TRIANGLES, 0, 3);
		}
	}
}