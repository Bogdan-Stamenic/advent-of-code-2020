# Files with specific rules that don't conform to patterns in Makefile
# Binaries
day13_O3: day13_O3.o file_to_vec.o chinese_remainder_theorem_O3.o
	g++ -o day13_O3 file_to_vec.o chinese_remainder_theorem_O3.o day13_O3.o

day13_pg: day13_pg.o file_to_vec_pg.o chinese_remainder_theorem_pg.o
	g++ -pg -o day13_pg file_to_vec_pg.o chinese_remainder_theorem_pg.o day13_pg.o

day13: day13.o file_to_vec.o chinese_remainder_theorem.o
	g++ -o day13 file_to_vec.o chinese_remainder_theorem.o day13.o

day8_O3: day8_O3.o file_to_vec.o simulated_handheld_debugger_O3.o
	g++ -o day8_O3 file_to_vec.o simulated_handheld_debugger_O3.o day8_O3.o

day8_pg: day8_pg.o file_to_vec_pg.o simulated_handheld_debugger_pg.o
	g++ -pg -o day8_pg file_to_vec_pg.o simulated_handheld_debugger_pg.o day8_pg.o

day8: day8.o file_to_vec.o simulated_handheld_debugger.o
	g++ -o day8 file_to_vec.o simulated_handheld_debugger.o day8.o

day7_O3: day7_O3.o file_to_vec.o rules_parser_O3.o
	g++ -o day7_O3 file_to_vec.o rules_parser_O3.o day7_O3.o

day7_pg: day7_pg.o file_to_vec_pg.o rules_parser_pg.o
	g++ -pg -o day7_pg file_to_vec_pg.o rules_parser_pg.o day7_pg.o

day7: day7.o file_to_vec.o rules_parser.o
	g++ -o day7 file_to_vec.o rules_parser.o day7.o

day6_O3: day6_O3.o file_to_vec.o customs_declaration_O3.o
	g++ -o day6_O3 file_to_vec.o customs_declaration_O3.o day6_O3.o

day6_pg: day6_pg.o file_to_vec_pg.o customs_declaration_pg.o
	g++ -pg -o day6_pg file_to_vec_pg.o customs_declaration_pg.o day6_pg.o

day6: day6.o file_to_vec.o customs_declaration.o
	g++ -o day6 file_to_vec.o customs_declaration.o day6.o

day4_O3: day4_O3.o file_to_vec.o passport_processor_O3.o
	g++ -o day4_O3 file_to_vec.o passport_processor_O3.o day4_O3.o

day4_pg: day4_pg.o file_to_vec_pg.o passport_processor_pg.o
	g++ -pg -o day4_pg file_to_vec_pg.o passport_processor_pg.o day4_pg.o

day4: day4.o file_to_vec.o passport_processor.o
	g++ -o day4 file_to_vec.o passport_processor.o day4.o

