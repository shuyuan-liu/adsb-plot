#include "utils.hpp"

#include <cmath>
#include <iostream>
#include <png++/rgb_pixel.hpp>

namespace Utils
{
bool args_ok (int argc, char* argv[]) { return (argc == 2); }

void print_usage (const char* name)
{
	std::cerr << "Usage:" << std::endl;
	std::cerr << "\t" << name << " <input_file>" << std::endl;
}

const png::rgb_pixel alt_to_color (int altitude)
{
	if (altitude == 0) {
		return { 0, 0, 0 };
	}

	double norm_alt = std::min (1.0, altitude / 25000.0);

	unsigned char r = 255 * std::cos (M_PI_2 * norm_alt);
	unsigned char g = 255 * std::sin (M_PI * norm_alt);
	unsigned char b = 255 * std::cos (M_PI_2 * (1 - norm_alt));
	return png::rgb_pixel (r, g, b);
}
} // namespace Utils