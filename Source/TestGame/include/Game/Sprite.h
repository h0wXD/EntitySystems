/********************************************************************************
 │ 
 │  ╔═════════════╗
 │  ║EntitySystems║
 │  ╚═════════════╝
 ╰╼━━━━━━━━━━━━━━━━━━━━━━━╾
                                                                                
   Copyright (c) 2015 h0wXD & LorenzJ.                                          
   https://github.com/h0wXD                                                     
   https://github.com/LorenzJ                                                   
                                                                                
   Permission is hereby granted, free of charge, to any person obtaining a copy 
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights 
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell    
   copies of the Software, and to permit persons to whom the Software is        
   furnished to do so, subject to the following conditions:                     
                                                                                
   The above copyright notice and this permission notice shall be included in   
   all copies or substantial portions of the Software.                          
                                                                                
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR   
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,     
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE  
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER       
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN    
   THE SOFTWARE.                                                                
 ********************************************************************************/


#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H

#include <GL/glew.h>
#include <GL/GL.h>
#include <iostream>

namespace game
{

	class Sprite
	{
		GLuint _vao;
		GLuint _program; // Temporary
	public:
		Sprite()
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glGenVertexArrays(1, &_vao);
			
			float vertices[] =
			{ -0.5f,  0.5f, //0,
			   0.5f, -0.5f, //0,
			  -0.5f, -0.5,  //0,

			  -0.5f,  0.5f, //0,
			   0.5f,  0.5f, //0,
			   0.5f, -0.5f, //0,
			};
			glBindVertexArray(_vao);
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
				glEnableVertexAttribArray(0);
			}
			glBindVertexArray(0);

			GLuint vertexShader;
			const char *vertexSource =
				"#version 330 core\n"
				"layout (location = 0) in vec2 position;"
				"uniform vec2 offset;"

				"void main(void)"
				"{"
				"   gl_Position = vec4(position + offset, 0.0f, 1.0f);"
				"}";

			vertexShader = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vertexShader, 1, &vertexSource, nullptr);
			glCompileShader(vertexShader);

			GLuint fragmentShader;
			const char *fragmentSource =
				"#version 330 core\n"
				"out vec4 color;"

				"void main(void)"
				"{"
				"   color = vec4(1.0f, 0.5f, 0.5f, 1.0f);"
				"}";

			fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
			glCompileShader(fragmentShader);
			
			GLint success;
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				GLchar log[512];
				glGetShaderInfoLog(vertexShader, 512, nullptr, log);
				std::cerr << log << std::endl;
			}

			glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				GLchar log[512];
				glGetShaderInfoLog(fragmentShader, 512, nullptr, log);
				std::cerr << log << std::endl;
			}

			_program = glCreateProgram();
			glAttachShader(_program, vertexShader);
			glAttachShader(_program, fragmentShader);
			glLinkProgram(_program);

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
		}

		void Test()
		{
			static float x;
			x += 0.02f;
			glUseProgram(_program);
			glUniform2f(glGetUniformLocation(_program, "offset"), x, 0);
			glBindVertexArray(_vao);
			
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	};
}

#endif
