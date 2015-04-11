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


#ifndef ES_FOR_EACH_WHERE_H
#define ES_FOR_EACH_WHERE_H

#include <cstddef>

namespace es
{
	template <class Iterator, class Predicate, class Operation>
	void for_each_where(Iterator begin, Iterator end, Predicate predicate, Operation operation)
	{
		while (begin != end)
		{
			if (predicate(*begin))
			{
				operation(*begin);
			}
			++begin;
		}
	}

	template <class Container, class Predicate, class Operation>
	void for_each_where(Container container, Predicate predicate, Operation operation)
	{
		for_each_where(container.begin(), container.end(), predicate, operation);
	}

	template <class Iterator, class Predicate, class Operation>
	void for_where(Iterator begin, Iterator end, Predicate predicate, Operation operation)
	{
		for (int i = 0; begin != end; ++i, ++begin)
		{
			if (predicate(*begin))
			{
				operation(i);
			}
		}
	};

	template <class Container, class Predicate, class Operation>
	void for_where(Container container, Predicate predicate, Operation operation)
	{
		for_where(container.begin(), container.end(), predicate, operation);
	}

	template <class Iterator, class Predicate, class Operation>
	void for_where_n(Iterator begin, std::size_t count, Predicate predicate, Operation operation)
	{
		for_where(begin, begin + count, predicate, operation);
	}

}

#endif
