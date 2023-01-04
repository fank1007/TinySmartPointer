#ifndef UNIQUE_PTR_H_
#define UNIQUE_PTR_H_

#include<utility>

namespace cpp{

template<typename T>
class UniquePointer{
 public:
  UniquePointer() : pointer_(nullptr) {}
  explicit UniquePointer(T* pointer) : pointer_(pointer) {}
  UniquePointer(const UniquePointer& copy) = delete;
  UniquePointer(UniquePointer&& move) : pointer_(move.pointer_) {
    move.pointer_ = nullptr;
  }
  ~UniquePointer() {
    delete pointer_;
    pointer_ = nullptr;
  }
  UniquePointer& operator=(const UniquePointer& copy) = delete;
  UniquePointer& operator=(UniquePointer&& move) {
    if (&move != this) {
      pointer_ = move.pointer_;
      move.pointer_ = nullptr;
    }
  }

  T operator*() {
    return *pointer_;
  }

  T* operator->() {
    return pointer_;
  }

  T* pointer() {
    return pointer_;
  }

  explicit operator bool() {
    if (pointer_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }
  
  void Reset(T* pointer) {
    auto p = pointer_;
    pointer_ = pointer;
    delete p;
  }
 private:
  T* pointer_;
};

template<typename T>
class UniquePointer<T[]>{
 public:
  UniquePointer() : pointer_(nullptr) {}
  explicit UniquePointer(T* pointer) : pointer_(pointer) {}
  UniquePointer(const UniquePointer& copy) = delete;
  UniquePointer(UniquePointer&& move) : pointer_(move.pointer_) {
    move.pointer_ = nullptr;
  }
  ~UniquePointer() {
    delete[] pointer_;
    pointer_ = nullptr;
  }
  UniquePointer& operator=(const UniquePointer& copy) = delete;
  UniquePointer& operator=(UniquePointer&& move) {
    if (&move != this) {
      pointer_ = move.pointer_;
      move.pointer_ = nullptr;
    }
  }

  T operator*() {
    return *pointer_;
  }

  T* operator->() {
    return pointer_;
  }

  T* pointer() {
    return pointer_;
  }

  T operator[](int index) {
    return pointer_[index];
  }

  explicit operator bool() {
    if (pointer_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }
  
  void Reset(T* pointer) {
    auto p = pointer_;
    pointer_ = pointer;
    delete[] p;
  }
 private:
  T* pointer_;
};

template<typename T, typename... Args>
UniquePointer<T> MakeUnique(Args&&... args) {
  return std::move(UniquePointer<T>(new T(std::forward<Args>(args)...)));
}

template<typename T>
UniquePointer<T[]> MakeUnique(int size) {
  return std::move(UniquePointer<T[]>(new T[size]));
}

} //namespace cpp

#endif //UNIQUE_PTR_H_