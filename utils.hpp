#pragma once
#include "types.hpp"

#include <png++/rgb_pixel.hpp>
#include <utility>

namespace Utils
{
bool                 args_ok (int argc, char* argv[]);
void                 print_usage (const char* name);
const png::rgb_pixel alt_to_color (int altitude);
} // namespace Utils