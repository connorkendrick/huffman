#include "hcode.h"
#include "min_heap_node.h"

#include <cstdlib>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

// Returns a vector of characters so that the file only needs to be opened once
vector<char> get_chars(const string& file_name)
{
  vector<char> file_chars;

  ifstream file;
  file.open(file_name.c_str(), ios::in);

  if (file.is_open())
  {
    char my_char;
  
    while (!file.eof())
    {
      file.get(my_char);
      file_chars.push_back(my_char);
    }

    file.close();
  }
  else
  {
    cout << "Unable to open file";
    exit(EXIT_FAILURE);
  }

  return file_chars;
}

// Custom comparator function for sorting vector of pairs by second value (ascending order)
bool sort_second(const pair<char,unsigned long long>& a, const pair<char,unsigned long long>& b)
{
  return (a.second < b.second);
}

// Returns a vector of pairs with the character first and frequency second 
vector< pair<char,unsigned long long> > get_freq(const vector<char>& char_vector)
{
  map<char,unsigned long long> freq_map;
  vector< pair<char,unsigned long long> > freq_vector;

  // Fill map with characters, updating frequencies when a match is found
  for (size_t n = 0; n < char_vector.size(); ++n)
  {
    freq_map.insert(pair<char,unsigned long long>(char_vector[n], ++freq_map[char_vector[n]]));
  }

  // Fill vector with map values
  for (map<char,unsigned long long>::iterator mi = freq_map.begin(); mi != freq_map.end(); ++mi)
  {
    freq_vector.push_back(make_pair(mi->first, mi->second));
  }

  // Sort vector
  sort(freq_vector.begin(), freq_vector.end(), sort_second);
  
  // Print frequencies
  cout << endl << endl;
  for (size_t i = 0; i < freq_vector.size(); ++i)
  {
    cout << freq_vector[i].first << ",\t" << freq_vector[i].second << endl;
  }

  return freq_vector;
}

// Custom comparator function for priority queue
struct min_heap_compare
{
  bool operator()(min_heap_node* const& left, min_heap_node* const& right)
  {
    return (left->freq > right->freq);
  }
};

min_heap_node* create_hcode(const vector< pair<char,unsigned long long> >& freq_vector)
{
  min_heap_node *left;
  min_heap_node *right;
  min_heap_node *top;

  // Create min heap, fill it with the characters and frequencies, then set 'internal' to false
  // (These nodes are leaves, so they will not be internal nodes)
  priority_queue<min_heap_node*, vector<min_heap_node*>, min_heap_compare> min_heap;
  for (size_t i = 0; i < freq_vector.size(); ++i)
  {
    min_heap.push(new min_heap_node(freq_vector[i].first, freq_vector[i].second, false));
  }

  // Heap will be compressed into one node (root)
  while (min_heap.size() != 1)
  {
    // Pull out first min freq element
    left = min_heap.top();
    min_heap.pop();

    // Pull out second min freq element
    right = min_heap.top();
    min_heap.pop();

    // Create internal node with freq equal to sum of left and right freq
    // This node's left and right children will be the left and right nodes, respectively
    // Push new internal node into min heap
    top = new min_heap_node('X', left->freq + right->freq, true);
    top->left = left;
    top->right = right;
    min_heap.push(top);
  }

  // Returns the root node of the min heap
  return min_heap.top();
}

// Assigns bit pattern to each character using the Huffman tree
void map_hcode(map<char,string>& hcode_table, min_heap_node* const& root, const string& str)
{
  if (!root)
  {
    return;
  }

  if (!root->internal)
  {
    hcode_table[root->data] = str;
  }

  map_hcode(hcode_table, root->left, str + "0");
  map_hcode(hcode_table, root->right, str + "1");
}

// Prints a representation of the huffman code table
void print_hcode(min_heap_node* const& root, const string& str)
{
  if (!root)
  {
    return;
  }

  if (!root->internal)
  {
    cout << root->data << ": " << str << "\n";
  }

  print_hcode(root->left, str + "0");
  print_hcode(root->right, str + "1");
}

// Compresses the original text file using the huffman code table
void compress(const vector<char>& char_vector, const map<char, string>& hcode_table)
{
  ofstream output("compressed.bin", ios::binary);
  string buffer = "";
  bitset<8> bset;
  unsigned long n;
    
  for (size_t i = 0; i < char_vector.size(); ++i)
  {
    buffer += hcode_table.at(char_vector[i]);
  }
    
  if (buffer.length() < 8)
  {
    buffer += string(8 - buffer.length(), '0');
  }
  else if (buffer.length() % 8 != 0)
  {
    buffer += string(8 - (buffer.length() % 8), '0');
  }
  
  size_t current = 0;
  for (size_t count = 0; count * 8 < buffer.length(); ++count)
  {
    bset = bitset<8>(buffer.substr(current, current + 8));
    n = bset.to_ulong();
    unsigned char c = static_cast<unsigned char>(n);
        
    output.write(reinterpret_cast<char*>(&c), sizeof(c));

    current += 8;
  }
  
  output.close();
}