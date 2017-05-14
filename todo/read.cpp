#include <fstream>
#include <ios>
#include <iostream>

using namespace std;

main()
{
  ifstream f("compressed.bin", ios::binary | ios::in);
  char c;
  while (f.get(c))
  {
    for (int i = 7; i >= 0; i--) // or (int i = 0; i < 8; i++)  if you want reverse bit order in bytes
      cout << ((c >> i) & 1);
  }
  
  return 0;
}