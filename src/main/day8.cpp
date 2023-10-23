#include "../../include/day8.h"
#include "../../include/simulated_handheld_debugger.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char *argv[]) {
#ifdef GPROF /* Build for profiling */
	for (int i = 0; i < 1000; i++){
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_input.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_and_halt_on_infinite_loop();
	}
#else
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

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
		//std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_dev_p2.txt");
		std::cout << "Not implemented yet..." << std::endl;
	} else {
		std::cout << "Error: Invalid argument. Must be \"1\" or \"2\" for solver or \"3\" or \"4\" for developement." << std::endl;
		return 1;
	}

	/* Stop timer */
	std::chrono::high_resolution_clock::time_point t2 =
		std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span =
		std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "Duration: " << time_span.count() << "s" << std::endl;
	return 0;
#endif
}
