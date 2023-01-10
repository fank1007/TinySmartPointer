#include <iostream>
#include "shared_ptr.h"
struct a;
struct b;
struct a {
  a() { std::cout << "a:construct" << std::endl; }
  ~a() { std::cout << "a:destory" << std::endl; }
  cpp::SharedPointer<b> ap;
};
struct b {
  b() { std::cout << "b:construct" << std::endl; }
  ~b() { std::cout << "b:destory" << std::endl; }
  cpp::SharedPointer<a> bp;
};
int main() {
  cpp::SharedPointer<a> p = cpp::MakeShared<a>();
  cpp::SharedPointer<b> p1 = cpp::MakeShared<b>();
  p->ap = p1;
  return 0;
}
