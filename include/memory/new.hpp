#pragma once

#include <cstddef>

namespace nstd {

typedef void (*new_handler)();

new_handler set_new_handler(new_handler handler) noexcept;

new_handler get_new_handler() noexcept;

struct nothrow_t {
  explicit nothrow_t() noexcept = default;
};

extern const nothrow_t nothrow;

enum class align_val_t : std::size_t {};

}  // namespace nstd

void* operator new(std::size_t count);

void* operator new[](std::size_t count);

void operator delete(void* memory) noexcept;

void operator delete[](void* memory) noexcept;

void operator delete(void* memory, std::size_t) noexcept;

void operator delete[](void* memory, std::size_t) noexcept;

void* operator new(std::size_t count, nstd::align_val_t al);

void* operator new[](std::size_t count, nstd::align_val_t alignment);

void operator delete(void* memory, nstd::align_val_t) noexcept;

void operator delete[](void* memory, nstd::align_val_t) noexcept;

void operator delete(void* memory, std::size_t, nstd::align_val_t) noexcept;

void operator delete[](void* memory, std::size_t, nstd::align_val_t) noexcept;

void* operator new(std::size_t count, const nstd::nothrow_t&) noexcept;

void* operator new[](std::size_t count, const nstd::nothrow_t&) noexcept;

void operator delete(void* memory, const nstd::nothrow_t&) noexcept;

void operator delete[](void* memory, const nstd::nothrow_t&) noexcept;

void* operator new(std::size_t count, nstd::align_val_t alignment,
                   const nstd::nothrow_t&) noexcept;

void* operator new[](std::size_t count, nstd::align_val_t alignment,
                     const nstd::nothrow_t&) noexcept;

void operator delete(void* memory, nstd::align_val_t alignment,
                     const nstd::nothrow_t&) noexcept;

void operator delete[](void* memory, nstd::align_val_t alignment,
                       const nstd::nothrow_t&) noexcept;
