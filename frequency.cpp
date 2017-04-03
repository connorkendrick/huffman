#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
  map<char,int> freq_map;

  ifstream file;
  file.open("words.txt", ios::in);

  if (file.is_open())
  {
    char my_char;
  
    while (!file.eof())
    {
      file.get(my_char);
      cout << my_char;
      freq_map.insert(pair<char,int>(my_char, freq_map[my_char]++));
    }

    file.close();
  }
  else
  {
    cout << "Unable to open file";
  }

  cout << endl << endl;
  cout << "Frequency of the letter 'b': " << freq_map['b'];

  return 0;
}
