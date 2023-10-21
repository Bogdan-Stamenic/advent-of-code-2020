#include "../include/rules_parser.h"
#include <iostream>
#include <list>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

RulesParser::RulesParser(const std::vector<std::string>& input){
	parse_input_to_bag_graph(input);
};
void RulesParser::print_hashing_for_testing(){
	for (auto mod: m_possible_modifiers) {
		for (auto clr: m_possible_colors) {
			std::string str;
			str.append(mod.substr(0,2));
			unsigned int clr_idx = (clr.size() == 3) ? 0 : clr.size() - 4;
			str.append(clr.substr(clr_idx,3));
			std::cout << str << std::endl;
		}
	}
}
void RulesParser::print_child_to_parent_for_testing(){
	for (auto map: m_child_to_parent_graph) {
		std::cout <<  map.first << " in ";
		for (auto prt: map.second) {
			std::cout << prt.first << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
void RulesParser::print_parent_to_child_for_testing(){
	for (auto map: m_parent_to_child_graph) {
		std::cout <<  map.first << " contains ";
		for (auto prt: map.second) {
			std::cout << prt.first << ", ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
/* depth-first search from children to parents; solves day7 part 1 */
void RulesParser::dfs_child_to_parent_graph(const std::string& bag_type_for_root_node, bool recursive_dfs){
	std::unordered_set<std::string> has_been_explored;
	if (recursive_dfs) {
		depth_first_search_recursive(has_been_explored, bag_type_for_root_node);
	} else {
		depth_first_search_iterative(has_been_explored, bag_type_for_root_node);
	}
	std::cout << "Number of bags that contain at least one " << bag_type_for_root_node << " bag is " << (has_been_explored.size() - 1) << "." << std::endl;
}
void RulesParser::dfs_parent_to_child_graph(const std::string& bag_type_for_root_node, bool recursive_dfs){
	std::unordered_set<std::string> has_been_explored;
	if (recursive_dfs) {
		depth_first_search_recursive(has_been_explored, bag_type_for_root_node, true);
	} else {
		depth_first_search_iterative(has_been_explored, bag_type_for_root_node, true);
	}
	std::cout << bag_type_for_root_node << " bag contains " << (has_been_explored.size() - 1) << " other bag types." << std::endl;
}
void RulesParser::count_bags_contained_in(const std::string& bag_type_for_root_node){
	unsigned int num_bags = recursive_bag_count(bag_type_for_root_node, true);
	std::cout << bag_type_for_root_node << " bag contains a total of " << num_bags << " inside." << std::endl;
}

void RulesParser::parse_input_to_bag_graph(const std::vector<std::string>& input){
	std::vector<std::pair<std::string,std::string>> parents_and_children_from_input;
	/* Split parents and children from input and build graph; parent bags contain children bags */
	for (auto line: input) {
		std::string sep_phrase = " bags contain ";
		unsigned int idx = line.find(sep_phrase);
		if (idx == std::string::npos) {
			throw std::logic_error("couldn't match \" bags contain \" for parsing key. Re-check input file and parsing code's source file.");
		}
		unsigned int parent_start_idx = 0;
		unsigned int parent_length = idx;
		unsigned int children_start_idx = idx + sep_phrase.size();
		unsigned int children_length = line.size() - (sep_phrase.size() + idx);
		std::string parent_bag = line.substr(parent_start_idx, parent_length);
		std::string children_str = line.substr(children_start_idx, children_length);
		std::vector<std::pair<std::string,int>> children_bags = parse_contained_bags(children_str);
		parsed_bags_to_both_graphs(parent_bag,children_bags);
	}
	//std::cout << "parent -> child size : " << m_parent_to_child_graph.size() << std::endl;
	//std::cout << "child -> parent size : " << m_child_to_parent_graph.size() << std::endl;
	/* For perfect hash tables (and speed) use first 2 letters of key-string (first two letters of modifier) and last 3 letters of key-string (last three letters of color) */
}

std::vector<std::pair<std::string,int>> RulesParser::parse_contained_bags(const std::string& children_str) {
	/* Starts off like this:
	 * 5 faded blue bags, 6 dotted black bags.
	 * */
	std::string str = children_str;
	std::regex e("([0-9] [a-z]+ [a-z]+)", std::regex::egrep);
	std::smatch sm;
	std::vector<std::string> matches;
	while(std::regex_search(str,sm,e)){
		matches.push_back(sm.str());
		str = sm.suffix().str();
	}
	if ( (matches.empty() == true) && (children_str.find("no") == std::string::npos) ) {
		throw std::runtime_error("something went wrong while parsing.");
	} else if (children_str.find("no") == 0) {
		/* If children_str was "no other bags." */
		std::vector<std::pair<std::string,int>> v = {};
		return v;
	}
	/* Now like this:
	 * matches = {"5 faded blue", "6 dotted black"}
	 * */
	std::vector<std::pair<std::string,int>> v;
	for (auto m: matches) {
		int num = std::stoi(m.substr(0,1)); 
		std::string bag_type = m.substr(2, std::string::npos - 2);
		std::pair<std::string,int> contained_bags = {bag_type, num};
		v.push_back(contained_bags);
	}
	/* Finally this:
	 * v = { {"faded blue",2},{"dotted black",6} }
	 * */
	return v;
}

void RulesParser::parsed_bags_to_both_graphs(const std::string& parent_bag, const std::vector<std::pair<std::string,int>>& children_bags) {
	/* parent -> child */
	std::unordered_map<std::string,int> parent_contains_this_bag_x_times;
	for (auto contain_pair: children_bags) {
		parent_contains_this_bag_x_times.insert(contain_pair);
	}
	m_parent_to_child_graph.emplace(parent_bag,parent_contains_this_bag_x_times);
	/* child -> parent */
	for (auto contain_pair: children_bags) {
		std::pair<std::string,int> blah(parent_bag,contain_pair.second);
		m_child_to_parent_graph[contain_pair.first].insert(blah);
	}
}
void RulesParser::depth_first_search_iterative(std::unordered_set<std::string>& has_been_explored, const std::string& bag_type_for_root_node,
		bool parent_to_child){
	std::list<std::string> stack;
	stack.push_back(bag_type_for_root_node);
	while (stack.size() > 0) {
		std::string bag = stack.front();
		stack.pop_front();
		/* Continue if parents of bag haven't already been explored */
		if (has_been_explored.count(bag) == 0) {
			has_been_explored.emplace(bag);
			try {
				std::unordered_map<std::string,int>& next_node = (parent_to_child)
					? m_parent_to_child_graph.at(bag)
					: m_child_to_parent_graph.at(bag);
				for(auto it = next_node.begin(); it != next_node.end(); it++){
					/* If the next node's entries haven't been explored yet, add to stack */
					if (has_been_explored.count(it->first) == 0) {
						stack.push_back(it->first);
					}
				}
			} catch (const std::out_of_range& e) {
				/* Do nothing; bag is leaf on graph */
			}
		}
	}
}
void RulesParser::depth_first_search_recursive(std::unordered_set<std::string>& has_been_explored, const std::string& bag,
		bool parent_to_child){
	has_been_explored.emplace(bag);
	try {
		std::unordered_map<std::string,int>& next_node = (parent_to_child)
			? m_parent_to_child_graph.at(bag)
			: m_child_to_parent_graph.at(bag);
		for (auto it = next_node.begin(); it != next_node.end(); it++) {
			if (has_been_explored.count(it->first) == 0) {
				depth_first_search_recursive(has_been_explored, it->first, parent_to_child);
			}
		}
	} catch (const std::out_of_range& e) {
		/* Do nothing; bag is leaf on graph */
	}
}
/* Function for solving day7 part 2 */
unsigned int RulesParser::recursive_bag_count(const std::string& bag, bool parent_to_child){
	unsigned int bag_count = 0;
	std::unordered_map<std::string,int>& next_node_map = (parent_to_child)
		? m_parent_to_child_graph.at(bag)
		: m_child_to_parent_graph.at(bag);
	if (next_node_map.empty()) {
		return 0;
	} else {
#pragma omp parallel for
		for (auto it = next_node_map.begin(); it != next_node_map.end(); it++) {
			int inc = it->second * (1 + recursive_bag_count(it->first, parent_to_child));
			bag_count += inc;
		}
	}
	return bag_count;
}

