#ifndef SHARED_PTR_H_
#define SHARED_PTR_H_

#include<utility>
#include<mutex>

namespace cpp{


/**
 * @brief 引用计数智能指针
 * 
 * 通过引用计数对资源进行管理，在离开作用域时，如果计数为零则释放资源
 * 
 * @tparam T {存放的指针类型}
 */
template<typename T>
class SharedPointer{
 public:
  /**
   * @brief 默认构造函数
   * 
   */
  SharedPointer() : pointer_(nullptr), user_count_(nullptr) {}
  /**
   * @brief 构造函数
   * 
   * @param pointer {T*}   智能指针内存放的资源
   */
  explicit SharedPointer(T* pointer) : pointer_(pointer), user_count_(new int(1)) {}

  /**
   * @brief 拷贝构造函数
   * 
   * 浅拷贝一个智能指针，在每次拷贝时使计数增加1；
   * 
   * @param copy {const SharedPointer&} 被拷贝的对象
   */
  SharedPointer(const SharedPointer& copy)
      :pointer_(copy.pointer_),
       user_count_(copy.user_count_) {
    if (user_count_ != nullptr) {
      ++(*user_count_);
    }
  }


  /**
   * @brief 移动构造函数
   * 
   * 转移所有权
   * 
   * @param move {SharedPointer&&} 被移动的对象
   */
  SharedPointer(SharedPointer&& move)
      :pointer_(move.pointer_),
       user_count_(move.user_count_) {
    move.pointer_ = nullptr;
    move.user_count_ = nullptr;
  }

  
  /**
   * @brief 析构函数
   * 
   * 销毁一个智能指针，将计数减1，在计数等于0时，释放内存
   * 
   */
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


  /**
   * @brief 拷贝赋值运算符
   * 
   * 浅拷贝一个智能指针，并将计数加1
   * 在进行自我赋值时不做任何事
   * 
   * @param copy {const SharedPointer&} 被拷贝的对象
   * @return SharedPointer& 返回 *this
   */
  SharedPointer& operator=(const SharedPointer& copy) {
    std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
    if (&copy != this) {
      pointer_ = copy.pointer_;
      user_count_ = copy.user_count_;
      ++(*user_count_);
      return *this;
    }
    return *this;
  }


  /**
   * @brief 移动赋值运算符
   * 
   * 转移所有权
   * 在自我赋值时不做任何事
   * 
   * @param move {SharedPointer&&} 被移动的对象
   * @return SharedPointer&  返回 *this
   */
  SharedPointer& operator=(SharedPointer&& move) {
    std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
    if (&move != this) {
      pointer_ = move.pointer_;
      user_count_ = move.user_count_;
      move.pointer_ = nullptr;
      move.user_count_ = nullptr;
      return *this;
    }
    return *this;
  }


  /**
   * @brief 返回存放的指针
   * 
   * @return T* 返回存放的指针
   */
  T* pointer() {
   return pointer_;
  }


  /**
   * @brief 返回当前指针的计数
   * 
   * @return int 返回当前指针的计数
   */
  int user_count() {
   return (*user_count_);
  }


  /**
   * @brief 查看是否只有一个智能指针管理该资源
   * 
   * @return true 只有一个对象管理该资源
   * @return false 反之
   */
  bool Unique() {
    if (*user_count_ != 1 || user_count_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }


  /**
   * @brief 返回指针指向的对象
   * 
   * @return T 指向的对象
   */
  T operator*() {
    return *pointer_;
  }


  /**
   * @brief 访问类成员
   * 
   * @return T* 
   */
  T* operator->() {
    return pointer_;
  }

  /**
   * @brief 判断该指针是否为空
   * 
   * @return true 该指针为空
   * @return false 反之
   */
  explicit operator bool() {
    if (pointer_ == nullptr) {
      return false;
    } else {
      return true;
    }
  }


  /**
   * @brief 重新设置指针
   * 
   * 在计数为1的时候释放原资源，否则计数减1
   * 
   */
  void Reset(T*);

 private:
  T* pointer_;
  int* user_count_;
  std::mutex mutex_;
};


/**
 * @brief 类模板特化用于处理数组类型
 * 
 * @tparam T 
 */
template<typename T>
class SharedPointer<T[]>{
 public:
  SharedPointer() : pointer_(nullptr), user_count_(nullptr) {}

  explicit SharedPointer(T* pointer) : pointer_(pointer), user_count_(new int(1)) {}

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
    std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
    if (&copy != this) {
      pointer_ = copy.pointer_;
      user_count_ = copy.user_count_;
      ++(*user_count_);
      return *this;
    }
    return *this;
  }

  SharedPointer& operator=(SharedPointer&& move) {
    std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
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
    if (*user_count_ != 1 || user_count_ == nullptr) {
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
  std::mutex mutex_;
};


template<typename T>
void SharedPointer<T>::Reset(T* pointer) {
  std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
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
void SharedPointer<T[]>::Reset(T* pointer) {
  std::unique_lock<std::mutex> lock(mutex_, std::try_to_lock);
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


/**
 * @brief 构造一个智能指针并返回
 * 
 * @tparam T 智能指针存放指针的类型
 * @tparam Args 参数包
 * @param args 参数包
 * @return SharedPointer<T> 返回一个智能指针
 */
template<typename T, typename... Args>
SharedPointer<T> MakeShared(Args&&... args) {
  return std::move(SharedPointer<T>(new T(std::forward<Args>(args)...)));
}


/**
 * @brief 构造一个智能指针并返回
 * 
 * @tparam T 智能指针存放指针的类型
 * @param size 数组的大小
 * @return SharedPointer<T[]> 返回一个智能指针
 */
template<typename T>
SharedPointer<T[]> MakeShared(int size) {
  return std::move(SharedPointer<T[]>(new T[size]));
}

} //namespace cpp

#endif //SHARED_PTR_H_