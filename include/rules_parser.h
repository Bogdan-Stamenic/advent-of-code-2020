#ifndef RULES_PARSER_H
#define RULES_PARSER_H
#include <cstring>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct Gperf_Hash
{
  static constexpr inline unsigned int hash (const char *str, size_t len);
  auto operator()(const std::string &key) const -> unsigned int {
	  return hash(key.c_str(),key.length());
  }
};


/* Custom hash function to guarantee perfect hashing. */
struct MyHash {
	/* For perfect hash tables (and speed) use first 2 letters of key-string (first
	 * two letters of color modifier) and last 3 letters of key-string (last three
	 * letters of color). */
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
		std::unordered_map<std::string,std::unordered_map<std::string,int>,MyHash> m_parent_to_child_graph;
		/* Inverse of the above graph, i.e. 2 muted yellow bags can be contained in light red bags*/
		std::unordered_map<std::string,std::unordered_map<std::string,int>,MyHash> m_child_to_parent_graph;
		/* Possible modifiers and colors found using bash cmds on input */
		void parse_input_to_bag_graph(const std::vector<std::string>& input);
		std::vector<std::pair<std::string,int>> parse_contained_bags(const std::string& children_str);
		std::vector<std::pair<std::string,int>> no_regex_parse_contained_bags(const std::string& children_str);
		void parsed_bags_to_both_graphs(const std::string& parent_bag, const std::vector<std::pair<std::string,int>>& children_bags);
		void depth_first_search_iterative(std::unordered_set<std::string>& has_been_explored, const std::string& bag_type_for_root_node,
				bool parent_to_child=false);
		void depth_first_search_recursive(std::unordered_set<std::string>& has_been_explored, const std::string& bag,
				bool parent_to_child=false);
		/* Function for solving day7 part 2 */
		unsigned int recursive_bag_count(const std::string& bag, bool parent_to_child=false);
};

/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf --language=C++ -l day7_gperf_input.txt  */
/* Computed positions: -k'1,4-5,8-10,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif


#define TOTAL_KEYWORDS 594
#define MIN_WORD_LENGTH 7
#define MAX_WORD_LENGTH 19
#define MIN_HASH_VALUE 91
#define MAX_HASH_VALUE 6331
/* maximum key range = 6241, duplicates = 0 */

constexpr inline unsigned int
Gperf_Hash::hash (const char *str, size_t len)
{
  unsigned short asso_values[] =
    {
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332,  135, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332,   20,  565, 1734,
        50,    0, 1944,  365,  365,  180, 6332,  803,    0,   15,
         5,   10,  145,   55,   10,  430,   45, 1324,  620,  655,
      6332,  770,    0, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332, 6332,
      6332, 6332, 6332, 6332, 6332, 6332
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[static_cast<unsigned char>(str[9])];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[static_cast<unsigned char>(str[8])];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[static_cast<unsigned char>(str[7])];
      /*FALLTHROUGH*/
      case 7:
      case 6:
      case 5:
        hval += asso_values[static_cast<unsigned char>(str[4])];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[static_cast<unsigned char>(str[3])];
      /*FALLTHROUGH*/
      case 3:
      case 2:
      case 1:
        hval += asso_values[static_cast<unsigned char>(str[0])];
        break;
    }
  return hval + asso_values[static_cast<unsigned char>(str[len - 1])];
}
#endif
