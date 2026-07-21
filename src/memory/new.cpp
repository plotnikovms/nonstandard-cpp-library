#include <memory/new.hpp>

#include <atomic>
#include <cerrno>
#include <cstdlib>
#include <new>

namespace nstd {

static std::atomic<new_handler> current_new_handler{nullptr};

new_handler set_new_handler(new_handler handler) noexcept {
  return current_new_handler.exchange(handler);
}

new_handler get_new_handler() noexcept { return current_new_handler.load(); }

const nothrow_t nothrow{};

}  // namespace nstd

__attribute__((weak))
void* operator new(std::size_t count) {
  if (count == 0) {
    count = 1;
  }

  void* ptr;
  while ((ptr = malloc(count)) == nullptr) {
    nstd::new_handler handler = nstd::get_new_handler();

    if (handler) {
      handler();
    } else {
      throw std::bad_alloc{};
    }
  }

  return ptr;
}

__attribute__((weak))
void* operator new[](std::size_t count) {
  return operator new(count);
}

__attribute__((weak))
void operator delete(void* memory) noexcept {
  std::free(memory);
}

__attribute__((weak))
void operator delete[](void* memory) noexcept {
  std::free(memory);
}

__attribute__((weak))
void operator delete(void* memory, std::size_t) noexcept {
  std::free(memory);
}

__attribute__((weak))
void operator delete[](void* memory, std::size_t) noexcept {
  std::free(memory);
}

__attribute__((weak))
void* operator new(std::size_t count, nstd::align_val_t al) {
  if (count == 0) {
    count = 1;
  }

  std::size_t alignment = static_cast<std::size_t>(al);

  if (alignment == 0 || (alignment & (alignment - 1)) != 0) {
    throw std::bad_alloc{};
  }

  if (alignment < sizeof(void*)) {
    alignment = sizeof(void*);
  }

  void* ptr;
  while (true) {
    const int result = posix_memalign(&ptr, alignment, count);

    if (result == 0) {
      return ptr;
    }

    if (result != ENOMEM) {
      throw std::bad_alloc{};
    }

    nstd::new_handler handler = nstd::get_new_handler();

    if (handler) {
      handler();
    } else {
      throw std::bad_alloc{};
    }
  }
}

__attribute__((weak))
void* operator new[](std::size_t count, nstd::align_val_t alignment) {
  return operator new(count, alignment);
}

__attribute__((weak))
void operator delete(void* memory, nstd::align_val_t) noexcept {
  std::free(memory);
}

__attribute__((weak))
void operator delete[](void* memory, nstd::align_val_t) noexcept {
  std::free(memory);
}

__attribute__((weak))
void operator delete(void* memory, std::size_t, nstd::align_val_t) noexcept {
  std::free(memory);
}

__attribute__((weak))
void operator delete[](void* memory, std::size_t,
                       nstd::align_val_t) noexcept {
  std::free(memory);
}

__attribute__((weak))
void* operator new(std::size_t count, const nstd::nothrow_t&) noexcept {
  try {
    return operator new(count);
  } catch (...) {
    return nullptr;
  }
}

__attribute__((weak))
void* operator new[](std::size_t count, const nstd::nothrow_t&) noexcept {
  try {
    return operator new[](count);
  } catch (...) {
    return nullptr;
  }
}

__attribute__((weak))
void operator delete(void* memory, const nstd::nothrow_t&) noexcept {
  operator delete(memory);
}

__attribute__((weak))
void operator delete[](void* memory, const nstd::nothrow_t&) noexcept {
  operator delete[](memory);
}

__attribute__((weak))
void* operator new(std::size_t count, nstd::align_val_t alignment,
                   const nstd::nothrow_t&) noexcept {
  try {
    return operator new(count, alignment);
  } catch (...) {
    return nullptr;
  }
}

__attribute__((weak))
void* operator new[](std::size_t count, nstd::align_val_t alignment,
                     const nstd::nothrow_t&) noexcept {
  try {
    return operator new[](count, alignment);
  } catch (...) {
    return nullptr;
  }
}

__attribute__((weak))
void operator delete(void* memory, nstd::align_val_t alignment,
                     const nstd::nothrow_t&) noexcept {
  operator delete(memory, alignment);
}

__attribute__((weak))
void operator delete[](void* memory, nstd::align_val_t alignment,
                       const nstd::nothrow_t&) noexcept {
  operator delete[](memory, alignment);
}
