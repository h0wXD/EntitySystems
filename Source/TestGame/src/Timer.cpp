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


#include <Game/Timer.h>
#include <GLFW/glfw3.h>
#include <chrono>

namespace game
{
	void Timer::_threadMethod()
	{
		using std::chrono::high_resolution_clock;
		using std::chrono::microseconds;
		auto nextEventTime = high_resolution_clock::now() + microseconds(1000000 / _tickRate);
		while (!ShouldStop())
		{
			std::this_thread::sleep_for(microseconds(1000000 / (_tickRate * 2)));
			if (high_resolution_clock::now() > nextEventTime)
			{
				nextEventTime += microseconds(1000000 / _tickRate);
				glfwPostEmptyEvent();
				std::this_thread::yield();
			}
		}
	}

	void Timer::Start()
	{
		_stopSet.reset(); // Set all to false
		_thread = std::thread(&Timer::_threadMethod, this);
	}

	void Timer::Stop()
	{
		_stopSet.set(_SHOULD_STOP);
		_thread.join();
		_stopSet.set(_IS_STOPPED);
	}

	Timer::~Timer()
	{
		if (!IsStopped())
		{
			Stop();
		}
	}
}
