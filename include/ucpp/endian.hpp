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
#ifndef UCPP_ENDIAN_HPP
#define UCPP_ENDIAN_HPP

#include <cstdint>

namespace ucpp {

namespace endian {

namespace impl {
static constexpr std::uint32_t LITTLE_{0x41424344u};
static constexpr std::uint32_t BIG_{0x44434241u};
static constexpr std::uint32_t NATIVE_{'ABCD'};
}  // namespace impl

static constexpr bool IS_LITTLE = impl::NATIVE_ == impl::LITTLE_;
static constexpr bool IS_BIG = impl::NATIVE_ == impl::BIG_;
static_assert(IS_LITTLE || IS_BIG, "Cannot determine endian");

}  // namespace endian

}  // namespace ucpp

#endif  // UCPP_ENDIAN_HPP
