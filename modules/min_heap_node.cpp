#include "min_heap_node.h"

#include <cstddef>

min_heap_node::min_heap_node(const char& data, const unsigned long long& freq, const bool& internal)
{
  left = NULL;
  right = NULL;
  this->data = data;
  this->freq = freq;
  this->internal = internal;
}