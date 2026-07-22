#include <iostream>
#include <vector>

class String {
 public:
  String() = default;

  String(std::size_t size, char character);

  String(const char* string);

  String(const String& string);

  String& operator=(const String& other);

  ~String();

  void Clear();

  void PushBack(char character);

  void PopBack();

  void Resize(std::size_t new_size);

  void Resize(std::size_t new_size, char character);

  void Reserve(std::size_t new_cap);

  void ShrinkToFit();

  void Swap(String& other);

  char& operator[](std::size_t index);

  const char& operator[](std::size_t index) const;

  char& Front();

  const char& Front() const;

  char& Back();

  const char& Back() const;

  bool Empty() const;

  std::size_t Size() const;

  std::size_t Capacity() const;

  char* Data();

  const char* Data() const;

  String& operator+=(const String& other);

  String operator*(std::size_t count) const;

  String& operator*=(std::size_t count);

  std::vector<String> Split(const String& delim = " ") const;

  String Join(const std::vector<String>& strings) const;

 private:
  size_t size_ = 0;
  size_t capacity_ = 0;
  char* data_ = nullptr;
};

bool operator<(const String& string1, const String& string2);

bool operator>(const String& string1, const String& string2);

bool operator<=(const String& string1, const String& string2);

bool operator>=(const String& string1, const String& string2);

bool operator==(const String& string1, const String& string2);

bool operator!=(const String& string1, const String& string2);

String operator+(const String& string1, const String& string2);

std::ostream& operator<<(std::ostream& os, const String& string);

std::istream& operator>>(std::istream& is, String& string);
