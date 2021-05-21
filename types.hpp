#pragma once
#include <tuple>
#include <utility>
#include <vector>

struct Position {
	double lat, lon;
	int    alt;
};

typedef std::vector<Position> Track;

template<typename T> class Range
{
public:
	bool        initialized = false;
	T           min, max;
	constexpr T range() { return max - min; }

	void update_with (const T& value)
	{
		if (initialized) {
			if (value < min) {
				min = value;
			}
			if (value > max) {
				max = value;
			}
		} else {
			min = max   = value;
			initialized = true;
		}
	}
};