#include"shared_ptr.h"
#include<iostream>
struct a{
  a(){std::cout<<"construct"<<std::endl;}
  ~a(){std::cout<<"destory"<<std::endl;}
};
int main(){
  cpp::SharedPointer<a[]> p = cpp::MakeShared<a>(10);
  return 0;
}
