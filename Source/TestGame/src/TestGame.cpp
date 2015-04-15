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
#include <Game/Timer.h>
#include <Game/Scene.h>
#include <Game/Sprite.h>

#include <iostream>
#include <typeinfo>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

int main(int argc, char *argv[])
{
	using namespace oglplus;

	//glewExperimental = GL_TRUE;
	glfwInit();
	
	GLFWwindow *window = glfwCreateWindow(400, 400, "Test", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glewInit();
	//glGetError();
	
	game::Scene scene;
	scene.StartLogicThread();

	game::Sprite sprite;
	while (!glfwWindowShouldClose(window))
	{
		
		scene.LockToSyncThreads();
		scene.Render();
		
		sprite.Test();
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwWaitEvents();
	}
	scene.StopLogicThread();

	return 0;
}

