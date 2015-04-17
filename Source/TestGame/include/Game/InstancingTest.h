#ifndef GAME_INSTANCING_TEST_H
#define GAME_INSTANCING_TEST_H

#include <GL/glew.h>
#include <iostream>
#include <random>

namespace game
{

	class InstancingTest
	{
		GLuint _program;
		GLuint _vao;
		GLuint _instanceVbo;

		float *_translations;

	public:
		InstancingTest()
		{
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_real_distribution<float> distribution{ -1, 1 };
			_translations = new float[400];
			for (int i = 0; i < 400; ++i)
			{
				_translations[i] = distribution(gen);
			}

			static const float vertices[] =
			{
				-0.5f, 0.5f,
				0.5f, -0.5f,
				-0.5f, -0.5f
			};

			GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			{
				const char *src =
					"#version 330 core\n"
					"layout (location = 0) in vec2 aPosition;"
					"layout (location = 1) in vec2 aTranslation;"

					"void main()"
					"{"
					"   gl_Position.xy = aPosition * 0.1f + aTranslation;"
					"   gl_Position.zw = vec2(0, 1);"
					"}";

				glShaderSource(vertexShader, 1, &src, nullptr);
				glCompileShader(vertexShader);

				GLint success;
				glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					GLchar log[512];
					glGetShaderInfoLog(vertexShader, 512, nullptr, log);
					std::cerr << log << std::endl;
				}
			}

			{
				const char *src =
					"#version 330 core\n"
					"out vec4 _color;"
					"void main()"
					"{"
					"   _color = vec4(1, 0, 1, 1);"
					"}";
				glShaderSource(fragmentShader, 1, &src, nullptr);
				glCompileShader(fragmentShader);

				GLint success;
				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
				if (!success)
				{
					GLchar log[512];
					glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
					std::cerr << log << std::endl;
				}
			}
			
			_program = glCreateProgram();
			glAttachShader(_program, vertexShader);
			glAttachShader(_program, fragmentShader);
			glLinkProgram(_program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			GLuint vbo;
			glGenVertexArrays(1, &_vao);
			glGenBuffers(1, &vbo);
			glGenBuffers(1, &_instanceVbo);

			glBindVertexArray(_vao);
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, _instanceVbo);
				glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableVertexAttribArray(1);
				glVertexAttribDivisor(1, 1);

				glBufferData(GL_ARRAY_BUFFER, 400 * 4, nullptr, GL_STREAM_DRAW);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
			}
			glBindVertexArray(0);
			
		}

		void Test() 
		{ 
			static float time;
			time += 0.02f;
			float *pTranslations = _translations;
			for (int i = 0; i < 200; ++i, pTranslations += 2)
			{
				*pTranslations += ::cos(time) * 0.01f;
				*(pTranslations + 1) += ::sin(time * *pTranslations) * 0.01f;
			}
			glBindVertexArray(_vao);
			
			glBindBuffer(GL_ARRAY_BUFFER, _instanceVbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, 400 * sizeof(float), _translations);
			glUseProgram(_program);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 200);
			
		}
	};
}

#endif
