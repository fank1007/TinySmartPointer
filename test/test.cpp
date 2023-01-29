#include <gtest/gtest.h>
#include <shared_ptr/shared_ptr.h>
#include <unique_ptr/unique_ptr.h>

#include <utility>

TEST(smart_pointer, shared_pointer) {
  cpp::SharedPointer<int> pointer1;
  ASSERT_TRUE(pointer1.Get() == nullptr);
  ASSERT_TRUE(pointer1.user_count() == 0);
  pointer1.Reset(new int(20));
  EXPECT_EQ(20, *pointer1);
  EXPECT_EQ(1, pointer1.user_count());
  pointer1.Reset();
  ASSERT_TRUE(pointer1.Get() == nullptr);
  ASSERT_TRUE(pointer1.user_count() == 0);
  cpp::SharedPointer<int> pointer2(new int(30));
  pointer1 = pointer2;
  ASSERT_TRUE(pointer1.Get() == pointer2.Get());
  ASSERT_TRUE(pointer1.user_count() == pointer2.user_count());
  cpp::SharedPointer<int> pointer3(new int(40));
  pointer1 = pointer3;
  EXPECT_EQ(1, pointer2.user_count());
  ASSERT_TRUE(pointer1.Get() == pointer3.Get());
  ASSERT_TRUE(pointer1.user_count() == pointer3.user_count());
  cpp::SharedPointer<int> pointer4(new int(50));
  pointer1 = std::move(pointer4);
  ASSERT_TRUE(pointer4.Get() == nullptr);
  ASSERT_TRUE(pointer4.user_count() == 0);
  ASSERT_TRUE(pointer3.user_count() == 1);
}

TEST(smart_pointer, unique_pointer) {
  cpp::UniquePointer<int> pointer1;
  EXPECT_EQ(nullptr, pointer1.Get());
  pointer1.Reset(new int(20));
  EXPECT_EQ(20, *pointer1);
  pointer1.Reset();
  EXPECT_EQ(nullptr, pointer1.Get());
  cpp::UniquePointer<int> pointer2(new int(20));
  auto temp = pointer2.Get();
  pointer1 = std::move(pointer2);
  EXPECT_EQ(pointer1.Get(), temp);
  ASSERT_TRUE(pointer2.Get() == nullptr);
}