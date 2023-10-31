#include "../../include/day11.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#define MAX_SIMULATION_LOOPS 800 
#define DEBUG false

enum Seat {Floor, Empty, Occupied};
typedef std::vector<std::vector<Seat>> FerrySeats;

class SeatSimulator {
	public:
		SeatSimulator(std::vector<std::string> input_line_by_line){
			init_ferry_seats(input_line_by_line);
		}
		~SeatSimulator() = default;
		void simulate_until_steady_state() {
			bool fsteady_state = false;
			for (int i = 0; i < MAX_SIMULATION_LOOPS; i++) {
				fsteady_state = simulation_step();
				if (fsteady_state) return;
			}
			throw std::runtime_error("simulation didn't terminate");
		}

		inline int count_all_occupied_seats(){
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
		FerrySeats m_ferry_seats{};
		FerrySeats m_last_ferry_seats_state{};
		int m_column_num;
		int m_row_num;

		void init_ferry_seats(const std::vector<std::string> input) {
			m_column_num = input.front().size();
			m_row_num = input.size();
			std::vector<Seat> vec = std::vector<Seat>(m_column_num, Seat::Empty);
			m_ferry_seats = FerrySeats(m_row_num,vec);
			for (int i = 0; i < m_row_num; i++) {
				for (int j = 0; j < m_column_num; j++) {
					const char& space = input[i][j];
					switch (space) {
						case '.':
							m_ferry_seats[i][j] = Seat::Floor;
							break;
						case '#':
							m_ferry_seats[i][j] = Seat::Occupied;
							break;
						default: break;
					};
				}
			}
			m_last_ferry_seats_state = m_ferry_seats;
		}

		bool simulation_step() {
#if DEBUG
			print_m_ferry_seats();
#endif
			//m_last_ferry_seats_state.swap(m_ferry_seats);
			//m_ferry_seats.swap(m_last_ferry_seats_state);
			m_last_ferry_seats_state = m_ferry_seats; //TODO: figure out why std::swap() causes problems
			update();
			bool is_steady_state = std::equal(
					vv_iterator<Seat>::begin(m_ferry_seats),
					vv_iterator<Seat>::end(m_ferry_seats),
					vv_iterator<Seat>::begin(m_last_ferry_seats_state)
					);
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

		inline void update_rule(int i, int j) {
			const Seat& state = m_last_ferry_seats_state[i][j];
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
					if (num_occupied >= 4) {
						m_ferry_seats[i][j] = Seat::Empty;
					}
					return;
				case Seat::Floor:
					return;
			};
			throw std::runtime_error("something unexpected happened");
		}

		inline int count_occupied_adjacent_seats(int i, int j) {
			std::vector<std::pair<int,int>> adj_seats;
			/* I keep getting segfaults, soooooo lots of if-statements to stop it */
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
			int count = 0;
			for (auto [x, y]: adj_seats) {
				if(m_last_ferry_seats_state[x][y] == Seat::Occupied) {
					count += 1;
				}
			}
			//std::cout << count << std::endl;
			return count;
		}
		
		void print_m_ferry_seats() {
			for (auto row: m_ferry_seats) {
				for (auto seat: row) {
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

	if (((argc == 2) && (*argv[1] == '1')) || (argc == 1)) {
		/* day11 - part 1 */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_input.txt");
		SeatSimulator ferry(input_line_by_line);
		ferry.simulate_until_steady_state();
		int answer = ferry.count_all_occupied_seats();
		std::cout << "Occupied seats in steady state is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '2')) {
		/* day11 - part 2 */
		//std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_input.txt");
		std::cout << "Not yet implemented..." << std::endl;
	} else if ((argc == 2) && (*argv[1] == '3')) {
		/* developement */
		std::vector<std::string> input_line_by_line = file_to_string_vec("input/day11_dev.txt");
		SeatSimulator ferry(input_line_by_line);
		ferry.simulate_until_steady_state();
		int answer = ferry.count_all_occupied_seats();
		std::cout << "Occupied seats in steady state is : " << answer << std::endl;
	} else if ((argc == 2) && (*argv[1] == '4')) {
		/* developement */
		//std::vector<std::string> input_dev1 = file_to_string_vec("input/day11_dev.txt");
		std::cout << "Not yet implemented..." << std::endl;
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
