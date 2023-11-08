#include "../../include/day11.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#define MAX_SIMULATION_LOOPS 800 
#define DEBUG false

enum class Seat {Floor, Empty, Occupied};
typedef std::vector<std::vector<Seat>> FerrySeats;
typedef std::vector<std::vector<std::vector<std::pair<int,int>>>> FerrySeatsNeighbours;

class SeatSimulator {
	public:
		SeatSimulator(std::vector<std::string> input_line_by_line){
			init_ferry_seats(input_line_by_line);
		}
		~SeatSimulator() = default;
		void simulate_until_steady_state(bool fis_day11_part2=false) {
			m_fis_day11_part2 = fis_day11_part2;
			if (m_fis_day11_part2) {
				m_threshold_occupied_seats = 5;
			} else {
				m_threshold_occupied_seats = 4;
			}
			bool fsteady_state = false;
			m_ffirst_simulation_pass = true;
			m_ferry_seats = m_seats;
			m_last_ferry_seats = m_seats;
			for (int i = 0; i < MAX_SIMULATION_LOOPS; i++) {
				fsteady_state = simulation_step();
				if (fsteady_state) {
					return;
				}
			}
			throw std::runtime_error("simulation didn't terminate");
		}

		inline int count_all_occupied_seats() {
			auto it = vv_iterator<Seat>::begin(m_ferry_seats);
			auto it_end = vv_iterator<Seat>::end(m_ferry_seats);
			int count = 0;
			for (it; it!= it_end; it++) {
				if (*it == Seat::Occupied) {
					count += 1;
				}
			}
			return count;
		}
	private:
		FerrySeats m_seats{}; /* seat arangement from input */
		FerrySeats m_ferry_seats{};
		FerrySeats m_last_ferry_seats{};
		FerrySeatsNeighbours m_ferry_seats_neighbours{};
		int m_column_num;
		int m_row_num;
		bool m_ffirst_simulation_pass = true;
		bool m_fis_day11_part2 = false;
		int m_threshold_occupied_seats = 4;

		void init_ferry_seats(const std::vector<std::string> input) {
			m_column_num = input.front().size();
			m_row_num = input.size();
			m_seats = FerrySeats(
					m_row_num,std::vector<Seat>(m_column_num, Seat::Empty)
					);
			for (int i = 0; i < m_row_num; i++) {
				for (int j = 0; j < m_column_num; j++) {
					const char& space = input[i][j];
					switch (space) {
						case '.':
							m_seats[i][j] = Seat::Floor;
							break;
						case '#':
							m_seats[i][j] = Seat::Occupied;
							break;
						case 'L':
							/* Was initialized with Seat::Empty everywhere */
							break;
					};
				}
			}
			m_ferry_seats = m_seats;
			m_last_ferry_seats = m_seats;
			m_ferry_seats_neighbours = FerrySeatsNeighbours(
					m_row_num,std::vector<std::vector<std::pair<int,int>>>(
						m_column_num,std::vector<std::pair<int,int>>{})
					);
		}

		bool simulation_step() {
#if DEBUG
			std::cout << "m_ferry_seats" << "\n";
			print_m_ferry_seats();
//			std::cout << "m_last_ferry_seats" << "\n";
//			print_m_last_ferry_seats();
//			std::cout << "==================================================" << std::endl;
#endif
			m_last_ferry_seats = m_ferry_seats; //TODO: figure out why std::swap() causes problems
			update();
			bool is_steady_state = std::equal(
					vv_iterator<Seat>::begin(m_ferry_seats),
					vv_iterator<Seat>::end(m_ferry_seats),
					vv_iterator<Seat>::begin(m_last_ferry_seats)
					);
			if (m_ffirst_simulation_pass) {
				m_ffirst_simulation_pass = false;
			}
			return is_steady_state;
		}

		void update () {
#pragma omp parallel for
			{
				for (int i = 0; i < m_row_num; i++) {
					for (int j = 0; j < m_column_num; j++) {
						update_rule(i,j);
					}
				}
			}
		}

