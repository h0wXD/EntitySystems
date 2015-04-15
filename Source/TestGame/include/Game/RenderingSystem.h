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


#ifndef GAME_RENDERING_SYSTEM_H
#define GAME_RENDERING_SYSTEM_H

#include <Game/SpriteDrawCommand.h>
#include <Game/RenderingLayer.h>
#include <ES/System.h>

#include <array>
#include <string>

namespace game
{
	
	class RenderingSystem : es::System
	{
	public:
		enum
		{
			BACKGROUND,
			MIDDLE,
			FOREGROUND,
			LAYER_COUNT
		};
	private:
		std::array<RenderingLayer, LAYER_COUNT> _renderingLayers;
		es::disarray<SpriteDrawCommand> _commands;
		std::uint16_t _commandCount;

	public:
		RenderingSystem()
		{
			for (auto &layer : _renderingLayers)
			{
				layer._system = this;
			}
			_commandCount = 0;
			_commands.Allocate(255);
		}
		Handle LoadTexture(const std::string &path);

		void Render() 
		{
			for (auto &layer : _renderingLayers)
			{
				layer.Sort();
			}

			for (auto &layer : _renderingLayers)
			{
				layer.Render();
			}
		}
		void HandleCommands()
		{
			for (auto layer : _renderingLayers)
			{
				layer._opaqueSpriteCount = 0;
				layer._transparentSpriteCount = 0;
			}

			SpriteDrawCommand *command = nullptr;
			for (std::uint16_t i = 0; i < _commandCount; ++i, ++command)
			{
				
			}
		}

		~RenderingSystem() { }
	};
}

#endif
