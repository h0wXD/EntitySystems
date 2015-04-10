/********************************************************************************
 *                                                                              *
 *  ╔═════════════╗                                                             *
 *  ║EntitySystems║                                                             *
 *  ╚═════════════╝                                                             *
 *━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*
                                                                                
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

#ifndef ES_REFERRIBLE_SYSTEM_H
#define ES_REFERRIBLE_SYSTEM_H

#include <ES/System.h>

namespace es
{
	/**
	 * @brief Allows the usage of System::Reference to reference to an entity
	 *
	 * ReferribleSystems can expose their entities with references.
	 *
	 * This comes at the cost of extra overhead for inserting and removing data and
	 * requires more memory to store lookup tables for references and handles.
	 */
	class ReferribleSystem : protected System
	{
		disarray<std::uint16_t> _referenceArray; /** reference to handle lookup */
		disarray<std::uint16_t> _handleArray; /** handle to reference lookup */

		Reference Add(Handle handle)
		{
			auto ref = std::find_if(_referenceArray.begin(), _referenceArray.end(), [&](const std::uint16_t r)
			{
				return r == UINT16_MAX;
			});
			*ref = _elementCount;
			_handleArray[_elementCount] = ref - _referenceArray.begin();
			++_elementCount;
			return Reference(ref - _referenceArray.begin());
		}

	protected:
		/************************************
		 * Helper methods for child classes *
		 ************************************/
		void Remove(Reference ref)
		{
			--_elementCount;
			auto it = std::find(_referenceArray.begin(), _referenceArray.end(), _elementCount);
			_handleArray[*it] = _handleArray[_elementCount];
			*it = _referenceArray[System::GetReferenceId(ref)];
			_referenceArray[System::GetReferenceId(ref)] = UINT16_MAX;
		}
	public:
		ReferribleSystem(std::uint16_t size) : _referenceArray(size), _handleArray(size)
		{
			std::fill(_referenceArray.begin(), _referenceArray.end(), UINT16_MAX);
		}

		/**
		 * @brief Adds a new entity to the system and returns its Reference
		 */
		Reference Add()
		{
			Handle handle = CreateHandle(_elementCount);
			return Add(handle);
		}

		/**
		 * @brief Returns a handle for the entity being Referenced by Reference ref
		 */
		Handle GetHandle(Reference ref) const
		{
			return CreateHandle(_referenceArray[System::GetReferenceId(ref)]);
		}

		/**
		 * @brief Gets a Reference for the entity being referenced by Handle h
		 */
		Reference GetReference(Handle h) const
		{
			return CreateReference(_handleArray[System::GetHandleId(h)]);
		}
	};
}
#endif
