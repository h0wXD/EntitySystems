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

#include <Game/Basic2DShader.h>

#include <GL/glew.h>
#include <GL/GL.h>
#include <iostream>
#include <cmath>

namespace game
{

	class Sprite
	{
		GLuint _vao;
		GLuint _instanceOffsetVbo;
		GLuint _instanceDepthVbo;
	public:
		Sprite()
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glGenVertexArrays(1, &_vao);
			glGenBuffers(1, &_instanceOffsetVbo);
			glGenBuffers(1, &_instanceDepthVbo);

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
				glEnableVertexAttribArray(1);
				glVertexAttribDivisor(1, 1);
				glEnableVertexAttribArray(2);
				glVertexAttribDivisor(2, 1);
			}
			
		}

		void Test()
		{
			static float time;
			time += 0.01f;

			auto &shader = Basic2DShader::Get();
			
			shader.SetLightCount(3);
			shader.SetLightColor(0, 1.0f, 0, 0);
			shader.SetLightIntensity(0, 2.0f);
			shader.SetLightPosition(0, Vector2f(0, 0));
			shader.SetLightColor(1, 0, 0.2f, 0);
			shader.SetLightPosition(1, Vector2f(-1, 0));
			shader.SetLightIntensity(1, 3.0f);
			shader.SetLightColor(2, 0, 0, ::cos(time) + 1.f);
			shader.SetLightIntensity(2, .18f);
			shader.SetLightPosition(2, Vector2f(::cos(time), ::sin(time)));

			shader.SetAmbientColor(1.0f, 1.0f, 1.0f);
			shader.SetAmbientIntensity(::cos(time * 0.1f));
			shader.Use();

			glBindVertexArray(_vao);
			
			shader.SetOffset(Vector2f(::sin(time), ::sin(time)), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			shader.SetOffset(Vector2f(::sin(-time), ::sin(time)), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			shader.SetOffset(Vector2f(-::sin(time), -::sin(time)), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			shader.SetOffset(Vector2f(-::sin(-time), -::sin(time)), 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

	};
}

#endif
