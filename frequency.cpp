#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool sort_second(const pair<char,int> &a, const pair<char,int> &b)
{
  return (a.second < b.second);
}

int main()
{
  map<char,int> freq_map;
  vector< pair<char,int> > freq_vector;

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

  for (map<char,int>::iterator mi = freq_map.begin(); mi != freq_map.end(); ++mi)
  {
    freq_vector.push_back(make_pair(mi->first, mi->second));
  }

  sort(freq_vector.begin(), freq_vector.end(), sort_second);

  cout << endl << endl;

  for (size_t i = 0; i < freq_vector.size(); ++i)
  {
    cout << freq_vector[i].first << ",\t" << freq_vector[i].second << endl;
  }

  return 0;
}
