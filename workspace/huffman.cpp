#include "Huffman.h"
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <iostream>

using namespace std;

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
}

void Huffman::compress() {

}

void Huffman::decompress() {

}

void Huffman::output_file() {

}

void Huffman::print_file_data() {
  vector<char>::iterator it;
  for (it = file_data.begin(); it < file_data.end(); ++it) {
    cout << *it;
  }
}

void Huffman::print_char_frequency() {

}

void Huffman::print_huffman_code() {

}
