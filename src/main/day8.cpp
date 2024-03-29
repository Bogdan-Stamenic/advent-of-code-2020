#include "../../include/day8.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_and_halt_on_infinite_loop();
		fixit.simulate_handheld_and_fix_infinite_loop();
	} else {
		std::cout << "Usage:\n./day8 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day8 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_input.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_and_halt_on_infinite_loop();
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day8 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_input.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_and_fix_infinite_loop();
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_dev.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_and_halt_on_infinite_loop();
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_dev.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_and_fix_infinite_loop();
	} else {
		std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" or \"4\" for developement." << std::endl;
		return 1;
	}
#endif
	/* Stop timer */
	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	return 0;
}
