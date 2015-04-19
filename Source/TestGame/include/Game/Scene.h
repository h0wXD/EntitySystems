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


#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include <Game/Timer.h>
#include <Game/RenderingSystem.h>
#include "InputSystem.h"

#include <thread>
#include <condition_variable>
#include <bitset>
#include <memory>

namespace game
{

	/*********************
	 * Scene declaration *
	 *******************************************************
	  Inline methods implemented at the bottom of this file 
	 *******************************************************/

	class Scene
	{
		enum : std::size_t
		{
			_SHOULD_STOP,
			_IS_STOPPED,
			_IS_READY_TO_SYNC,
			_IS_READY_TO_RESUME,
			_FLAG_COUNT
		};
		std::bitset<_FLAG_COUNT> _flags;

		std::condition_variable _synchronizeThreads;
		std::thread _logicThread;
		std::mutex _mutex;
		void _logicMethod();

		Timer _timer;

		inline bool IsStopped() const;
		inline bool ShouldStop() const;
		inline bool IsReadyToSync() const;
		inline bool IsReadyToResume() const;

		inline void SetStopped(bool v = true);
		inline void SetShouldStop(bool v = true);
		inline void SetReadyToSync(bool v = true);
		inline void SetReadyToResume(bool v = true);

		std::unique_ptr<RenderingSystem> _renderingSystem;
		std::unique_ptr<InputSystem> _inputSystem;

	public:
		Scene();
		~Scene();

		void StartLogicThread();
		void StopLogicThread();
		void LockAndSyncThreads();
		void NotifyThreads();

		void Render();

		inline RenderingSystem *GetRenderingSystem();
		inline InputSystem *GetInputSystem();
	};

	/*******************************
	 * Scene inline helper methods *
	 *******************************/

	/*
	 =Getters=
	*/
	bool Scene::IsStopped() const
	{
		return _flags.test(_IS_STOPPED);
	}

	bool Scene::ShouldStop() const
	{
		return _flags.test(_SHOULD_STOP);
	}

	bool Scene::IsReadyToSync() const
	{
		return _flags.test(_IS_READY_TO_SYNC);
	}

	bool Scene::IsReadyToResume() const
	{
		return _flags.test(_IS_READY_TO_RESUME);
	}

	RenderingSystem *Scene::GetRenderingSystem()
	{
		return _renderingSystem.get();
	}

	InputSystem *Scene::GetInputSystem()
	{
		return _inputSystem.get();
	}

	/*
	 =Setters=
	*/
	void Scene::SetReadyToResume(bool v)
	{
		_flags.set(_IS_READY_TO_RESUME, v);
	}

	void Scene::SetReadyToSync(bool v)
	{
		_flags.set(_IS_READY_TO_SYNC, v);
	}

	void Scene::SetShouldStop(bool v)
	{
		_flags.set(_SHOULD_STOP, v);
	}

	void Scene::SetStopped(bool v)
	{
		_flags.set(_IS_STOPPED, v);
	}

}

#endif
