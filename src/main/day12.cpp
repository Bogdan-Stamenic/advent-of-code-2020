#include "../../include/day12.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum class ShipInstruction {North,South,East,West,Left,Right,Forward};

inline constexpr int my_sin(int angle_degrees) {
	switch (angle_degrees) {
		case 0:
			return 0;
		case 90:
			return 1;
		case 180:
			return 0;
		case 270:
			return -1;
		case -90:
			return -1;
		case -180:
			return 0;
		case -270:
			return 1;
		default:
			throw std::invalid_argument("my_sin() expected {-270,-180,-90,0,90,180,270}");
	};
}

inline constexpr int my_cos(int angle_degrees) {
	/* cos() is even function */
	switch (angle_degrees) {
		case 0:
			return 1;
		case 90:
			return 0;
		case 180:
			return -1;
		case 270:
			return 0;
		case -90:
			return 0;
		case -180:
			return -1;
		case -270:
			return 0;
		default:
			throw std::invalid_argument("my_cos() expected {-270,-180,-90,0,90,180,270}");
	};
}

class ShipNavigation {
	public:
		ShipNavigation(std::vector<std::string> input) {
			init_instrucions(input);
		}
		void run_emergency_navigation() {
			for (const auto& [instruct,value]: m_instructions) {
				switch (instruct) {
					case ShipInstruction::North:
						m_ship_y_coord += value;
						break;
					case ShipInstruction::South:
						m_ship_y_coord -= value;
						break;
					case ShipInstruction::East:
						m_ship_x_coord += value;
						break;
					case ShipInstruction::West:
						m_ship_x_coord -= value;
						break;
					case ShipInstruction::Left:
						m_ship_orientation_degrees =
							(m_ship_orientation_degrees + value) % 360;
						break;
					case ShipInstruction::Right:
						m_ship_orientation_degrees = (m_ship_orientation_degrees - value >= 0)
							? m_ship_orientation_degrees - value
							: m_ship_orientation_degrees + 360 - value;
						break;
					case ShipInstruction::Forward:
						switch (m_ship_orientation_degrees / 90) {
							case 0:
								m_ship_x_coord += value;
								break;
							case 1:
								m_ship_y_coord += value;
								break;
							case 2:
								m_ship_x_coord -= value;
								break;
							case 3:
								m_ship_y_coord -= value;
								break;
							default:
								throw std::runtime_error("unexpected ship direction " + std::to_string(m_ship_orientation_degrees));
						};
				};
			}
		}
		void run_emergency_navigation_with_waypoint() {
			for (const auto& [instruct,value]: m_instructions) {
				switch (instruct) {
					case ShipInstruction::North:
						m_waypoint_y_coord += value;
						break;
					case ShipInstruction::South:
						m_waypoint_y_coord -= value;
						break;
					case ShipInstruction::East:
						m_waypoint_x_coord += value;
						break;
					case ShipInstruction::West:
						m_waypoint_x_coord -= value;
						break;
					case ShipInstruction::Left:
						rotate_waypoint_around_ship(value);
						break;
					case ShipInstruction::Right:
						rotate_waypoint_around_ship(-1*value);
						break;
					case ShipInstruction::Forward:
						m_ship_x_coord += value * m_waypoint_x_coord;
						m_ship_y_coord += value * m_waypoint_y_coord;
				};
			}
		}
		void print_manhattan_distance() const {
			std::cout << "x : " << m_ship_x_coord
				<< ", y : " << m_ship_y_coord
				<< " => "
				<< sgn(m_ship_x_coord)*m_ship_x_coord + sgn(m_ship_y_coord)*m_ship_y_coord
				<< std::endl;
		}
	private:
		std::vector<std::pair<ShipInstruction,int>> m_instructions;
		const std::unordered_map<std::string,ShipInstruction> m_string_to_shipinstruction = {
			{"N",ShipInstruction::North}, {"S",ShipInstruction::South}, {"E",ShipInstruction::East},
			{"W",ShipInstruction::West}, {"L",ShipInstruction::Left}, {"R",ShipInstruction::Right},
			{"F",ShipInstruction::Forward}, 
		};
		int m_ship_orientation_degrees = 0;
		int m_ship_x_coord = 0; /* + is east, - is west */
		int m_ship_y_coord = 0; /* + is north, - is south*/
		int m_waypoint_x_coord = 10;
		int m_waypoint_y_coord = 1;
		void init_instrucions(std::vector<std::string> input) {
			for(auto line: input) {
				std::pair<ShipInstruction,int> inst(
						m_string_to_shipinstruction.at(line.substr(0, 1)),
						std::stoi(line.substr(1, line.size() - 1))
						);
				m_instructions.push_back(inst);
			}
		}
		void rotate_waypoint_around_ship(int ang_deg) {
			/* Rotation matrix math -> noobs can look it up on Wikipedia */
			int new_waypoint_x = my_cos(ang_deg)*m_waypoint_x_coord - my_sin(ang_deg)*m_waypoint_y_coord;
			int new_waypoint_y = my_sin(ang_deg)*m_waypoint_x_coord + my_cos(ang_deg)*m_waypoint_y_coord;
			m_waypoint_x_coord = new_waypoint_x; 
			m_waypoint_y_coord = new_waypoint_y;
		}
};

int main(int argc, char *argv[]) {
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		ShipNavigation yarr(input_line_by_line);
		yarr.run_emergency_navigation();
		yarr.print_manhattan_distance();
		yarr.run_emergency_navigation_with_waypoint();
		yarr.print_manhattan_distance();
	} else {
		std::cout << "Usage:\n./day12 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day12 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day12_input.txt");
		ShipNavigation yarr(input_line_by_line);
		yarr.run_emergency_navigation();
		yarr.print_manhattan_distance();
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day12 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day12_input.txt");
		ShipNavigation yarr(input_line_by_line);
		yarr.run_emergency_navigation_with_waypoint();
		yarr.print_manhattan_distance();
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day12_dev.txt");
		ShipNavigation yarr(input_line_by_line);
		yarr.run_emergency_navigation();
		yarr.print_manhattan_distance();
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day12_dev.txt");
		ShipNavigation yarr(input_line_by_line);
		yarr.run_emergency_navigation_with_waypoint();
		yarr.print_manhattan_distance();
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
