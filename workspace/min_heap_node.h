#ifndef NODE
#define NODE

struct min_heap_node {
  min_heap_node(char data, unsigned long long frequency, bool is_internal) {
    left = 0;
    right = 0;
    this->data = data;
    this->frequency = frequency;
    this->is_internal = is_internal;
  };
  min_heap_node *left;
  min_heap_node *right;
  char data;
  unsigned long long freq;
  bool internal;
};

#endif
