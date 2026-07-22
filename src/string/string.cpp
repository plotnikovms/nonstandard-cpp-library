#include <string/string.hpp>

#include <cstring>
#include <iostream>
#include <vector>

String::String(std::size_t size, char character) : size_(size), capacity_(size), data_(new char[capacity_ + 1]) {
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] = character;
  }
  data_[size_] = '\0';
}

String::String(const char* string) : size_(strlen(string)), capacity_(size_), data_(new char[capacity_ + 1]) {
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] = string[i];
  }
  data_[size_] = '\0';
}

String::String(const String& string)
    : size_(string.size_),
      capacity_(string.capacity_),
      data_(new char[capacity_ + 1]) {
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] = string[i];
  }
  data_[size_] = '\0';
}

String& String::operator=(const String& other) {
  if (&other == this) {
    return *this;
  }
  size_ = other.size_;
  capacity_ = other.capacity_;
  delete[] data_;
  data_ = new char[capacity_ + 1];
  for (std::size_t i = 0; i < size_; ++i) {
    data_[i] = other[i];
  }
  data_[size_] = '\0';
  return *this;
}

String::~String() { delete[] data_; }

void String::Clear() {
  size_ = 0;
  if (capacity_ != 0) {
    data_[size_] = '\0';
  }
}

void String::PushBack(char character) {
  if (capacity_ == 0) {
    Reserve(1);
  } else if (size_ == capacity_) {
    Reserve(capacity_ * 2);
  }
  data_[size_] = character;
  ++size_;
  data_[size_] = '\0';
}

void String::PopBack() {
  if (!Empty()) {
    --size_;
    data_[size_] = '\0';
  }
}

void String::Resize(size_t new_size) {
  Reserve(new_size);
  size_ = new_size;
  data_[size_] = '\0';
}

void String::Resize(size_t new_size, char character) {
  Reserve(new_size);
  for (std::size_t i = size_; i < new_size; ++i) {
    data_[i] = character;
  }
  size_ = new_size;
  data_[size_] = '\0';
}

void String::Reserve(std::size_t new_capacity) {
  if (new_capacity > capacity_) {
    capacity_ = new_capacity;
    char* new_data = new char[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i) {
        new_data[i] = data_[i];
    }
    delete[] data_;
    data_ = new_data;
    data_[size_] = '\0';
  }
}

void String::ShrinkToFit() {
  capacity_ = size_;
  char* new_data = new char[capacity_ + 1];
  for (size_t i = 0; i < size_; ++i) {
    new_data[i] = data_[i];
  }
  delete[] data_;
  data_ = new_data;
  data_[size_] = '\0';
}

void String::Swap(String& other) {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}

char& String::operator[](std::size_t index) { return data_[index]; }

const char& String::operator[](std::size_t index) const { return data_[index]; }

char& String::Front() { return data_[0]; }

const char& String::Front() const { return data_[0]; }

char& String::Back() { return data_[size_ - 1]; }

const char& String::Back() const { return data_[size_ - 1]; }

bool String::Empty() const { return size_ == 0; }

size_t String::Size() const { return size_; }

size_t String::Capacity() const { return capacity_; }

char* String::Data() { return data_; }

const char* String::Data() const { return data_; }

String& String::operator+=(const String& other) {
  Reserve(size_ + other.size_);
  for (size_t i = 0; i < other.size_; ++i) {
    PushBack(other[i]);
  }
  return *this;
}

String& String::operator*=(std::size_t count) {
  if (count == 0) {
    Clear();
    return *this;
  }
  Reserve(size_ * count);
  std::size_t tmp_size = size_;
  for (std::size_t i = 0; i < count - 1; ++i) {
    for (std::size_t j = 0; j < tmp_size; ++j) {
      PushBack(data_[j]);
    }
  }
  return *this;
}

String String::operator*(std::size_t count) const {
  String new_string = *this;
  new_string *= count;
  return new_string;
}

std::vector<String> String::Split(const String& delim) const {
  String current;
  std::vector<String> splited;
  std::size_t index_1 = 0;
  while (index_1 < size_) {
    String tmp;
    std::size_t index_2 = 0;
    while (index_1 < size_ && index_2 < delim.size_ && data_[index_1] == delim[index_2]) {
      tmp.PushBack(data_[index_1]);
      ++index_1;
      ++index_2;
    }

    if (index_2 == delim.size_) {
      splited.push_back(current);
      current.Clear();
      --index_1;
    } else if (index_2 != 0) {
      current += tmp;
      --index_1;
    } else {
      current.PushBack(data_[index_1]);
    }
    ++index_1;
  }

  splited.push_back(current);

  return splited;
}

String String::Join(const std::vector<String>& strings) const {
  String string = "";
  for (size_t i = 0; i < strings.size(); ++i) {
    string += strings[i];
    if (i != strings.size() - 1) {
      string += *this;
    }
  }
  return string;
}

bool operator<(const String& string1, const String& string2) {
  size_t i = 0;
  while (i < string1.Size() && i < string2.Size() && string1[i] == string2[i]) {
    ++i;
  }
  if (i == string2.Size()) {
    return false;
  }
  if (i == string1.Size()) {
    return true;
  }
  return string1[i] < string2[i];
}

bool operator>(const String& string1, const String& string2) {
  return string2 < string1;
}

bool operator<=(const String& string1, const String& string2) {
  return !(string1 > string2);
}

bool operator>=(const String& string1, const String& string2) {
  return !(string1 < string2);
}

bool operator==(const String& string1, const String& string2) {
  if (string1.Size() != string2.Size()) {
    return false;
  }
  for (size_t i = 0; i < string1.Size(); ++i) {
    if (string1[i] != string2[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& string1, const String& string2) {
  return !(string1 == string2);
}

String operator+(const String& string1, const String& string2) {
  String new_string = string1;
  new_string += string2;
  return new_string;
}

std::ostream& operator<<(std::ostream& os, const String& string) {
  os << string.Data();
  return os;
}

std::istream& operator>>(std::istream& is, String& string) {
  char chr;
  while (is.get(chr) && (std::isspace(chr) != 0)) {
  }
  string.PushBack(chr);
  while (is.get(chr) && (std::isspace(chr) == 0) && (chr != '\n')) {
    string.PushBack(chr);
  }
  return is;
}
