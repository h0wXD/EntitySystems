#ifndef ES_TRANSFORM_SELF_H
#define ES_TRANSFORM_SELF_H

#include <cstddef>
#include <algorithm>

namespace es
{
	template <class Target, class Input, class Operation>
	void transform_self(Target start, Target end, Input input, Operation operation)
	{
		while (start != end)
		{
			operation(*start, *input);
			++start;
			++input;
		}
	}

	template <class Target, class Input, class Operation>
	void transform_self(Target &target, Input &input, Operation operation)
	{
		transform_self(target.begin(), target.end(), input.begin(), operation);
	}

	template <class Target, class Input, class Operation>
	void transform_self_n(Target target, Input input, std::size_t n, Operation operation)
	{
		transform_self(target, target + n, input, operation);
	}
}
#endif
