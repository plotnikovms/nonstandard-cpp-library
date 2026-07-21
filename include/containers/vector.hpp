#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class Vector {
 public:
  using value_type = T;
  using allocator_type = Allocator;
  using size_type = size_t;
  using difference_type = size_t;
  using reference = T&;
  using const_reference = const T&;
  using pointer = T*;
  using const_pointer = const T*;

  Vector();
  explicit Vector(const Allocator& allocator);
  explicit Vector(size_t count, const Allocator& allocator = Allocator());
  Vector(size_t count, const T& value,
         const Allocator& allocator = Allocator());
  Vector(const Vector& other);
  Vector(Vector&& other);
  Vector(std::initializer_list<T> init,
         const Allocator& allocator = Allocator());

  ~Vector();

  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);

  reference at(size_t index);
  const_reference at(size_t index) const;
  reference operator[](size_t index);
  const_reference operator[](size_t index) const;

  bool empty() const;
  size_type size() const;
  size_type capacity() const;

  void reserve();

  void push_back(const T& value);
  void push_back(T&& value);

  template <typename... Args>
  void emplace_back(Args&&... args);

  void pop_back();

 private:
  using allocator_traits = std::allocator_traits<allocator_type>;

  size_t size_ = 0;
  size_t capacity_ = 0;
  [[no_unique_address]] allocator_type allocator_;
  T* arr_ = nullptr;
};


template <typename T, typename Allocator>
Vector<T, Allocator>::Vector() : Vector(Allocator()) {}


template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Allocator& allocator)
    : allocator_(allocator) {}


template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const Allocator& allocator)
    : size_(count),
      capacity_(count),
      allocator_(allocator),
      arr_(allocator_traits::allocate(allocator_, count)) {
  size_t index = 0;
  try {
    for (; index < size_; ++index) {
      allocator_traits::construct(allocator_, arr_ + index);
    }
  } catch (...) {
    for (size_t i = 0; i < index; ++i) {
      allocator_traits::destroy(allocator_, arr_ + index);
    }
    allocator_traits::deallocate(allocator_, arr_, capacity_);
  }
}


template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(size_t count, const T& value,
                             const Allocator& allocator)
    : size_(count),
      capacity_(count),
      allocator_(allocator),
      arr_(allocator_traits::allocate(allocator_, count)) {
  size_t index = 0;
  try {
    for (; index < size_; ++index) {
      allocator_traits::construct(allocator_, arr_ + index, value);
    }
  } catch (...) {
    for (size_t i = 0; i < index; ++i) {
      allocator_traits::destroy(allocator_, arr_ + index);
    }
    allocator_traits::deallocate(allocator_, arr_, capacity_);
  }
}


template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(const Vector& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      allocator_(allocator_traits::select_on_container_copy_construction(other.allocator_)),
      arr_(allocator_traits::allocate(allocator_, capacity_)) {
  size_t index = 0;
  try {
    for (; index < size_; ++index) {
      allocator_traits::construct(allocator_, arr_ + index, other[index]);
    }
  } catch (...) {
    for (size_t i = 0; i < index; ++i) {
      allocator_traits::destroy(allocator_, arr_ + index);
    }
    allocator_traits::deallocate(allocator_, arr_, capacity_);
  }
}


template <typename T, typename Allocator>
Vector<T, Allocator>::Vector(Vector&& other)
    : size_(other.size_),
      capacity_(other.capacity_),
      allocator_(other.allocator_),
      arr_(other.arr_) {
  other.size_ = 0;
  other.capacity_ = 0;
  other.allocator_ = decltype(other)::allocator_type();
  other.arr_ = nullptr;
}

template <typename T, typename Allocator>
Vector<T, Allocator>::~Vector() {
  for (size_t i = 0; i < size_; ++i) {
    allocator_traits::destroy(allocator_, arr_ + i);
  }
  allocator_traits::deallocate(allocator_, arr_, capacity_);
}


template <typename T, typename Allocator>
typename Vector<T, Allocator>::reference
Vector<T, Allocator>::operator[](size_t index) {
  return arr_[index];
}


template <typename T, typename Allocator>
typename Vector<T, Allocator>::const_reference
Vector<T, Allocator>::operator[](size_t index) const {
  return arr_[index];
}


template <typename T, typename Allocator>
bool Vector<T, Allocator>::empty() const {
  return size_ == 0;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::size() const {
  return size_;
}

template <typename T, typename Allocator>
typename Vector<T, Allocator>::size_type
Vector<T, Allocator>::capacity() const {
  return capacity_;
}
