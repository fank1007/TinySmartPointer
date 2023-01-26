#ifndef UNIQUE_PTR_H_
#define UNIQUE_PTR_H_

#include <utility>

namespace cpp {

/**
 * @brief 独占智能指针
 *
 * 每次只能有一个智能指针持有资源，无法拷贝，只能移动
 *
 * @tparam T 存放指针的类型
 */
template <typename T>
class UniquePointer {
 public:
  /**
   * @brief 默认构造函数
   *
   */
  UniquePointer() : pointer_(nullptr) {}

  /**
   * @brief 构造函数
   *
   * @param pointer 存入智能指针的资源
   */
  explicit UniquePointer(T* pointer) : pointer_(pointer) {}

  /**
   * @brief 删除的拷贝构造函数
   *
   * @param copy
   */
  UniquePointer(const UniquePointer& copy) = delete;

  /**
   * @brief 移动构造函数
   *
   * 转移所有权
   *
   * @param move {Unique&&} 被移动的对象
   */
  UniquePointer(UniquePointer&& move) : pointer_(move.pointer_) {
    move.pointer_ = nullptr;
  }

  ~UniquePointer() {
    delete pointer_;
    pointer_ = nullptr;
  }

  /**
   * @brief 删除的拷贝赋值运算符
   *
   * @param copy
   * @return UniquePointer&
   */
  UniquePointer& operator=(const UniquePointer& copy) = delete;

  /**
   * @brief 移动赋值运算符
   *
   *转移所有权
   *
   * @param move {Unique&&} 被移动的对象
   * @return UniquePointer& 返回 *this
   */
  UniquePointer& operator=(UniquePointer&&);

  /**
   * @brief 返回存放的指针
   *
   * @return T* 返回存放的指针
   */
  T operator*() { return *pointer_; }

  /**
   * @brief 访问类成员
   *
   * @return T*
   */
  T* operator->() { return pointer_; }

  /**
   * @brief 返回存放的指针
   *
   * @return T* 返回存放的指针
   */
  T* pointer() { return pointer_; }

  /**
   * @brief 判断该指针是否为空
   *
   * @return true 该指针为空
   * @return false 反之
   */
  explicit operator bool() { return pointer_ != nullptr; }

  /**
   * @brief 销毁原资源，存入新资源
   *
   * @param pointer 存入的新资源
   */
  void Reset(T* pointer) {
    auto p = pointer_;
    pointer_ = pointer;
    delete p;
  }

 private:
  T* pointer_;
};

/**
 * @brief 类模板特化用于处理数组类型
 *
 * @tparam T
 */
template <typename T>
class UniquePointer<T[]> {
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

  UniquePointer& operator=(UniquePointer&&);

  T operator*() { return *pointer_; }

  T* operator->() { return pointer_; }

  T* pointer() { return pointer_; }

  T operator[](int index) { return pointer_[index]; }

  explicit operator bool() { return pointer_ != nullptr; }

  void Reset(T* pointer) {
    auto p = pointer_;
    pointer_ = pointer;
    delete[] p;
  }

 private:
  T* pointer_;
};
template <typename T>
UniquePointer<T>& UniquePointer<T>::operator=(UniquePointer&& move) {
  if (&move != this) {
    if (this->pointer_ == nullptr) {
      pointer_ = move.pointer_;
      move.pointer_ = nullptr;
      return *this;
    } else {
      delete pointer_;
      pointer_ = move.pointer_;
      move.pointer_ = nullptr;
      return *this;
    }
  }
  return *this;
}

template <typename T>
UniquePointer<T[]>& UniquePointer<T[]>::operator=(UniquePointer&& move) {
  if (&move != this) {
    if (this->pointer_ == nullptr) {
      pointer_ = move.pointer_;
      move.pointer_ = nullptr;
      return *this;
    } else {
      delete[] pointer_;
      pointer_ = move.pointer_;
      move.pointer_ = nullptr;
      return *this;
    }
  }
  return *this;
}

/**
 * @brief 构造一个智能指针并返回
 *
 * @tparam T 智能指针存放指针的类型
 * @tparam Args 参数包
 * @param args 参数包
 * @return UniquePointer<T> 返回一个智能指针
 */
template <typename T, typename... Args>
UniquePointer<T> MakeUnique(Args&&... args) {
  return std::move(UniquePointer<T>(new T(std::forward<Args>(args)...)));
}

}  // namespace cpp

#endif  // UNIQUE_PTR_H_