#ifndef HUFFMAN
#define HUFFMAN

#include "min_heap_node.h"
#include <string>
#include <vector>
#include <map>

class Huffman {
  public:
    explicit Huffman(const std::string& file_name);
    // Precondition: file_name is a valid path to a file
    // Postcondition: Each character in file_name has been transferred to file_data
    void compress();
    // Postcondition: file_data has been overwritten with the compressed data
    void decompress();
    // Postcondition: file_data has been overwritten with the decompressed data
    void output_file();
    // Postcondition: file_data has been written and saved to the disk as a new file
    void print_file_data();
    // Postcondition: file_data has been printed to standard output
    void print_char_frequency();
    // Postcondition: char_frequency has been printed to standard output
    void print_huffman_code();
    void print_huffman_code(min_heap_node *root, const std::string& str);
    // Postcondition: A representation of the Huffman Code table has been printed to standard output
  private:
    /* Functions */
    void compute_char_frequency();
    // Postcondition: char_frequency contains one of each character in file_data and the corresponding frequencies
    void generate_huffman_tree();
    // Postcondition: root is now the root node of the min heap (huffman tree)

    /* Variables */
    std::vector<char> file_data;
    // Stores the data that is being managed
    std::vector< std::pair<char, unsigned long long> > char_frequency;
    // Maps each character with its frequency
    min_heap_node *root;
    // Points to the root of a min heap (Huffman Tree)
};

#endif
