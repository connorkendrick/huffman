#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

using namespace std;

// Custom comparator function for sorting vector of pairs by second value (ascending order)
bool sort_second(const pair<char,unsigned long long> &a, const pair<char,unsigned long long> &b)
{
  return (a.second < b.second);
}

// Returns a vector of pairs with the character first and frequency second 
vector< pair<char,unsigned long long> > get_freq(string file_name)
{
  map<char,unsigned long long> freq_map;
  vector< pair<char,unsigned long long> > freq_vector;

  // Open file whose name was passed in to get_freq
  ifstream file;
  file.open(file_name.c_str(), ios::in);

  // Fill map with characters, updating frequencies when a match is found
  if (file.is_open())
  {
    char my_char;
  
    while (!file.eof())
    {
      file.get(my_char);
      cout << my_char;
      freq_map.insert(pair<char,unsigned long long>(my_char, freq_map[my_char]++));
    }

    file.close();
  }
  else
  {
    cout << "Unable to open file";
    exit(EXIT_FAILURE);
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

// Node for Huffman Tree
struct min_heap_node
{
  char data;
  unsigned long long freq;
  bool internal;
  min_heap_node *left;
  min_heap_node *right;

  min_heap_node(char data, unsigned long long freq, bool internal)
  {
    left = NULL;
    right = NULL;
    this->data = data;
    this->freq = freq;
    this->internal = internal;
  }
};

struct min_heap_compare
{
  bool operator()(min_heap_node* left, min_heap_node* right)
  {
    return (left->freq > right->freq);
  }
};

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

int main()
{
  string file_name = "words.txt";
  vector< pair<char,unsigned long long> > freq_vector = get_freq(file_name);

  min_heap_node* root = create_hcode(freq_vector);
  cout << endl << endl;
  print_hcode(root, "");

  return EXIT_SUCCESS;
}
