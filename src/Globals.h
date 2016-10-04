#ifndef GLOBALS_H_
#define GLOBALS_H_

namespace Globals
{
	const unsigned int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 600;
	const float GROUND_OFFSET = 30;

	template<typename T1, typename T2>
	bool valueBetween(T1 val, T2 min, T2 max)
	{
		if (min > max)
		{
			T2 temp = min;
			min = max;
			max = temp;
		}
		return (val >= min && val <= max) ? true : false;
	}
}

#endif // GLOBALS_H_