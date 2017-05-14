#ifndef HCODE
#define HCODE

#include "min_heap_node.h"

#include <string>
#include <vector>
#include <map>

std::vector<char> get_chars(const std::string& file_name);

std::vector< std::pair<char,unsigned long long> > get_freq(const std::vector<char>& char_vector);

min_heap_node* create_hcode(std::vector< std::pair<char,unsigned long long> > freq_vector);

void map_hcode(std::map<char,std::string> &hcode_table, min_heap_node* root, std::string str = std::string());

void print_hcode(min_heap_node* root, std::string str);

void compress(std::vector<char> char_vector, std::map<char, std::string> hcode_table);

#endif