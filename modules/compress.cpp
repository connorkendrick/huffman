#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <bitset>

#include "compress.h"

using namespace std;

void compress(vector<char> char_vector, map<char, string> hcode_table)
{
  ofstream output("compressed.bin", ios::binary);
  string buffer = "";
  bitset<8> bset;
  unsigned long n;
  
  for (size_t i = 0; i < char_vector.size(); ++i)
  {
    buffer += hcode_table[char_vector[i]];
  }
  
  if (buffer.length() < 8)
  {
    buffer += string(8 - buffer.length(), '0');
  }
  else if (buffer.length() % 8 != 0)
  {
    buffer += string(8 - (buffer.length() % 8), '0');
  }
  
  while (buffer.length() != 0)
  {
    bset = bitset<8>(buffer.substr(0, 8));
    n = bset.to_ulong();
    unsigned char c = static_cast<unsigned char>(n);

    output.write(reinterpret_cast<char*>(&c), sizeof(c));
    
    buffer.erase(0, 8);
  }
  
  output.close();
}

// I ran this on a very large text file and it took way too long to compress
// I need to find a more efficient way to compress
// Maybe not putting everything into a string in the beginning? I don't think that would help though,
// because it was still writing to the bin file, but it was taking a very long time.