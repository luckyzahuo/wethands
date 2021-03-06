// Copyright (c) 2020 GGGGITFKBJG
//
// Date: 2020-05-12 12:46:37
// Description:

#ifndef SRC_THREAD_ATOMIC_H_
#define SRC_THREAD_ATOMIC_H_

#include <cstdint>
#include "src/utils/Uncopyable.h"

namespace wethands {
namespace details {

// 原子整型. 不可拷贝.
// 使用__ATOMIC_SEQ_CST内存模型.
// https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
template <typename T>
class AtomicInterger : public Uncopyable {
 public:
  AtomicInterger() : value_(0) {}
  explicit AtomicInterger(T value) : value_(value) {}
  ~AtomicInterger() = default;

  T Get() {
    return __atomic_load_n(&value_, __ATOMIC_SEQ_CST);
  }

  T GetAndSet(T newValue) {
    return __atomic_exchange_n(&value_, newValue, __ATOMIC_SEQ_CST);
  }

  T GetAndAdd(T x) {
    return __atomic_fetch_add(&value_, x, __ATOMIC_SEQ_CST);
  }

  T AddAndGet(T x) {
    return __atomic_add_fetch(&value_, x, __ATOMIC_SEQ_CST);
  }

  T IncrementAndGet() {
    return AddAndGet(1);
  }

  T DecrementAndGet() {
    return AddAndGet(-1);
  }

 private:
  volatile T value_;
};

}  // namespace details

using AtomicInt32 = details::AtomicInterger<int32_t>;
using AtomicInt64 = details::AtomicInterger<int64_t>;

}  // namespace wethands


#endif  // SRC_THREAD_ATOMIC_H_
