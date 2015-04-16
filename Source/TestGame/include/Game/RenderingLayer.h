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


#ifndef GAME_RENDERING_LAYER_H
#define GAME_RENDERING_LAYER_H

#include <ES/disarray.h>
#include <Game/InstancedSprite.h>

namespace game
{
	
	class RenderingSystem;
	class RenderingLayer
	{
		friend class RenderingSystem;

		RenderingSystem *_system;
		std::uint16_t _opaqueSpriteCount;
		es::disarray<InstancedSprite> _opaqueSpriteArray;
		std::uint16_t _transparentSpriteCount;
		es::disarray<InstancedSprite> _transparentSpriteArray;

	public:
		RenderingLayer() :
			_opaqueSpriteCount(0),
			_opaqueSpriteArray(255),
			_transparentSpriteCount(0),
			_transparentSpriteArray(255) { }

	private:
		void Sort()
		{
			auto transparent = _transparentSpriteArray.data();
			auto count = _transparentSpriteCount;

			while (count > 0)
			{
				--count;
				transparent->Sort();
				++transparent;
			}
		}

		void Render()
		{
			auto opaqueCount = _opaqueSpriteCount;
			auto opaque = _opaqueSpriteArray.data();
			auto transparentCount = _transparentSpriteCount;
			auto transparent = _transparentSpriteArray.data();

			while (opaqueCount > 0)
			{
				--opaqueCount;
				opaque->Draw();
				++opaque;
			}

			while (transparentCount > 0)
			{
				--transparentCount;
				transparent->Draw();
				++transparent;
			}
		}
	public:
		~RenderingLayer() { }

	};
}


#endif
