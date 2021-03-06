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


#ifndef GAME_TIMER_H
#define GAME_TIMER_H

#include <bitset>
#include <thread>

namespace game
{
	/**
	 * @brief Generates empty events for GLFW
	 */
	class Timer
	{
		int _tickRate;
		std::bitset<2> _stopSet;
		static const int _SHOULD_STOP = 0;
		static const int _IS_STOPPED = 1;
		
		void _threadMethod();
		std::thread _thread;

		inline bool ShouldStop() const;
		inline bool IsStopped() const;

	public:
		explicit Timer(int tickRate) : _tickRate(tickRate) 
		{ 
			_stopSet.set(_IS_STOPPED);
		}
		void Start();
		void Stop();
		~Timer();
	};

	bool Timer::ShouldStop() const
	{
		return _stopSet.test(_SHOULD_STOP);
	}

	bool Timer::IsStopped() const
	{
		return _stopSet.test(_IS_STOPPED);
	}

}

#endif
