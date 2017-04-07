#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>
#include <queue>

#include "modules/min_heap_node.h"
#include "modules/get_freq.h"
#include "modules/create_hcode.h"
#include "modules/print_hcode.h"

using namespace std;

int main()
{
  string file_name = "input.txt";
  vector< pair<char,unsigned long long> > freq_vector = get_freq(file_name);

  min_heap_node* root = create_hcode(freq_vector);
  cout << endl << endl;
  print_hcode(root, "");

  return EXIT_SUCCESS;
}