		void update_rule(int i, int j) {
			Seat state = m_last_ferry_seats[i][j];
			int num_occupied = 0;
			switch (state) {
				case Seat::Empty:
					num_occupied = count_occupied_adjacent_seats(i,j);
					if (num_occupied == 0) {
						m_ferry_seats[i][j] = Seat::Occupied;
					}
					return;
				case Seat::Occupied:
					num_occupied = count_occupied_adjacent_seats(i,j);
					/* Threshold is either 4 for p1 or 5 for p2 */
					if (num_occupied >= m_threshold_occupied_seats) {
						m_ferry_seats[i][j] = Seat::Empty;
					}
					return;
				case Seat::Floor:
					return;
			};
		}

		int count_occupied_adjacent_seats(int i, int j) {
			/* Memoize indices for faster indexing in subsequent run */
			if (m_ffirst_simulation_pass) {
				std::vector<std::pair<int,int>> adj_seats;
				if (m_fis_day11_part2) {
					adj_seats = adjacent_seat_indices_p2(i,j);
				} else {
					adj_seats = adjacent_seat_indices_p1(i,j);
				}
				m_ferry_seats_neighbours[i][j] = adj_seats;
			}
			int count = 0;
			for (const auto& [x, y]: m_ferry_seats_neighbours[i][j]) {
				if(m_last_ferry_seats[x][y] == Seat::Occupied) {
					count += 1;
				}
			}
		return count;
		}

		inline std::vector<std::pair<int,int>> adjacent_seat_indices_p1(int i, int j) {
			std::vector<std::pair<int,int>> adj_seats;
			/* Normal case */
			if (i > 0 && i < m_row_num - 1 && j > 0 && j < m_column_num - 1) {
				adj_seats = {
					{i-1,j-1}, {i-1,j}, {i-1,j+1},
					{i,j-1}, /*{i,j}*/  {i,j+1},
					{i+1,j-1}, {i+1,j}, {i+1,j+1}
				};
			}
			/* Edge cases (as in along the edge) */
			else if (i == 0  && j > 0 && j < m_column_num - 1) {
				adj_seats = {
					{i,j-1}, /*{i,j}*/  {i,j+1},
					{i+1,j-1}, {i+1,j}, {i+1,j+1}
				};
			} else if (i > 0 && i < m_row_num - 1  && j == 0) {
				adj_seats = {
					{i-1,j}, {i-1,j+1},
					/*{i,j}*/  {i,j+1},
					{i+1,j}, {i+1,j+1}
				};
			} else if (i > 0 && i < m_row_num - 1  && j == m_column_num - 1) {
				adj_seats = {
					{i-1,j-1}, {i-1,j},
					{i,j-1}, /*{i,j}*/ 
					{i+1,j-1}, {i+1,j},
				};
			} else if (i == m_row_num - 1 && j > 0 && j < m_column_num - 1) {
				adj_seats = {
					{i-1,j-1}, {i-1,j}, {i-1,j+1},
					{i,j-1}, /*{i,j}*/  {i,j+1},
				};
			}
			/* Corner cases */
			else if (i == 0  && j == 0) {
				adj_seats = {
					/*{i,j}*/  {i,j+1},
					{i+1,j}, {i+1,j+1}
				};
			} else if (i == m_row_num - 1 && j == 0) {
				adj_seats = {
					{i-1,j}, {i-1,j+1},
					/*{i,j}*/  {i,j+1},
				};
			} else if (i == 0 && j == m_column_num - 1) {
				adj_seats = {
					{i,j-1}, /*{i,j}*/ 
					{i+1,j-1}, {i+1,j},
				};
			} else if (i == m_row_num - 1 && j == m_column_num - 1) {
				adj_seats = {
					{i-1,j-1}, {i-1,j},
					{i,j-1}, /*{i,j}*/ 
				};
			} else {
				std::cout << "i = " << i << ", j = " << j << std::endl;
				throw std::logic_error("check occupied seat counting code");
			}
			return adj_seats;
		}

