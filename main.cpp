#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "modules/min_heap_node.h"
#include "modules/get_freq.h"
#include "modules/create_hcode.h"
#include "modules/print_hcode.h"
#include "modules/map_hcode.h"
#include "modules/get_chars.h"
#include "modules/compress.h"

using namespace std;

int main()
{
  string file_name = "input.txt";
  vector<char> char_vector = get_chars(file_name);
  
  vector< pair<char,unsigned long long> > freq_vector = get_freq(char_vector);

  min_heap_node* root = create_hcode(freq_vector);
  cout << endl << endl;
  print_hcode(root, "");
  
  map<char,string> hcode_table;
  map_hcode(hcode_table, root);
  
  compress(char_vector, hcode_table);

  return EXIT_SUCCESS;
}
