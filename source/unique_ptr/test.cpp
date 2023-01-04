#include"unique_ptr.h"
#include<iostream>
struct a{
  a(){std::cout<<"construct"<<std::endl;}
  ~a(){std::cout<<"destory"<<std::endl;}
};
int main(){
  cpp::UniquePointer<a[]> p = cpp::MakeUnique<a>(10);
  return 0;
}