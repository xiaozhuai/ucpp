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

namespace ucpp {

class SpinLock {
public:
    SpinLock() { lock_variable_.store(false); }

    SpinLock(const SpinLock &) = delete;

    SpinLock &operator=(const SpinLock &) = delete;

    ~SpinLock() { lock_variable_.store(false); }

    void lock() {
        bool expected = false;
        bool desired = true;
        while (!lock_variable_.compare_exchange_strong(expected, desired)) {
            expected = false;
        }
        owner_.store(std::this_thread::get_id());
    }

    bool unlock() {
        if (lock_variable_.load()) {
            if (owner_.load() == std::this_thread::get_id()) {
                lock_variable_.store(false);
                return true;
            }
        }
        return false;
    }

private:
    std::atomic<bool> lock_variable_;
    std::atomic<std::thread::id> owner_;
};

}  // namespace ucpp

#endif  // UCPP_SPIN_LOCK_HPP
