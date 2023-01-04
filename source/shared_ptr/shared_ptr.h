#ifndef SHARED_PTR_H_
#define SHARED_PTR_H_

namespace cpp{

template<typename T>
class SharedPointer{
 public:
  SharedPointer() : pointer_(nullptr),user_count_(nullptr) {}

  SharedPointer(T* pointer) : pointer_(pointer),user_count_(new int(1)) {}

  SharedPointer(const SharedPointer& copy)
      :pointer_(copy.pointer_),
       user_count_(copy.user_count_) {
    if (user_count_ != nullptr) {
      ++(*user_count_);
    }
  }

  SharedPointer(SharedPointer&& move)
      :pointer_(move.pointer_),
       user_count_(move.user_count_) {
    move.pointer_ = nullptr;
    move.user_count_ = nullptr;
  }

  ~SharedPointer(){
    if (user_count_ != nullptr) {
      --(*user_count_);
    }
    if (*user_count_ == 0 || user_count_ == nullptr) {
     delete pointer_;
     delete user_count_;
     pointer_ = nullptr;
     user_count_ = nullptr;
    }
  }

  SharedPointer& operator=(const SharedPointer& copy) {
    if (&copy != this) {
      pointer_ = copy.pointer_;
      user_count_ = copy.user_count_;
      ++(*user_count_);
      return *this;
    }
  }

  SharedPointer& operator=(SharedPointer&& move) {
    if (&move != this) {
      pointer_ = move.pointer_;
      user_count_ = move.user_count_;
      move.pointer_ = nullptr;
      move.user_count_ = nullptr;
      return *this;
    }
  }
      
 private:
  T* pointer_;
  unsigned int* user_count_;
};

} //namespace cpp

#endif //SHARED_PTR_H_