#pragma once

#include <vector>

extern int decodePNG(std::vector<unsigned char>& out_image_32bit,
			  unsigned long& image_width, unsigned long& image_height,
			  const unsigned char* in_png, unsigned long in_size);