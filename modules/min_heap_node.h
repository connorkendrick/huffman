#ifndef MHN_H
#define MHN_H

struct min_heap_node
{
  min_heap_node(char data, unsigned long long freq, bool internal);
  
  char data;
  unsigned long long freq;
  bool internal;
  min_heap_node *left;
  min_heap_node *right;
};

#endif