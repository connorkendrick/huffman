#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <vector>
#include <map>

class Huffman {
  public:
    Huffman(std::string file_name);
    void compress();
    void decompress();
    void output_file();
    void print_file_data();
    void print_char_frequency();
    void print_huffman_code();
  private:
    std::vector<char> file_data;
    std::vector< std::pair<char, unsigned long long> > char_frequency;
    //min_heap_node* root;
};

#endif
