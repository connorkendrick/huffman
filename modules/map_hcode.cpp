#include <string>
#include <map>

#include "map_hcode.h"
#include "min_heap_node.h"

using namespace std;

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