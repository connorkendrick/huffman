#include <vector>
#include <queue>

#include "create_hcode.h"

using namespace std;

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