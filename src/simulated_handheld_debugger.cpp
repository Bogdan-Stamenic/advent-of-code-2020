#include "../include/simulated_handheld_debugger.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <vector>

StackTrace::StackTrace() {the_stacktrace = {};}
void StackTrace::add_entry(unsigned int line_number, unsigned int cmd_name, unsigned int cmd_val, int acc_val) {
	StackTraceEntry new_entry(line_number,cmd_name,cmd_val,acc_val);
	the_stacktrace.push_back(new_entry);
}
void StackTrace::clear() {the_stacktrace.clear();}
const StackTraceEntry& StackTrace::back() {return the_stacktrace.back();}
StackTraceEntry StackTrace::pop() {
	StackTraceEntry blah = the_stacktrace.back();
	the_stacktrace.pop_back();
	return blah;
}

/****************************************************/
SimulatedHandheld::SimulatedHandheld(const std::vector<std::string>& input_line_by_line){
	insert_instructions_and_initialize_handheld(input_line_by_line);
}

SimulatedHandheld::SimulatedHandheld(){}

StackTrace SimulatedHandheld::get_m_stacktrace() {return m_stacktrace;}
std::vector<bool> SimulatedHandheld::get_m_cmd_has_been_visited () {return m_cmd_has_been_visited;}
void SimulatedHandheld::set_m_cmd_has_been_visited (const std::vector<bool>& cmd_has_been_visited) {
	if (cmd_has_been_visited.size() != m_max_line_num) {
		throw std::invalid_argument("Bool vector must have exactly m_max_line_num entries.");
	}
	m_cmd_has_been_visited = cmd_has_been_visited;
}

unsigned int SimulatedHandheld::get_m_acc () {
	return m_r_acc;
};

void SimulatedHandheld::insert_instructions_and_initialize_handheld(const std::vector<std::string>& input_line_by_line){
	input_to_handheld_boot_code(input_line_by_line);
	m_max_line_num = m_instructions.size();
	m_cmd_has_been_visited = std::vector<bool>(m_max_line_num,false);//range constructor
}

void SimulatedHandheld::reset_handheld_state() {
	m_exec_line = 0;
	m_r_acc = 0;
	m_stacktrace = StackTrace();
	m_cmd_has_been_visited = std::vector<bool>(m_max_line_num,false);
}

void SimulatedHandheld::print_m_instructions(){
	for (auto boot_cmd: m_instructions) {
		std::cout << boot_cmd.first << " " << boot_cmd.second << std::endl;
	}
}

int SimulatedHandheld::try_boot(bool verbose) {
	m_stacktrace.clear();
	int boot_cmd_status = boot_n_halt_w_stacktrace(verbose);
	return boot_cmd_status;
}

void SimulatedHandheld::input_to_handheld_boot_code(const std::vector<std::string>& input){
	for (auto line: input) {
		unsigned int cmd_name = m_assembly_to_uint.at(line.substr(0,3));
		int cmd_val = stoi(line.substr(4));
		std::pair<unsigned int,int> boot_cmd(cmd_name,cmd_val);
		m_instructions.push_back(boot_cmd);
	}
}

int SimulatedHandheld::boot_n_halt_w_stacktrace(bool verbose) {
	while (m_cmd_has_been_visited[m_exec_line] != true) {
		m_cmd_has_been_visited[m_exec_line] = true;
		const std::pair<unsigned int, int>& boot_cmd = m_instructions[m_exec_line];
		m_stacktrace.add_entry(m_exec_line,boot_cmd.first,boot_cmd.second,m_r_acc);
		switch (boot_cmd.first) {
			case ACC:
				m_r_acc += boot_cmd.second;
				m_exec_line += 1;
				break;
			case JMP:
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
			return 0;
		} else if ((m_exec_line < 0) || (m_exec_line > m_max_line_num)) {
			throw std::out_of_range("Uh-oh! m_exec_line went out of bounds.");
			return 2;
		}
	}
	const std::pair<unsigned int, int>& boot_cmd = m_instructions[m_exec_line];
	m_stacktrace.add_entry(m_exec_line,boot_cmd.first,boot_cmd.second,m_r_acc);
#ifdef GPROF
#else
	if (verbose) std::cout << "Handheld's accumulator on halt (m_exec_line = " << m_exec_line << ") during boot : " << m_r_acc << std::endl;
#endif
	return 1;
}

void SimulatedHandheld::flip_instruction_for_debugging(int instruction_to_flip_for_debugging) {
	auto flip_instr = [](unsigned int x){
		if (x == JMP) {return NOP;}
		else if (x == NOP) {return JMP;}
		else if (x == ACC) {throw std::out_of_range("Can't flip ACC");}
		else {throw std::out_of_range("Uh-oh");}
	};
	std::pair<unsigned int,int>& instruction = m_instructions[instruction_to_flip_for_debugging];
	instruction.first = flip_instr(instruction.first);
	if (m_last_instruction_flipped_for_debugging != -1) {
		/* Re-flip instruction from previous call */
		std::pair<unsigned int,int> last_instruction = m_instructions[m_last_instruction_flipped_for_debugging];
		last_instruction.first = flip_instr(last_instruction.first);
	}
	m_last_instruction_flipped_for_debugging = instruction_to_flip_for_debugging;
}

/****************************************************/
HandheldDebugger::HandheldDebugger(const std::vector<std::string>& input_line_by_line){
	m_gameboy.insert_instructions_and_initialize_handheld(input_line_by_line);
}

/* Solves day8 part 1 */
void HandheldDebugger::simulate_handheld_and_halt_on_infinite_loop(){
	m_gameboy.reset_handheld_state();
	bool VERBOSE = true;
	int boot_status = m_gameboy.try_boot(VERBOSE);
}

/* Solves day8 part 2 */
void HandheldDebugger::simulate_handheld_and_fix_infinite_loop(){
	m_gameboy.reset_handheld_state();
	int boot_status = m_gameboy.try_boot();
	StackTrace stacktrace = m_gameboy.get_m_stacktrace();
	std::vector<bool> cmd_has_been_visited = m_gameboy.get_m_cmd_has_been_visited();
	auto it_stacktrace = stacktrace.crbegin();
	/* 1) Work backwards through stacktrace
	 * 2) Flip exactly one noop or jmp
	 * 3) Reinitialize handheld at state with flipped command
	 * */
	while(boot_status == 1){
		while (it_stacktrace->cmd_name == ACC) {
			it_stacktrace++;
		}
		/* jmp 0 and nop 0 both do nothing -> continue */
		if (it_stacktrace->cmd_val == 0) continue;
		m_gameboy.flip_instruction_for_debugging(it_stacktrace->line_number);
		m_gameboy.reset_handheld_state();
		boot_status = m_gameboy.try_boot();
		if (boot_status != 0) {
			it_stacktrace++;
		}
	}
	if(boot_status == 2) {
		throw std::runtime_error("Something went very wrong! Handheld boot failed with unexpected behaviour.");
	}
#ifdef GPROF
#else
	std::cout << "Boot code error was on line " << it_stacktrace->line_number << ".\n"
		<< "Accumulator value on termination (solution to part 2) is : " << m_gameboy.get_m_acc() << "." << std::endl;
#endif
}
