#ifndef MHN
#define MHN

struct min_heap_node
{
  min_heap_node(const char& data, const unsigned long long& freq, const bool& internal);
  
  char data;
  unsigned long long freq;
  bool internal;
  min_heap_node *left;
  min_heap_node *right;
};

#endif