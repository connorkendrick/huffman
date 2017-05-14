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
      cout << my_char; // test
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
    cout << char_vector[n];
    freq_map.insert(pair<char,unsigned long long>(char_vector[n], ++freq_map[char_vector[n]]));
  }

  // Fill vector with map values
  for (map<char,unsigned long long>::iterator mi = freq_map.begin(); mi != freq_map.end(); ++mi)
  {
    freq_vector.push_back(make_pair(mi->first, mi->second));
  }

  // Sort vector
  sort(freq_vector.begin(), freq_vector.end(), sort_second);

  cout << endl << endl;

  for (size_t i = 0; i < freq_vector.size(); ++i)
  {
    cout << freq_vector[i].first << ",\t" << freq_vector[i].second << endl;
  }

  return freq_vector;
}

struct min_heap_compare
{
  bool operator()(min_heap_node* left, min_heap_node* right)
  {
    return (left->freq > right->freq);
  }
};

min_heap_node* create_hcode(vector< pair<char,unsigned long long> > freq_vector)
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

void map_hcode(map<char,string> &hcode_table, min_heap_node* root, string str)
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

void print_hcode(min_heap_node* root, string str)
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

void compress(vector<char> char_vector, map<char, string> hcode_table)
{
  ofstream output("compressed.bin", ios::binary);
  string buffer = "";
  bitset<8> bset;
  unsigned long n;
  
  // could skip the buffer entirely
  
  for (size_t i = 0; i < char_vector.size(); ++i)
  {
    buffer += hcode_table[char_vector[i]];
  }
  
  // just check if the vector length is < 8 and add to it instead
  
  if (buffer.length() < 8)
  {
    buffer += string(8 - buffer.length(), '0');
  }
  else if (buffer.length() % 8 != 0)
  {
    buffer += string(8 - (buffer.length() % 8), '0');
  }
  
  // instead of removing items from the container holding it,
  // I could just iterate along it using an int variable to count
  
  while (buffer.length() != 0)
  {
    bset = bitset<8>(buffer.substr(0, 8));
    n = bset.to_ulong();
    unsigned char c = static_cast<unsigned char>(n);

    output.write(reinterpret_cast<char*>(&c), sizeof(c)); // STORE CHARACTER IN A BUFFER AND DON'T WRITE TO THE FILE EVERY TIME!!!!!
    
    buffer.erase(0, 8);
  }
  
  output.close();
}
// I ran this on a very large text file and it took way too long to compress
// I need to find a more efficient way to compress
// Maybe not putting everything into a string in the beginning? I don't think that would help though,
// because it was still writing to the bin file, but it was taking a very long time.



