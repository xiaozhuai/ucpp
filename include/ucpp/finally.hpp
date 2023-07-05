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
 *          char *data = new char[1024];
 *          if (some_condition1) {
 *              delete[] data;
 *              return false;
 *          }
 *
 *          delete[] data;
 *          return true;
 *      }
 *
 * ------------------------------------------------------
 *
 * - Usage:
 *      bool demo() {
 *          char *data = new char[1024];
 *          finally { delete[] data; };
 *          if (some_condition1) {
 *              return false;
 *          }
 *          return true;
 *      }
 *
 * - Or:
 *      bool demo() {
 *          char *data = new char[1024];
 *          finally2([&data](){ delete[] data; });
 *          if (some_condition1) {
 *              return false;
 *          }
 *          return true;
 *      }
 */

#pragma once
#ifndef UCPP_FINALLY_HPP
#define UCPP_FINALLY_HPP

#include <functional>
#include <utility>

namespace ucpp {

template <class F>
class FinalAction {
public:
    FinalAction(F f) noexcept : f_(std::move(f)), invoke_(true) {}

    FinalAction(FinalAction &&other) noexcept : f_(std::move(other.f_)), invoke_(other.invoke_) {
        other.invoke_ = false;
    }

    FinalAction(const FinalAction &) = delete;

    FinalAction &operator=(const FinalAction &) = delete;

    ~FinalAction() noexcept {
        if (invoke_) f_();
    }

private:
    F f_;
    bool invoke_;
};

template <class F>
inline FinalAction<F> final(const F &f) noexcept {
    return FinalAction<F>(f);
}

template <class F>
inline FinalAction<F> final(F &&f) noexcept {
    return FinalAction<F>(std::forward<F>(f));
}

}  // namespace ucpp

#define _concat1(a, b)  a##b
#define _concat2(a, b)  _concat1(a, b)
#define _finally_object _concat2(_finally_object_, __COUNTER__)
#define finally         ucpp::FinalAction _finally_object = [&]()
#define finally2(func)  ucpp::FinalAction _finally_object = ucpp::final(func)

#endif  // UCPP_FINALLY_HPP
