#include "../../include/day8.h"
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct StackTraceEntry {
	unsigned int line_number;
	unsigned int cmd_name;
	unsigned int cmd_val;
	int acc_val;
	StackTraceEntry (unsigned int ln, unsigned int cn, unsigned int cv, int ac) {
		line_number = ln;
		cmd_name = cn;
		cmd_val = cv;
		acc_val = ac;
	}
};

struct StackTrace {
	std::vector<StackTraceEntry> the_stacktrace;
	StackTrace() {the_stacktrace = {};}
	void add_entry(unsigned int line_number, unsigned int cmd_name, unsigned int cmd_val, int acc_val) {
		StackTraceEntry new_entry(line_number,cmd_name,cmd_val,acc_val);
		the_stacktrace.push_back(new_entry);
	}
	void clear() {the_stacktrace.clear();}
	/* TODO : Implement [] or -> for entry access */
};

class SimulatedHandheld {
	public:
		SimulatedHandheld(const std::vector<std::string>& input_line_by_line){
			initialize(input_line_by_line);
		}
		SimulatedHandheld(){}
		void initialize(const std::vector<std::string>& input_line_by_line){
			input_to_handheld_boot_code(input_line_by_line);
			m_max_line_num = m_instructions.size();
			m_cmd_has_been_visited = std::vector<bool>(m_max_line_num,false);//range constructor
		}
		~SimulatedHandheld() = default;
		void print_m_instructions(){
			for (auto boot_cmd: m_instructions) {
				std::cout << boot_cmd.first << " " << boot_cmd.second << std::endl;
			}
		}
		void try_boot(bool verbose=false) {
			m_stacktrace.clear();
			boot_n_halt_w_stacktrace(verbose);
		}
		const StackTrace& get_stacktrace_ref(){return m_stacktrace;}
	private:
		std::vector<std::pair<unsigned int,int>> m_instructions;
		const std::unordered_map<std::string,unsigned int> m_assembly_to_uint = {{"acc",0},{"jmp",1},{"nop",2}};
		const std::unordered_map<unsigned int,std::string> m_uint_to_assembly = {{0,"acc"},{1,"jmp"},{2,"nop"}};
		unsigned int m_r_acc=0;
		unsigned int m_exec_line=0;
		unsigned int m_max_line_num=0;
		std::vector<bool> m_cmd_has_been_visited;//range constructor
		StackTrace m_stacktrace;
		void input_to_handheld_boot_code(const std::vector<std::string>& input){
			for (auto line: input) {
				unsigned int cmd_name = m_assembly_to_uint.at(line.substr(0,3));
				int cmd_val = stoi(line.substr(4));
				std::pair<unsigned int,int> boot_cmd(cmd_name,cmd_val);
				m_instructions.push_back(boot_cmd);
			}
		}
		void boot_n_halt_w_stacktrace(bool verbose=false) {
			while (m_cmd_has_been_visited[m_exec_line] != true) {
				m_cmd_has_been_visited[m_exec_line] = true;
				const std::pair<unsigned int, int>& boot_cmd = m_instructions[m_exec_line];
				m_stacktrace.add_entry(m_exec_line,boot_cmd.first,boot_cmd.second,m_r_acc);
				switch (boot_cmd.first) {
					case 0:
						m_r_acc += boot_cmd.second;
						m_exec_line += 1;
						break;
					case 1:
						m_exec_line += boot_cmd.second;
						break;
					default: /*noop*/
						m_exec_line += 1;
						break;
				}
				if (m_exec_line == m_max_line_num) {
#ifdef GPROF
#else
					if (verbose) std::cout << "Boot code terminated with no infinite loops." << std::endl;
#endif
					break;
				} else if ((m_exec_line < 0) || (m_exec_line > m_max_line_num)) {
					throw std::out_of_range("Uh-oh! m_exec_line went out of bounds.");
				}
			}
			const std::pair<unsigned int, int>& boot_cmd = m_instructions[m_exec_line];
			m_stacktrace.add_entry(m_exec_line,boot_cmd.first,boot_cmd.second,m_r_acc);
#ifdef GPROF
#else
			if (verbose) std::cout << "Handheld's accumulator on halt (m_exec_line = " << m_exec_line << ") during boot : " << m_r_acc << std::endl;
#endif
		}
};

class HandheldDebugger {
	public:
		HandheldDebugger(const std::vector<std::string>& input_line_by_line){
			m_gameboy.initialize(input_line_by_line);
		}
		~HandheldDebugger() = default;
		/* Solves day8 part 1 */
		void simulate_handheld_halt_on_infinite_loop(){
			m_gameboy.try_boot(true);
		}

	private:
		SimulatedHandheld m_gameboy;
		const std::unordered_map<std::string,unsigned int> m_assembly_to_uint = {{"acc",0},{"jmp",1},{"nop",2}};
		const std::unordered_map<unsigned int,std::string> m_uint_to_assembly = {{0,"acc"},{1,"jmp"},{2,"nop"}};
};

int main(int argc, char *argv[]) {
#ifdef GPROF /* Build for profiling */
	for (int i = 0; i < 1000; i++){
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_input.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_halt_on_infinite_loop();
	}
#else
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day8 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_input.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_halt_on_infinite_loop();
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day8 - part 2 */
		//std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_input.txt");
		std::cout << "Not implemented yet..." << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day8_dev.txt");
		HandheldDebugger fixit(input_line_by_line);
		fixit.simulate_handheld_halt_on_infinite_loop();
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
