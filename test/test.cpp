#include<gtest/gtest.h>
#include<shared_ptr/shared_ptr.h>
#include<unique_ptr/unique_ptr.h>
#include<utility>

TEST(smart_pointer, shared_pointer){
  cpp::SharedPointer<int> pointer1;
  EXPECT_EQ(nullptr, pointer1.pointer());
  EXPECT_EQ(0, pointer1.user_count());
  cpp::SharedPointer<int> pointer2 = cpp::MakeShared<int>(20);
  pointer1 = pointer2;
  EXPECT_EQ(pointer1.pointer(),pointer2.pointer());
  EXPECT_EQ(2, pointer1.user_count());
  EXPECT_EQ(2, pointer2.user_count());
  pointer2.Reset(new int(50));
  EXPECT_EQ(1, pointer1.user_count());
  EXPECT_EQ(1, pointer2.user_count());
}

TEST(smart_pointer, unique_pointer){
  cpp::UniquePointer<int> pointer1;
  EXPECT_EQ(nullptr, pointer1.pointer());
  cpp::UniquePointer<int> pointer2 = cpp::MakeUnique<int>(20);
  auto temp_p = pointer2.pointer();
  pointer1 = std::move(pointer2);
  EXPECT_EQ(temp_p, pointer1.pointer());
  EXPECT_EQ(nullptr, pointer2.pointer());

}