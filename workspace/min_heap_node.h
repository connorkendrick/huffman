#ifndef NODE
#define NODE

struct min_heap_node {
  min_heap_node() {};
  min_heap_node(char data, unsigned long long frequency, bool is_internal) {
    left = 0;
    right = 0;
    this->data = data;
    this->frequency = frequency;
    this->is_internal = is_internal;
  };
  min_heap_node(const min_heap_node& obj) {
    left = obj.left;
    right = obj.right;
    data = obj.data;
    frequency = obj.frequency;
    is_internal = obj.is_internal;
  };
  min_heap_node& operator= (const min_heap_node& obj) {
    left = obj.left;
    right = obj.right;
    data = obj.data;
    frequency = obj.frequency;
    is_internal = obj.is_internal;
    return *this;
  };
  min_heap_node left;
  min_heap_node right;
  char data;
  unsigned long long frequency;
  bool is_internal;
};

#endif
