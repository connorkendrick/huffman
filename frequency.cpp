#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

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

struct min_heap_node
{
  char data;

};

int main()
{
  string file_name = "words.txt";
  vector< pair<char,unsigned long long> > freq_vector = get_freq(file_name);

  return 0;
}
