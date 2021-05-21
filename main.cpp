#include "csv-parser.hpp"
#include "sbs-fields.hpp"
#include "types.hpp"
#include "utils.hpp"

#include <algorithm>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>
#include <string>
#include <tuple>

using namespace std;
using namespace Utils;

double pixels_per_degree = 1000;

int main (int argc, char* argv[])
{
	if (!args_ok (argc, argv)) {
		print_usage (argv[0]);
		return 1;
	}

	filesystem::path input_path (argv[1]);
	ifstream         input_file (input_path);
	if (!input_file.good()) {
		cerr << "Couldn't open " << argv[1] << endl;
		return 2;
	}

	vector<Position> positions;
	Range<double>    lat_range, lon_range;
	while (input_file.good()) {
		static string line;
		getline (input_file, line);

		// Only process type 3 messages, which contains both position and
		// altitude data
		if (line[4] != '3') {
			continue;
		}

		static vector<string> fields;
		CsvParser::parse (line, fields);
		const string lat_str = fields[static_cast<int> (SbsFields::LATITUDE)];
		const string lon_str = fields[static_cast<int> (SbsFields::LONGITUDE)];
		const string alt_str = fields[static_cast<int> (SbsFields::ALTITUDE)];
		if (lat_str.empty() || lon_str.empty() || alt_str.empty()) {
			// Don't process this position if any of the coordinates is missing
			continue;
		}

		Position pos = { stod (lat_str), stod (lon_str), stoi (alt_str) };
		positions.push_back (pos);
		lat_range.update (pos.lat);
		lon_range.update (pos.lon);
	}

	const int image_width =
	    static_cast<int> (ceil (lon_range.range() * pixels_per_degree));
	const int image_height =
	    static_cast<int> (ceil (lat_range.range() * pixels_per_degree));
	png::image<png::rgb_pixel> image (image_width, image_height);

	for (const auto& [lat, lon, alt]: positions) {
		int y = (lat_range.max - lat) * pixels_per_degree;
		int x = (lon - lon_range.min) * pixels_per_degree;

		image[y][x] = alt_to_color (alt);
	}

	filesystem::path output_path =
	    input_path.parent_path().string() + "/adsb-plot.png";
	image.write (output_path);

	return 0;
}