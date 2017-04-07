#include <string>
#include <iostream>

#include "print_hcode.h"

using namespace std;

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