#include "csv-parser.hpp"

#include <string>

namespace CsvParser
{
void parse (std::string& input_line, std::vector<std::string>& parsed_fields)
{
	int field_start  = 0;
	int field_end    = 0;
	int field_length = 0;

	parsed_fields.clear();

	while (true) {
		field_end = input_line.find_first_of (",", field_start);

		if (field_end != std::string::npos) {
			field_length = field_end - field_start;
			parsed_fields.push_back (
			    input_line.substr (field_start, field_length));
			field_start = field_end + 1;
		} else {
			// There isn't another comma so we are on the last field
			// `substr` goes till end of string if not supplied with a length
			parsed_fields.push_back (input_line.substr (field_start));
			break;
		}
	}
}
} // namespace CsvParser