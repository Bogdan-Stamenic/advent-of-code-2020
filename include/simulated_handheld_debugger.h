#include <string>
#include <unordered_map>
#include <vector>

#define ACC 0
#define JMP 1
#define NOP 2

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
	std::vector<StackTraceEntry> the_stacktrace;//TODO: try adding {}
	StackTrace();
	void add_entry(unsigned int line_number, unsigned int cmd_name, unsigned int cmd_val, int acc_val);
	void clear();
	const StackTraceEntry& back();
	StackTraceEntry pop();
	/* Iterator stuff */
	auto crbegin() {return the_stacktrace.crbegin();};
	auto crend() {return the_stacktrace.crend();};
	auto cbegin() {return the_stacktrace.cbegin();};
	auto cend() {return the_stacktrace.cend();};
};

class SimulatedHandheld {
	public:
		SimulatedHandheld(const std::vector<std::string>& input_line_by_line);
		SimulatedHandheld();
		~SimulatedHandheld() = default;
		StackTrace get_m_stacktrace();
		std::vector<bool> get_m_cmd_has_been_visited ();
		unsigned int get_m_acc ();
		void set_m_cmd_has_been_visited (const std::vector<bool>& cmd_has_been_visited);

		void insert_instructions_and_initialize_handheld(const std::vector<std::string>& input_line_by_line);
		void reset_handheld_state();
		void print_m_instructions();
		int try_boot(bool verbose=false);
		void flip_instruction_for_debugging(int instruction_to_flip_for_debugging);
	private:
		std::vector<std::pair<unsigned int,int>> m_instructions;
		const std::unordered_map<std::string,unsigned int> m_assembly_to_uint = {{"acc",ACC},{"jmp",JMP},{"nop",NOP}};
		const std::unordered_map<unsigned int,std::string> m_uint_to_assembly = {{ACC,"acc"},{JMP,"jmp"},{NOP,"nop"}};
		unsigned int m_r_acc=0;
		unsigned int m_exec_line=0;
		unsigned int m_max_line_num=0;
		int m_last_instruction_flipped_for_debugging=-1;
		std::vector<bool> m_cmd_has_been_visited;//range constructor
		StackTrace m_stacktrace;
		void input_to_handheld_boot_code(const std::vector<std::string>& input);
		int boot_n_halt_w_stacktrace(bool verbose=false);
};

class HandheldDebugger {
	public:
		HandheldDebugger(const std::vector<std::string>& input_line_by_line);
		~HandheldDebugger() = default;
		/* Solves day8 part 1 */
		void simulate_handheld_and_halt_on_infinite_loop();
		/* Solves day8 part 2 */
		void simulate_handheld_and_fix_infinite_loop();
	private:
		SimulatedHandheld m_gameboy;
		const std::unordered_map<std::string,unsigned int> m_assembly_to_uint = {{"acc",0},{"jmp",1},{"nop",2}};
		const std::unordered_map<unsigned int,std::string> m_uint_to_assembly = {{0,"acc"},{1,"jmp"},{2,"nop"}};
};
