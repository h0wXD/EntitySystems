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


#ifndef ES_SYSTEM_H
#define ES_SYSTEM_H

#include <ES/disarray.h>

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <type_traits>


namespace es
{
	/**
	 * @brief Abstract base class for systems.
	 *
	 * A system contains collections of components that define entities and their behaviors.
	 */
	class System
	{ 
	protected:
		std::uint16_t _elementCount;

		/*********************************************
		 * Helper template methods for child classes *
		 *********************************************/
		template <class T>
		static void Remove(std::uint16_t destination, std::uint16_t source, T &t)
		{
			t[destination] = t[source];
		}

		template <class T, class ...Y>
		static void Remove(std::uint16_t destination, std::uint16_t source, T &head, Y &...tail)
		{
			Remove(destination, source, head);
			Remove(destination, source, tail...);
		}

	public:

		/******************************
		 * Handle and reference class *
		 ******************************/

		/**
		 * @brief A temporary handle to an entity in the system
		 *
		 * A temporary handle to an entity in the system.
		 * Can become invalid upon removal of an entity or after processing the system.
		 */
		class Handle
		{
			friend class System;
			friend class Reference;
			std::uint16_t _id;
			Handle(std::uint16_t id) : _id(id) { }
		public:
			std::uint16_t GetId()
			{
				return _id;
			}

		};

		/**
		 * @brief A permanent handle to an entity in the system
		 *
		 * A permanent handle to an entity in the system.
		 * Will remain valid for as long as the entity that is referred to hasn't been removed.
		 */
		class Reference
		{
			friend class System;
			std::uint16_t _id;
		public:
			Reference(std::uint16_t id) : _id(id) { }
			Reference() : _id(UINT16_MAX) { }

			bool operator==(nullptr_t)
			{
				return _id == UINT16_MAX;
			}

			bool operator!=(nullptr_t)
			{
				return _id != UINT16_MAX;
			}

			Reference &operator=(nullptr_t)
			{
				_id = UINT16_MAX;
			}
		};
	
		System() : _elementCount(0) { }
		virtual ~System() = 0;

	protected:	
		
		/************************************
		 * Helper methods for child classes *
		 ************************************/
		inline void IncreaseElementCount()
		{
			++_elementCount;
		}

		static void SetHandle(Handle &h, std::uint16_t id)
		{
			h._id = id;
		}
		
		static Handle CreateHandle(std::uint16_t id)
		{
			return Handle(id);
		}

		Handle CreateHandle() const
		{
			return Handle(_elementCount);
		}

		Reference CreateReference(std::uint16_t id) const
		{
			return Reference(id);
		}

		static std::uint16_t GetReferenceId(const Reference &ref)
		{
			return ref._id;
		}

		static std::uint16_t GetHandleId(const Handle &handle)
		{
			return handle._id;
		}

	};
}

#endif
