#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
  ifstream file;
  file.open("words.txt", ios::in);

  if (file.is_open())
  {
    char my_char;
  
    while (!file.eof())
    {
      file.get(my_char);
      cout << my_char;
    }

    file.close();
  }
  else
  {
    cout << "Unable to open file";
  }

  return 0;
}
