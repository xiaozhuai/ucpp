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
 *
 * - Original Code:
 *      bool demon() {
 *          {
 *               std::lock_guard<std::mutex> lock(mutex);
 *               ...
 *          }
 *      }
 *
 * ------------------------------------------------------
 *
 * - Usage:
 *      bool demo() {
 *          synchronized(mutex) {
 *              ...
 *          }
 *      }
 */

#pragma once
#ifndef UCPP_SYNCHRONIZED_HPP
#define UCPP_SYNCHRONIZED_HPP

#include <mutex>
#include <thread>

#define synchronized(L) for (auto _lock##L = ucpp::create_lock_guard(L); _lock##L.locked(); _lock##L.unlock())

namespace ucpp {

template <class T>
class LockGuard {
public:
    explicit LockGuard(T &lock) : lock_(lock), locked_(true) { lock_.lock(); }

    LockGuard(const LockGuard &) = delete;

    LockGuard &operator=(const LockGuard &) = delete;

    ~LockGuard() { lock_.unlock(); }

    inline bool locked() const { return locked_; }

    inline void unlock() { locked_ = false; }

private:
    T &lock_;
    bool locked_;
};

template <class T>
inline LockGuard<T> create_lock_guard(T &lock) {
    return LockGuard<T>(lock);
}

}  // namespace ucpp

#endif  // UCPP_SYNCHRONIZED_HPP
