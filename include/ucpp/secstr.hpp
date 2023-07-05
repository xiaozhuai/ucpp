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
#ifndef UCPP_SECSTR_HPP
#define UCPP_SECSTR_HPP

#include <cstdint>
#include <functional>
#include <utility>

#include "countof.hpp"

#if !defined(SECSTR_PASSWORD)
#define SECSTR_PASSWORD "SECSTR"
#endif

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
#define SECSTR_ALWAYS_INLINE __forceinline
#elif defined(__GNUC__) || defined(__clang__)
#define SECSTR_ALWAYS_INLINE inline __attribute__((always_inline))
#else
#define SECSTR_ALWAYS_INLINE inline
#endif

#define SECSTR(str)                                    \
    []() {                                             \
        static ucpp::SecureString<sizeof(str)> s(str); \
        s.decrypt();                                   \
        return s.data;                                 \
    }()

namespace ucpp {

template <size_t N>
struct SecureString final {
    SecureString(const SecureString &) = delete;
    SecureString &operator=(const SecureString &) = delete;
    SecureString(SecureString &&) = delete;
    SecureString &operator=(SecureString &&) = delete;

    constexpr explicit SecureString(const char (&str)[N]) noexcept {
        for (size_t i = 0; i < N; i++) {
            data[i] = str[i] ^ SECSTR_PASSWORD[i % countof(SECSTR_PASSWORD)];
        }
    }

    SECSTR_ALWAYS_INLINE void decrypt() noexcept {
        for (size_t i = 0; i < N; i++) {
            data[i] ^= SECSTR_PASSWORD[i % countof(SECSTR_PASSWORD)];
        }
    }

    char data[N] = {0};
};

}  // namespace ucpp

#endif  // UCPP_SECSTR_HPP
