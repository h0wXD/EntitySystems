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


#ifndef GAME_INSTANCED_SPRITE
#define GAME_INSTANCED_SPRITE

#include <ES/disarray.h>
#include <Game/Vector2.h>
#include <algorithm>
#include <tuple>
#include <limits>

namespace game
{
	class InstancedSprite
	{
		friend class RenderingSystem;
		friend class RenderingLayer;
		es::disarray<Vector2f> _positionArray;
		es::disarray<float>	_depthArray;
		std::uint16_t _elementCount;

		void Sort()
		{
			std::uint16_t i = _elementCount;
			auto lowest = _positionArray.begin();
			while (i > 0)
			{
				--i;
				auto it = std::min_element(_depthArray.begin(), _depthArray.begin() + i);
				int distance = it - _depthArray.begin();
				std::iter_swap(lowest, _positionArray.begin() + distance);
				_depthArray[distance] = std::numeric_limits<float>::infinity();
			}
		}

		void Draw()
		{

		}

	public:
		InstancedSprite() { }
		~InstancedSprite() { }

	};
}

#endif
