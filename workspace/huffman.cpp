#include "Huffman.h"
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

/* Helper functions */
bool sort_frequency(const pair<char, unsigned long long>& p1, const pair<char, unsigned long long>& p2) {
  return (p1.second < p2.second);
}

/* Huffman member functions */
Huffman::Huffman(const string& file_name) {
  ifstream file;
  file.open(file_name.c_str(), ios::in);

  if (file.fail()) {
    cerr << "Error opening " << file_name << ": " << strerror(errno) << endl;
    exit(EXIT_FAILURE);
  }
  else {
    char current_char;

    while (!file.eof()) {
      file.get(current_char);
      file_data.push_back(current_char);
    }

    file.close();
  }

  compute_char_frequency();
}

void Huffman::compress() {

}

void Huffman::decompress() {

}

void Huffman::output_file() {

}

void Huffman::print_file_data() {
  vector<char>::iterator it;
  for (it = file_data.begin(); it != file_data.end(); ++it) {
    cout << *it;
  }
}

void Huffman::print_char_frequency() {
  vector< pair<char, unsigned long long> >::iterator it;
  for (it = char_frequency.begin(); it != char_frequency.end(); ++it) {
    cout << (*it).first << ",\t" << (*it).second << endl;
  }
}

void Huffman::print_huffman_code() {

}

void Huffman::compute_char_frequency() {
  // create temporary map used to count frequencies of each char
  map<char, unsigned long long> temp_char_frequency_map;

  // fill map with characters, updating frequencies when a match (duplicate) is found
  vector<char>::iterator vit;
  for (vit = file_data.begin(); vit != file_data.end(); ++vit) {
    temp_char_frequency_map.insert(pair<char, unsigned long long>(*vit, ++temp_char_frequency_map[*vit]));
  }

  // fill char_frequency with map values
  map<char, unsigned long long>::iterator mit;
  for (mit = temp_char_frequency_map.begin(); mit != temp_char_frequency_map.end(); ++mit) {
    char_frequency.push_back(make_pair(mit->first, mit->second));
  }

  // sort char_frequency by frequency in ascending order
  sort(char_frequency.begin(), char_frequency.end(), sort_frequency);
}
