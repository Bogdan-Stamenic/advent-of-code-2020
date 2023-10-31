#include "../../include/day7.h"
#include <chrono>
#include <iostream>
#include <string>
#include <vector>


int main(int argc, char *argv[]) {
#ifdef GPROF /* Build for profiling */
	for (int i = 0; i < 1000; i++){
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_input.txt");
		RulesParser stickler(input_line_by_line);
		stickler.dfs_child_to_parent_graph("shiny gold");
		stickler.count_bags_contained_in("shiny gold");
	}
#else
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		RulesParser stickler(input_line_by_line);
		stickler.dfs_child_to_parent_graph("shiny gold");
		stickler.count_bags_contained_in("shiny gold");
	} else {
		std::cout << "Usage:\n./day7 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day7 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_input.txt");
		RulesParser stickler(input_line_by_line);
		stickler.dfs_child_to_parent_graph("shiny gold");
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day7 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_input.txt");
		RulesParser stickler(input_line_by_line);
		stickler.count_bags_contained_in("shiny gold");
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_dev_p1.txt");
		RulesParser stickler(input_line_by_line);
		/* Iterative DFS */
		stickler.dfs_child_to_parent_graph("shiny gold");
		stickler.print_child_to_parent_for_testing();
		stickler.print_parent_to_child_for_testing();
		/* Count contained bags */
		//stickler.count_bags_contained_in("shiny gold");
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day7_dev_p2.txt");
		RulesParser stickler(input_line_by_line);
		stickler.count_bags_contained_in("shiny gold");
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
#endif
}
