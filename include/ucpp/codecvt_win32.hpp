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
#ifndef UCPP_CODECVT_WIN32_H
#define UCPP_CODECVT_WIN32_H

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>

#include <optional>
#include <string>
#include <string_view>

namespace ucpp {

inline std::wstring utf8_to_utf16(std::string_view utf8_str) {
    if (utf8_str.empty()) {
        return {};
    }
    int utf8_len = static_cast<int>(utf8_str.length());
    int utf16_len = MultiByteToWideChar(CP_UTF8, 0, utf8_str.data(), utf8_len, nullptr, 0);
    if (utf16_len == 0) {
        return {};
    }
    std::wstring utf16_str(utf16_len, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, utf8_str.data(), utf8_len, utf16_str.data(), utf16_len);
    return utf16_str;
}

inline std::string utf16_to_ansi(std::wstring_view utf16_str) {
    if (utf16_str.empty()) {
        return {};
    }
    int utf16_len = static_cast<int>(utf16_str.length());
    int ansi_len = WideCharToMultiByte(CP_ACP, 0, utf16_str.data(), utf16_len, nullptr, 0, nullptr, nullptr);
    if (ansi_len == 0) {
        return {};
    }
    std::string ansi_str(ansi_len, '\0');
    WideCharToMultiByte(CP_ACP, 0, utf16_str.data(), utf16_len, ansi_str.data(), ansi_len, nullptr, nullptr);
    return ansi_str;
}

inline std::string utf16_to_utf8(std::wstring_view utf16_str) {
    if (utf16_str.empty()) {
        return "";
    }
    int utf16_len = static_cast<int>(utf16_str.length());
    int utf8_len = WideCharToMultiByte(CP_UTF8, 0, utf16_str.data(), utf16_len, nullptr, 0, nullptr, nullptr);
    if (utf8_len == 0) {
        return {};
    }
    std::string utf8_str(utf8_len, '\0');
    WideCharToMultiByte(CP_UTF8, 0, utf16_str.data(), utf16_len, utf8_str.data(), utf8_len, nullptr, nullptr);
    return utf8_str;
}

inline std::string utf8_to_ansi(std::string_view utf8_str) { return utf16_to_ansi(utf8_to_utf16(utf8_str)); }

}  // namespace ucpp

#endif  // UCPP_CODECVT_WIN32_H
