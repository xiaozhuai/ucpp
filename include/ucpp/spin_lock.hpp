/**
 * MIT License
 *
 * Copyright (c) 2023 xiaozhuai
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#pragma once
#ifndef UCPP_SPIN_LOCK_HPP
#define UCPP_SPIN_LOCK_HPP

#include <atomic>
#include <thread>

#if defined(__x86_64__) || defined(__i386__)
#include <emmintrin.h>
#elif defined(__ARM_ARCH)
#if defined(_MSC_VER)
#include <arm64_neon.h>
#else
#include <arm_acle.h>
#endif
#endif

namespace ucpp {

class SpinLock final {
public:
    SpinLock() = default;

    SpinLock(const SpinLock &) = delete;
    SpinLock &operator=(const SpinLock &) = delete;
    SpinLock(SpinLock &&) = delete;
    SpinLock &operator=(SpinLock &&) = delete;

    inline void lock() noexcept {
        for (;;) {
            // Optimistically assume the lock is free on the first try
            if (!lock_.exchange(true, std::memory_order_acquire)) {
                return;
            }
            // Wait for lock to be released without generating cache misses
            while (lock_.load(std::memory_order_relaxed)) {
                // Issue X86 PAUSE or ARM YIELD instruction to reduce contention between hyper-threads
#if defined(__x86_64__) || defined(__i386__)
                _mm_pause();
#elif defined(__ARM_ARCH)
                __yield();
#elif defined(__powerpc__) || defined(__ppc__) || defined(__PPC__)
                asm volatile("or 27,27,27" : : : "memory");
#endif
            }
        }
    }

    inline bool try_lock() noexcept {
        // First do a relaxed load to check if lock is free in order to prevent
        // unnecessary cache misses if someone does while(!try_lock())
        return !lock_.load(std::memory_order_relaxed) && !lock_.exchange(true, std::memory_order_acquire);
    }

    inline void unlock() noexcept { lock_.store(false, std::memory_order_release); }

private:
    std::atomic<bool> lock_ = {false};
};

}  // namespace ucpp

#endif  // UCPP_SPIN_LOCK_HPP
