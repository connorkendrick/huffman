#include "Huffman.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

/* Helper functions */
bool sort_frequency(const pair<char, unsigned long long>& p1, const pair<char, unsigned long long>& p2) {
  return (p1.second < p2.second);
}

struct priority_queue_compare {
  bool operator() (const min_heap_node& left, const min_heap_node& right) {
    return (left.frequency > right.frequency);
  }
};

/* Huffman member functions */
explicit Huffman::Huffman(const string& file_name) {
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

void Huffman::print_huffman_code(min_heap_node *root, const string& str) {
  if (!root) {
    return;
  }
  if (!root->is_internal) {
    cout << root->data << ": " << str << "\n";
  }

  print_huffman_code(root->left, str + "0");
  print_huffman_code(root->right, str + "1");
}

void Huffman::print_huffman_code() {
  min_heap_node *proot = &root;
  print_huffman_code(proot, "");
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

void Huffman::generate_huffman_tree() {
  priority_queue<min_heap_node, vector<min_heap_node>, priority_queue_compare> min_heap;
  vector< pair<char, unsigned long long> >::iterator it;
  for (it = char_frequency.begin(); it != char_frequency.end(); ++it) {
    min_heap.push(min_heap_node(it->first, it->second, false));
  }

  // COULD RUN INTO POSSIBLE ERRORS IF THE MIN HEAP IS EMPTY - PUT PRECONDITION ON THIS FUNCTION?
  while (min_heap.size() > 1) {
    min_heap_node obj1(min_heap.top());
    min_heap.pop();

    min_heap_node obj2(min_heap.top());
    min_heap.pop();

    min_heap_node internal('X', obj1.frequency + obj2.frequency);
    internal.left = obj1;
    internal.right = obj2;
    min_heap.push(internal);
  }

  root = min_heap.top();
  // OBJECTS WONT WORK, NEED TO USE SHARED POINTER
}
