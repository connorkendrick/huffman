#include <fstream>
#include <ios>
#include <bitset>
#include <string>

using namespace std;

main()
{
  // Still need to figure out how to append '0b' onto the number
  
  // When encoding, I can go to the table and pull the code for the letter I'm at,
  // put the code in a "buffer", and place each number in an unsigned char variable
  // If variable fills: push variable and start another
  // If code ends and variable isn't filled: pull next letter's code into buffer and continue
  // The final character will most likely be missing a few bits. This needs to be filled in then pushed.
  // If a character is not full when pushed, it will mess up the ordering of numbers by putting 0's before the code.
  
  // WAIT: I could hold the entire encoded message in a string variable and go character by character and fill up
  // unsigned char variables. Then when I'm decoding, I can hold the interpretation of it in a string variable,
  // and go character by character until a match is found (using the tree)
  string char_01 = "10111001";
  string char_02 = "10011011";
  bitset<8> buffer;
  unsigned long n;
  
  buffer = bitset<8>(char_01);
  n = buffer.to_ulong(); 
  unsigned char F = static_cast<unsigned char>(n);
  
  buffer = bitset<8>(char_02);
  n = buffer.to_ulong();
  unsigned char G = static_cast<unsigned char>(n);
  
  ofstream K("binary.bin", ios::binary);
  K.write(reinterpret_cast<char*>(&F), sizeof(F));
  K.write(reinterpret_cast<char*>(&G), sizeof(G));
  
  K.close();
  
  return 0;
}