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

#ifndef GAME_SIMPLE_BULLET_SYSTEM_H
#define GAME_SIMPLE_BULLET_SYSTEM_H

#include <ES/System.h>
#include <ES/disarray.h>

#include <Game/ILogic.h>
#include <Game/Vector2.h>

namespace game
{

	class SimpleBulletSystem;

	/**************************************
	 * Simple Bullet instance declaration *
	 **************************************/
	class SimpleBulletInstance
	{
		friend class SimpleBulletSystem;
		es::System::Handle _handle;
		SimpleBulletSystem *_system;

		SimpleBulletInstance(SimpleBulletSystem *system, es::System::Handle handle) : 
			_system(system), _handle(handle) { }
	public:
		inline Vector2f &Position();
		inline Vector2f &Direction();
	};

	/************************
	 * Simple Bullet system *
	 ************************/
	class SimpleBulletSystem : public es::System
	{
		friend class SimpleBulletInstance;
		es::disarray<Vector2f> _positionArray;
		es::disarray<Vector2f> _directionArray;

	public:
		es::System::Handle Add()
		{
			Handle handle = CreateHandle();
			IncreaseElementCount();
			return handle;
		}

		SimpleBulletInstance GetInstance(Handle handle)
		{
			return SimpleBulletInstance(this, handle);
		}
	};

	/*************************************
	 * Simple Bullet instance definition *
	 *************************************/
	Vector2f &SimpleBulletInstance::Position()
	{
		return _system->_positionArray[_handle.GetId()];
	}

	Vector2f &SimpleBulletInstance::Direction()
	{
		return _system->_directionArray[_handle.GetId()];
	}
}

#endif