		inline std::vector<std::pair<int,int>> adjacent_seat_indices_p2(int i_in, int j_in) {
			std::vector<std::pair<int,int>> adj_seats;
			auto are_idxs_in_bounds = [this](int i,int j){
				return ((i >= 0) && (i <= m_row_num - 1) && (j >= 0) && (j <= m_column_num - 1));
			};
			std::vector<std::pair<int,int>> increment_pairs = {
				{-1,-1}, {-1,0}, {-1,1},
				{0,-1}, /*{0,0},*/ {0,1},
				{1,-1}, {1,0}, {1,1},
			};
			/* Search all 8 directions to find an adjacent seat */
			for (auto [i_inc,j_inc]: increment_pairs) {
				int i = i_in + i_inc;
				int j = j_in + j_inc;
				while (are_idxs_in_bounds(i,j)) {
					if(m_last_ferry_seats[i][j] != Seat::Floor) {
						adj_seats.push_back(std::make_pair(i,j));
						break;
					}
					i += i_inc;
					j += j_inc;
				}
			}
			return adj_seats;
		}

		void print_m_ferry_seats() const {
			for (auto& row: m_ferry_seats) {
				for (auto& seat: row) {
					switch (seat) {
						case Seat::Floor:
							std::cout << '.';
							break;
						case Seat::Empty:
							std::cout << 'L';
							break;
						case Seat::Occupied:
							std::cout << '#';
							break;
					}
				}
				std::cout << '\n';
			}
			std::cout << std::endl;
		}

		void print_m_last_ferry_seats() const {
			for (auto& row: m_last_ferry_seats) {
				for (auto& seat: row) {
					switch (seat) {
						case Seat::Floor:
							std::cout << '.';
							break;
						case Seat::Empty:
							std::cout << 'L';
							break;
						case Seat::Occupied:
							std::cout << '#';
							break;
						default:
							throw std::invalid_argument("didn't get Seat type");
					}
				}
				std::cout << '\n';
			}
			std::cout << std::endl;
		}

};

int main(int argc, char *argv[]) {
#ifdef GPROF /* Build for profiling */
	for (int i = 0; i < 1000; i++) {
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_input.txt");
	}
#else
	/* Start timer */
	std::chrono::high_resolution_clock::time_point t1 =
		std::chrono::high_resolution_clock::now();

#ifdef READ_AOC_INPUT_FROM_CMD 
	if (argc==2) {
		std::string filepath = std::string(argv[1]);
		std::vector<std::string> input_line_by_line = file_to_string_vec(filepath);
		SeatSimulator ferry(input_line_by_line);
		ferry.simulate_until_steady_state();
		int answer_p1 = ferry.count_all_occupied_seats();
		bool is_part2 = true;
		ferry.simulate_until_steady_state(is_part2);
		int answer_p2 = ferry.count_all_occupied_seats();
		std::cout << answer_p1 << std::endl;
		std::cout << answer_p2 << std::endl;
	} else {
		std::cout << "Usage:\n./day11 <input_file_path>" << std::endl;
	}
#else
	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day11 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_input.txt");
		SeatSimulator ferry(input_line_by_line);
		ferry.simulate_until_steady_state();
		int answer = ferry.count_all_occupied_seats();
		std::cout << "Occupied seats in steady state is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day11 - part 2 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_input.txt");
		SeatSimulator ferry(input_line_by_line);
		bool is_part2=true;
		ferry.simulate_until_steady_state(is_part2);
		int answer = ferry.count_all_occupied_seats();
		std::cout << "Occupied seats in steady state is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_dev.txt");
		SeatSimulator ferry(input_line_by_line);
		ferry.simulate_until_steady_state();
		int answer = ferry.count_all_occupied_seats();
		std::cout << "Occupied seats in steady state is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_dev.txt");
		SeatSimulator ferry(input_line_by_line);
		bool is_part2=true;
		ferry.simulate_until_steady_state(is_part2);
		int answer = ferry.count_all_occupied_seats();
		std::cout << "Occupied seats in steady state is : " << answer << std::endl;
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
