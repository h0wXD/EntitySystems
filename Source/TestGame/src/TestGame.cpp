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
#include <Game/Scene.h>
#include <Game/Sprite.h>
#include <Game/InstancingTest.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <oglplus/gl.hpp>

int main(int argc, char *argv[]);

#ifdef _WIN32
#include <windows.h>
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	return main(0, nullptr);
}
#endif

int main(int argc, char ** argv)
{
	using namespace oglplus;

	//glewExperimental = GL_TRUE;
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	auto window = glfwCreateWindow(800, 400, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	//glGetError();
	
	game::Scene scene;
	scene.StartLogicThread();

	game::Sprite sprite;

	game::InstancingTest test;
	while (!glfwWindowShouldClose(window))
	{
		
		scene.LockToSyncThreads();
		scene.Render();
		
		glViewport(0, 0, 400, 400);
		sprite.Test();
		glViewport(400, 0, 400, 400);
		test.Test();
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwWaitEvents();
	}
	scene.StopLogicThread();

	return 0;
}

