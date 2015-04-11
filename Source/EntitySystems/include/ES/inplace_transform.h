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


#ifndef ES_TRANSFORM_SELF_H
#define ES_TRANSFORM_SELF_H

#include <cstddef>
#include <algorithm>

namespace es
{
	/**
	 * @brief Transforms Target with data from Input using a binary Operation
	 *
	 * Transforms Target in place.
	 * Input is used as the data to transform the Target with
	 * Operation is a binary operation (takes two paramaters of decltype(*Target), decltype(*Input))
	 * The Operation is expected to be of type void
	 * The output gets written to Target
	 *
	 * @tparam start     Start of the Target iterator
	 * @tparam end       End of the Target iterator
	 * @tparam input     Start of the Input iterator
	 * @tparam operation Operation to perform on *Target, *Input
	 */
	template <class Target, class Input, class Operation>
	void inplace_transform(Target start, Target end, Input input, Operation operation)
	{
		while (start != end)
		{
			operation(*start, *input);
			++start;
			++input;
		}
	}

	template <class Target, class Input, class Operation>
	void inplace_transform(Target &target, Input &input, Operation operation)
	{
		inplace_transform(target.begin(), target.end(), input.begin(), operation);
	}

	template <class Target, class Input, class Operation>
	void inplace_transform_n(Target target, Input input, std::size_t n, Operation operation)
	{
		inplace_transform(target, target + n, input, operation);
	}

}

#endif
