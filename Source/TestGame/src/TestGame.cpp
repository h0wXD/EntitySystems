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


#include <ES/System.h>
#include <Game/DumbEnemySystem.h>
#include <iostream>
#include <typeinfo>
#include <chrono>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

int main(int argc, char *argv[])
{
	using namespace oglplus;

	glewExperimental = GL_TRUE;
	glfwInit();
	
	GLFWwindow *window = glfwCreateWindow(400, 400, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	//glGetError();
	
	try
	{
		Context context;
		VertexShader vs;
		FragmentShader fs;
		Program program;
		VertexArray triangle;
		Buffer vertices;
		Buffer colors;
		vs.Source("#version 330\n"
			"in vec3 Position;"
			"in vec3 Color;"
			"out vec4 vertexColor;"
			"void main(void)"
			"{"
			"	gl_Position = vec4(Position, 1.0);"
			"   vertexColor = vec4(Color, 1.0);"
			"}");

		fs.Source("#version 330\n"
			"in vec4 vertexColor;"
			"out vec4 fragColor;"
			"void main(void)"
			"{"
			"   fragColor = vertexColor;"
			"}");

		vs.Compile();
		fs.Compile();
		program.AttachShader(vs);
		program.AttachShader(fs);
		program.Link();

		triangle.Bind();
		{
			GLfloat triangle_verts[9] = {
				0.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f
			};
			vertices.Bind(Buffer::Target::Array);
			Buffer::Data(Buffer::Target::Array, 9, triangle_verts);
			VertexArrayAttrib(program, "Position").Setup<GLfloat>(3).Enable();

			GLfloat triangle_colors[9] = {
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
			};
			colors.Bind(Buffer::Target::Array);
			Buffer::Data(Buffer::Target::Array, 9, triangle_colors);
			VertexArrayAttrib(program, "Color").Setup<GLfloat>(3).Enable();
		}

		program.Use();
		auto oldTime = std::chrono::high_resolution_clock::now();
		decltype(oldTime) newTime = oldTime + std::chrono::milliseconds(16);
		decltype(newTime - oldTime) deltaTime;
		decltype(deltaTime) accumulatedTime = std::chrono::milliseconds(0);
		while (!glfwWindowShouldClose(window))
		{
			using std::chrono::high_resolution_clock;
			using std::chrono::milliseconds;
			const int maxFrameRate = 160;

			deltaTime = newTime - oldTime;
			accumulatedTime += deltaTime;
			oldTime = newTime;
			
			while (accumulatedTime.count() > 0)
			{
				auto timeStep = std::chrono::milliseconds(1000 / maxFrameRate);
				std::this_thread::sleep_for(timeStep / 2);
				accumulatedTime -= timeStep;
				// logic(timeStep)
			}
			context.Clear().ColorBuffer();
			context.DrawArrays(PrimitiveType::Triangles, 0, 3);
			glfwSwapBuffers(window);
			glfwPollEvents();

			newTime = high_resolution_clock::now();
		}

		glfwTerminate();

	}
	catch (Error &e)
	{
		std::cerr << e.what() << '\n' << e.Log() << std::endl;
	}
	

	game::DumbEnemySystem system(100);
	
	{
		auto reference = system.Add();
		auto instance = system.GetInstance(reference);
		instance.Health() = 5.f;
	}

	{
		auto reference = system.Add();
		auto instance = system.GetInstance(reference);
		instance.Health() = -0.5f;
	}
	
	system.Tick(0.16f);
	return 0;
}

