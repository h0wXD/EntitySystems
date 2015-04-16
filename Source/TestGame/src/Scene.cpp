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


#include <Game/Scene.h>
#include <chrono>

namespace game
{

	Scene::Scene() : _timer(144), _renderingSystem(new RenderingSystem())
	{
		_flags.set(_IS_STOPPED);
	}

	Scene::~Scene()
	{
		if (!IsStopped())
		{
			StopLogicThread();
		}
	}

	void Scene::_logicMethod()
	{
		using std::chrono::microseconds;
		using std::chrono::high_resolution_clock;

		high_resolution_clock::duration timeStepDuration = microseconds(1000000 / 200);
		float timeStepFloat = 1.f / 200.f;
		auto oldTime = high_resolution_clock::now();
		auto newTime = oldTime + timeStepDuration;
		high_resolution_clock::rep accumulatedTime = 0;

		while (!ShouldStop())
		{
			auto deltaTime = newTime - oldTime;
			oldTime = newTime;
			accumulatedTime += deltaTime.count();

			while (accumulatedTime > 0)
			{
				accumulatedTime -= timeStepDuration.count();
				// Do logic
				// Logic(timeStepFloat);
			}

			SetReadyToSync();
			_synchronizeThreads.notify_one();
			{
				std::unique_lock<std::mutex> lock(_mutex);
				_synchronizeThreads.wait(lock, [this] { return IsReadyToResume(); });
			}
			newTime = high_resolution_clock::now();
		}
	}

	void Scene::Render()
	{
		_renderingSystem->Render();
	}

	void Scene::StartLogicThread()
	{
		_timer.Start();
		_logicThread = std::thread(&Scene::_logicMethod, this);
	}

	void Scene::StopLogicThread()
	{
		SetShouldStop();
		_logicThread.join();
		_timer.Stop();
		SetStopped();
	}

	void Scene::LockToSyncThreads()
	{
		{
			std::unique_lock<std::mutex> lock(_mutex);
			_synchronizeThreads.wait(lock, [this] { return IsReadyToSync(); });
			//_renderingSystem->HandleCommands();
			SetReadyToResume();
		}
		_synchronizeThreads.notify_one();
	}
}
