#include "Window_Demo1.h"
#include "WindowV1.h"
#include "ColorV1.h"
#include "VertexV1.h"
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace o2;

namespace windowDemo1
{
    void demo0()
    {
        v1::Window window(v1::Vector2i(600, 400), "Pong");

        while (window.isOpen())
        {
            window.update();
            window.clear(v1::Color::fromRGBA(0, 255, 0, 255));
            window.display();
        }
    }

	GLuint loadShader1(const char *shaderSrc, GLenum type)
	{
		GLuint shader;
		GLint compiled;

		shader = glCreateShader(type);

		if (shader == 0)
		{
			v1::error() << "Error creating shader" << endl;
			return 0;
		}

		glShaderSource(shader, 1, &shaderSrc, NULL);

		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);
				glGetShaderInfoLog(shader, infoLen, NULL, infoLog);
				string infoLogString(infoLog);
				free(infoLog);
				v1::error() << "Error compiling shader: " << endl << infoLog << endl;
			}

			glDeleteShader(shader);
			return 0;
		}
		return shader;
	}

	GLuint init1()
	{
		const char vertexShaderCode[] =
			"attribute vec4 position;			\n"
			"void main()						\n"
			"{									\n"
			"	gl_Position = position;			\n"
			"}									\n";

		const char fragmentShaderCode[] =
			"precision mediump float;						\n"
			"void main()									\n"
			"{												\n"
			"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);	\n"
			"}												\n";

		GLuint vertexShader;
		GLuint fragmentShader;
		GLuint shaderProgram;
		GLint linked;

		vertexShader = loadShader1(vertexShaderCode, GL_VERTEX_SHADER);
		fragmentShader = loadShader1(fragmentShaderCode, GL_FRAGMENT_SHADER);

		shaderProgram = glCreateProgram();

		if (shaderProgram == 0)
			v1::error() << "error creating shader program" << endl;

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);

		glBindAttribLocation(shaderProgram, 0, "vPosition");

		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linked);

		if (!linked)
		{
			GLint infoLen = 0;
			glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLen);

			if (infoLen > 1)
			{
				char* infoLog = (char*)malloc(sizeof(char) * infoLen);
				glGetProgramInfoLog(shaderProgram, infoLen, NULL, infoLog);
				glDeleteProgram(shaderProgram);
				string infoLogString(infoLog);
				free(infoLog);
				v1::error() << "Error linking program: " << endl << infoLogString << endl;
			}
		}

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		return shaderProgram;
	}

	void draw1(GLuint shaderProgram)
	{
		GLfloat vertices[] = 
		{ 
			 0.0f,  0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f 
		};

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	// https://www.khronos.org/assets/uploads/books/openglr_es_20_programming_guide_sample.pdf
    void demo1()
    {
        v1::Window window(v1::Vector2i(600, 400), "Pong");
		GLuint shaderProgram = init1();

        while (window.isOpen())
        {
            window.update();

			draw1(shaderProgram);

            window.display();
        }
    }
    
    void run()
    {
         demo1();
        //demo0();
    }
}