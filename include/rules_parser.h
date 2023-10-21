#ifndef RULES_PARSER_H
#define RULES_PARSER_H
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

/* Custom hash function to guarantee perfect hashing */
struct MyHash {
  auto operator()(const std::string &key) const -> size_t {
	auto hash1 = std::hash<std::string>{}(key.substr(0,2));
	unsigned int clr_idx = (key.size() == 3) ? 0 : key.size() - 4;
	auto hash2 = std::hash<std::string>{}(key.substr(clr_idx,3));
    return (hash1 ^ hash2);
  }
};

class RulesParser {
    public:
        RulesParser(const std::vector<std::string>& input);
        ~RulesParser() = default;
        void print_hashing_for_testing();
		void print_child_to_parent_for_testing();
		void print_parent_to_child_for_testing();
		/* depth-first search from children to parents; solves day7 part 1 */
		void dfs_child_to_parent_graph(const std::string& bag_type_for_root_node, bool recursive_dfs=false);
		void dfs_parent_to_child_graph(const std::string& bag_type_for_root_node, bool recursive_dfs=false);
		void count_bags_contained_in(const std::string& bag_type_for_root_node);

	protected:
		const std::vector<std::string> m_possible_modifiers{"bright","clear","dark","dim","dotted","drab",
			"dull","faded","light","mirrored","muted","pale","plaid","posh","shiny","striped",
			"vibrant","wavy"};
		const std::vector<std::string> m_possible_colors{"aqua","beige","black","blue","bronze","brown",
			"chartreuse","coral","crimson","cyan","fuchsia","gold","gray","green","indigo","lavender",
			"lime","magenta","maroon","olive","orange","plum","purple","red","salmon","silver","tan",
			"teal","tomato","turquoise","violet","white","yellow"};

    private:
		/* Graph representing input, e.g. light red bags contain 1 bright white bag, 2 muted yellow bags. */
		std::unordered_map<std::string,std::unordered_map<std::string, int>,MyHash> m_parent_to_child_graph;
		/* Inverse of the above graph, i.e. 2 muted yellow bags can be contained in light red bags*/
		std::unordered_map<std::string,std::unordered_map<std::string, int>,MyHash> m_child_to_parent_graph;
		/* Possible modifiers and colors found using bash cmds on input */
		void parse_input_to_bag_graph(const std::vector<std::string>& input);
		std::vector<std::pair<std::string,int>> parse_contained_bags(const std::string& children_str);
		void parsed_bags_to_both_graphs(const std::string& parent_bag, const std::vector<std::pair<std::string,int>>& children_bags);
		void depth_first_search_iterative(std::unordered_set<std::string>& has_been_explored, const std::string& bag_type_for_root_node,
				bool parent_to_child=false);
		void depth_first_search_recursive(std::unordered_set<std::string>& has_been_explored, const std::string& bag,
				bool parent_to_child=false);
		/* Function for solving day7 part 2 */
		unsigned int recursive_bag_count(const std::string& bag, bool parent_to_child=false);
};
#endif
