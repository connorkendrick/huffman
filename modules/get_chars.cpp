#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>

#include "get_chars.h"

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