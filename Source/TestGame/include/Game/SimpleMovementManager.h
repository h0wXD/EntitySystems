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


#ifndef GAME_SIMPLE_MOVEMENT_MANAGER_H
#define GAME_SIMPLE_MOVEMENT_MANAGER_H

#include <ES/disarray.h>
#include <Game/Vector2f.h>
#include <algorithm>
#include <iostream>
#include <ES/inplace_transform.h>

namespace game
{
	class SimpleMovementManager
	{
	public:
		static void Process(es::disarray<Vector2f> *position, es::disarray<Vector2f> *direction, std::int16_t count, float deltaTime)
		{
			es::inplace_transform_n(position->begin(), direction->begin(), count, 
				[deltaTime](Vector2f &pos, const Vector2f &dir)
				{
					pos.x += dir.x * deltaTime;
					pos.y += dir.y * deltaTime;
				});
		}
	};
}

#endif
