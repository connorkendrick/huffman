#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>
#include <vector>

#include "get_freq.h"

using namespace std;

// Custom comparator function for sorting vector of pairs by second value (ascending order)
bool sort_second(const pair<char,unsigned long long> &a, const pair<char,unsigned long long> &b)
{
  return (a.second < b.second);
}

// Returns a vector of pairs with the character first and frequency second 
vector< pair<char,unsigned long long> > get_freq(vector<char> char_vector)
{
  map<char,unsigned long long> freq_map;
  vector< pair<char,unsigned long long> > freq_vector;

  // Fill map with characters, updating frequencies when a match is found
  for (size_t n = 0; n < char_vector.size(); ++n)
  {
    cout << char_vector[n];
    freq_map.insert(pair<char,unsigned long long>(char_vector[n], ++freq_map[char_vector[n]]));
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