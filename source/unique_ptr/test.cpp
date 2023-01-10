#include <iostream>

#include "unique_ptr.h"
struct a {
  a() { std::cout << "construct" << std::endl; }
  ~a() { std::cout << "destory" << std::endl; }
};
int main() {
  cpp::UniquePointer<a> p = cpp::MakeUnique<a>();
  return 0;
}