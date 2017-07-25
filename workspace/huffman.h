#ifndef HUFFMAN
#define HUFFMAN

#include <string>
#include <vector>
#include <map>

class huffman {
  public:
    huffman(std::string file_name);
    void compress();
    void decompress();
    void output_file();
    void print_file_contents();
    void print_char_frequency();
    void print_huffman_code();
  private:
    std::string file_name;
    std::vector<char> char_vector;
    std::vector< std::pair<char, unsigned long long> > char_frequency;
    //min_heap_node* root;
};

#endif
