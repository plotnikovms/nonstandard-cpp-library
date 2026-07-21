#include <gtest/gtest.h>

#include <cstdint>

#include <memory/new.hpp>


void FirstHandler() {}

void SecondHandler() {}


TEST(NewHandlerTest, InitiallyNull) {
  EXPECT_EQ(nstd::get_new_handler(), nullptr);
}

TEST(NewHandlerTest, SetAndGetHandler) {
  nstd::new_handler old_handler =
      nstd::set_new_handler(FirstHandler);

  EXPECT_EQ(old_handler, nullptr);
  EXPECT_EQ(nstd::get_new_handler(), FirstHandler);

  old_handler = nstd::set_new_handler(SecondHandler);

  EXPECT_EQ(old_handler, FirstHandler);
  EXPECT_EQ(nstd::get_new_handler(), SecondHandler);

  nstd::set_new_handler(nullptr);
}

TEST(NewTest, AllocatesMemory) {
  void* memory = ::operator new(128);

  ASSERT_NE(memory, nullptr);

  ::operator delete(memory);
}

TEST(NewTest, AllocatesZeroBytes) {
  void* memory = ::operator new(0);

  ASSERT_NE(memory, nullptr);

  ::operator delete(memory);
}

TEST(NewArrayTest, AllocatesMemory) {
  void* memory = ::operator new[](128);

  ASSERT_NE(memory, nullptr);

  ::operator delete[](memory);
}

TEST(DeleteTest, SizedDelete) {
  void* memory = ::operator new(128);

  ASSERT_NE(memory, nullptr);

  ::operator delete(memory, 128);
}

TEST(DeleteArrayTest, SizedDelete) {
  void* memory = ::operator new[](128);

  ASSERT_NE(memory, nullptr);

  ::operator delete[](memory, 128);
}

TEST(AlignedNewTest, ReturnsAlignedMemory) {
  constexpr std::size_t alignment = 64;

  void* memory = ::operator new(
      100,
      nstd::align_val_t{alignment}
  );

  ASSERT_NE(memory, nullptr);

  const auto address =
      reinterpret_cast<std::uintptr_t>(memory);

  EXPECT_EQ(address % alignment, 0);

  ::operator delete(
      memory,
      nstd::align_val_t{alignment}
  );
}

TEST(AlignedNewTest, AllocatesZeroBytes) {
  constexpr std::size_t alignment = 64;

  void* memory = ::operator new(
      0,
      nstd::align_val_t{alignment}
  );

  ASSERT_NE(memory, nullptr);

  const auto address =
      reinterpret_cast<std::uintptr_t>(memory);

  EXPECT_EQ(address % alignment, 0);

  ::operator delete(
      memory,
      nstd::align_val_t{alignment}
  );
}

TEST(AlignedNewTest, RejectsZeroAlignment) {
  EXPECT_THROW(
      ::operator new(100, nstd::align_val_t{0}),
      std::bad_alloc
  );
}

TEST(AlignedNewTest, RejectsNonPowerOfTwoAlignment) {
  EXPECT_THROW(
      ::operator new(100, nstd::align_val_t{24}),
      std::bad_alloc
  );
}

TEST(AlignedNewArrayTest, ReturnsAlignedMemory) {
  constexpr std::size_t alignment = 64;

  void* memory = ::operator new[](
      100,
      nstd::align_val_t{alignment}
  );

  ASSERT_NE(memory, nullptr);

  const auto address =
      reinterpret_cast<std::uintptr_t>(memory);

  EXPECT_EQ(address % alignment, 0);

  ::operator delete[](
      memory,
      nstd::align_val_t{alignment}
  );
}

TEST(NothrowNewTest, AllocatesMemory) {
  void* memory = ::operator new(128, nstd::nothrow);

  ASSERT_NE(memory, nullptr);

  ::operator delete(memory, nstd::nothrow);
}

TEST(NothrowNewArrayTest, AllocatesMemory) {
  void* memory = ::operator new[](128, nstd::nothrow);

  ASSERT_NE(memory, nullptr);

  ::operator delete[](memory, nstd::nothrow);
}

TEST(NothrowNewTest, ConstructsObject) {
  int* value = new (nstd::nothrow) int{42};

  ASSERT_NE(value, nullptr);
  EXPECT_EQ(*value, 42);

  delete value;
}

TEST(AlignedNothrowNewTest, ReturnsNullForInvalidAlignment) {
  void* memory = ::operator new(
      100,
      nstd::align_val_t{24},
      nstd::nothrow
  );

  EXPECT_EQ(memory, nullptr);
}

TEST(AlignedNothrowNewTest, ReturnsAlignedMemory) {
  constexpr std::size_t alignment = 64;

  void* memory = ::operator new(
      100,
      nstd::align_val_t{alignment},
      nstd::nothrow
  );

  ASSERT_NE(memory, nullptr);

  const auto address =
      reinterpret_cast<std::uintptr_t>(memory);

  EXPECT_EQ(address % alignment, 0);

  ::operator delete(
      memory,
      nstd::align_val_t{alignment},
      nstd::nothrow
  );
}
