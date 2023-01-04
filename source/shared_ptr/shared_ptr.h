#ifndef SHARED_PTR_H_
#define SHARED_PTR_H_

#include<utility>

namespace cpp{

template<typename T>
class SharedPointer{
 public:

  SharedPointer() : pointer_(nullptr),user_count_(nullptr) {}

  explicit SharedPointer(T* pointer) : pointer_(pointer),user_count_(new int(1)) {}

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
    if (user_count_ == nullptr || *user_count_ == 0) {
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
    return *this;
  }

  SharedPointer& operator=(SharedPointer&& move) {
    if (&move != this) {
      pointer_ = move.pointer_;
      user_count_ = move.user_count_;
      move.pointer_ = nullptr;
      move.user_count_ = nullptr;
      return *this;
    }
    return *this;
  }

  T* pointer() {
   return pointer_;
  }

  int user_count() {
   return (*user_count);
  }

  bool Unique() {
    if (*user_count != 1 || user_count_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  T operator*() {
    return *pointer_;
  }

  T* operator->() {
    return pointer_;
  }

  explicit operator bool() {
    if (pointer_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  void Reset(T*);
 private:
  T* pointer_;
  int* user_count_;
};

template<typename T>
class SharedPointer<T[]>{
 public:
  SharedPointer() : pointer_(nullptr),user_count_(nullptr) {}

  explicit SharedPointer(T* pointer) : pointer_(pointer),user_count_(new int(1)) {}

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
    if (user_count_ == nullptr || *user_count_ == 0) {
     delete[] pointer_;
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
    return *this;
  }

  SharedPointer& operator=(SharedPointer&& move) {
    if (&move != this) {
      pointer_ = move.pointer_;
      user_count_ = move.user_count_;
      move.pointer_ = nullptr;
      move.user_count_ = nullptr;
      return *this;
    }
    return *this;
  }

  T* pointer() {
   return pointer_;
  }

  int user_count() {
   return (*user_count);
  }

  bool Unique() {
    if (*user_count != 1 || user_count_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  T operator*() {
    return *pointer_;
  }

  T operator[](unsigned int index) {
   return pointer_[index];
  }

  T* operator->() {
    return pointer_;
  }

  explicit operator bool() {
    if (pointer_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }

  void Reset(T*);
  
 private:
  T* pointer_;
  int* user_count_;
};


template<typename T>
void SharedPointer<T>::Reset(T* pointer){
  if (*user_count_ == 1) {
    auto p = pointer_;
    pointer_ = pointer;
    delete p;
  } else if (user_count_ == nullptr) {
    pointer_ = pointer;
    user_count_ = new int(1);
  } else {
    pointer_ = pointer;
    --(*user_count_);
    user_count_ = new int(1);
  }
}

template<typename T>
void SharedPointer<T[]>::Reset(T* pointer){
  if (*user_count_ == 1) {
    auto p = pointer_;
    pointer_ = pointer;
    delete[] p;
  } else if (user_count_ == nullptr) {
    pointer_ = pointer;
    user_count_ = new int(1);
  } else {
    pointer_ = pointer;
    --(*user_count_);
    user_count_ = new int(1);
  }
}

template<typename T, typename... Args>
SharedPointer<T> MakeShared(Args&&... args) {
  return SharedPointer<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
SharedPointer<T[]> MakeShared(int size) {
  return SharedPointer<T[]>(new T[size]);
}

} //namespace cpp

#endif //SHARED_PTR_H_