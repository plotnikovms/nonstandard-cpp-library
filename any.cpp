#include <any>

class any {
 public:
 template <typename T>
  any(const T& value) : ptr(new object(value)) {}

  any(const any& other) : ptr(other.ptr->get_copy()) {}

  template <typename T>
  any& operator=(const T& value) {
    delete ptr;
    ptr = new object(value);
    return *this;
  }

  any& operator=(const any& other) {
    delete ptr;
    ptr = other.ptr->get_copy();
    return *this;
  }

  ~any() {
    delete ptr;
  }

 private:
  struct helper {
    virtual helper* get_copy() const = 0;
    virtual ~helper() = default;
  };

  template <typename T>
  struct object : helper {
    object(const T& value) : value(value) {}
    
    helper* get_copy() const override {
      return &object(value);
    }

    T value;
  };

  helper* ptr;

  template <typename T>
  friend T any_cast(const any& any_object);
};


template <typename T>
T& any_cast(const any& any_object) {
  if (!dynamic_cast<any::object<T>*>(any_object.ptr)) {
    throw std::bad_any_cast();
  }
  return (dynamic_cast<any::object<T>*>(any_object.ptr))->value;
}
