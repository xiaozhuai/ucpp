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
#ifndef UCPP_STRINGS_HPP
#define UCPP_STRINGS_HPP

#include <algorithm>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace ucpp {

namespace strings {

template <typename T>
static inline std::string to_string(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

template <typename T>
static inline T parse(const std::string &str) {
    std::stringstream ss(str);
    T value;
    ss >> value;
    return value;
}

static inline char char_to_lower(char c) { return static_cast<char>(::tolower(c)); }

static inline char char_to_upper(char c) { return static_cast<char>(::toupper(c)); }

static inline std::string to_lower_copy(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), char_to_lower);
    return str;
}

static inline std::string to_upper_copy(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), char_to_upper);
    return str;
}

static inline std::string &to_lower(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), char_to_lower);
    return str;
}

static inline std::string &to_upper(std::string &str) {
    std::transform(str.begin(), str.end(), str.begin(), char_to_upper);
    return str;
}

static inline std::string trim_copy(std::string str, const char *characters = " \t\r\n") {
    return str.erase(0, str.find_first_not_of(characters)).erase(str.find_last_not_of(characters) + 1);
}

static inline std::string trim_left_copy(std::string str, const char *characters = " \t\r\n") {
    return str.erase(0, str.find_first_not_of(characters));
}

static inline std::string trim_right_copy(std::string str, const char *characters = " \t\r\n") {
    return str.erase(str.find_last_not_of(characters) + 1);
}

static inline std::string &trim(std::string &str, const char *characters = " \t\r\n") {
    return str.erase(0, str.find_first_not_of(characters)).erase(str.find_last_not_of(characters) + 1);
}

static inline std::string &trim_left(std::string &str, const char *characters = " \t\r\n") {
    return str.erase(0, str.find_first_not_of(characters));
}

static inline std::string &trim_right(std::string &str, const char *characters = " \t\r\n") {
    return str.erase(str.find_last_not_of(characters) + 1);
}

static inline bool starts_with(const std::string &str, const std::string &prefix, bool ignore_case = false) {
    size_t s = str.size();
    size_t ps = prefix.size();
    if (ignore_case) {
        return s >= ps && to_lower_copy(str.substr(0, ps)) == to_lower_copy(prefix);
    } else {
        return s >= ps && str.substr(0, ps) == prefix;
    }
}

static inline bool starts_with(const std::string &str, const char prefix, bool ignore_case = false) {
    if (ignore_case) {
        return !str.empty() && (char_to_lower(str.front()) == char_to_lower(prefix));
    } else {
        return !str.empty() && (str.front() == prefix);
    }
}

static inline bool ends_with(const std::string &str, const std::string &suffix, bool ignore_case = false) {
    size_t s = str.size();
    size_t ss = suffix.size();
    if (ignore_case) {
        return s >= ss && to_lower_copy(str.substr(s - ss, s)) == to_lower_copy(suffix);
    } else {
        return s >= ss && str.substr(s - ss, s) == suffix;
    }
}

static inline bool ends_with(const std::string &str, const char suffix, bool ignore_case = false) {
    if (ignore_case) {
        return !str.empty() && (char_to_lower(str.back()) == char_to_lower(suffix));
    } else {
        return !str.empty() && (str.back() == suffix);
    }
}

static inline bool contains(const std::string &str, const std::string &substring, bool ignore_case = false) {
    if (ignore_case) {
        return to_lower_copy(str).find(to_lower_copy(substring)) != std::string::npos;
    } else {
        return str.find(substring) != std::string::npos;
    }
}

static inline bool contains(const std::string &str, const char character, bool ignore_case = false) {
    return contains(str, std::string(1, character), ignore_case);
}

static inline bool equals(const std::string &str1, const std::string &str2, bool ignore_case = false) {
    if (ignore_case) {
        return to_lower_copy(str1) == to_lower_copy(str2);
    } else {
        return str1 == str2;
    }
}

static inline std::string pad_left(const std::string &str, char c, int size) {
    return str.size() < size ? (std::string(size - str.size(), c) + str) : str;
}

static inline std::string pad_right(const std::string &str, char c, int size) {
    return str.size() < size ? (str + std::string(size - str.size(), c)) : str;
}

static inline std::string repeat(const std::string &str, int times) {
    std::string result;
    for (int i = 0; i < times; ++i) {
        result += str;
    }
    return result;
}

static inline std::string repeat(char c, int times) { return std::string(times, c); }

static inline std::string join(const std::vector<std::string> &tokens, const std::string &delim) {
    std::ostringstream result;
    for (auto it = tokens.begin(); it != tokens.end(); ++it) {
        if (it != tokens.begin()) {
            result << delim;
        }
        result << *it;
    }
    return result.str();
}

template <typename... Args>
static inline std::string join(const std::string &delim,                                          //
                               const std::string &str1, const std::string &str2, Args... args) {  //
    return join(delim, str1 + delim + str2, args...);
}

template <>
inline std::string join(const std::string &delim,                            //
                        const std::string &str1, const std::string &str2) {  //
    return str1 + delim + str2;
}

static inline std::vector<std::string> split(const std::string &str, const std::string &delim, int limit = -1) {
    if (limit == 0) return {};
    if (limit == 1) return {str};
    size_t pos_start = 0, pos_end, delim_len = delim.length();
    std::string token;
    std::vector<std::string> tokens;

    while ((pos_end = str.find(delim, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        tokens.push_back(token);
        if (limit > 0 && tokens.size() == static_cast<size_t>(limit - 1)) {
            break;
        }
    }

    tokens.push_back(str.substr(pos_start));
    return tokens;
}

static inline std::vector<std::string> split(const std::string &str, char delim, int limit = -1) {
    if (limit == 0) return {};
    if (limit == 1) return {str};
    size_t pos_start = 0, pos_end, delim_len = 1;
    std::string token;
    std::vector<std::string> tokens;

    while ((pos_end = str.find(delim, pos_start)) != std::string::npos) {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        tokens.push_back(token);
        if (limit > 0 && tokens.size() == static_cast<size_t>(limit - 1)) {
            break;
        }
    }

    tokens.push_back(str.substr(pos_start));
    return tokens;
}

static inline std::vector<std::string> regex_split(const std::string &str, const std::string &pattern, int limit = -1) {
    if (limit == 0) return {};
    if (limit == 1) return {str};

    std::regex regex(pattern);
    std::vector<std::string> tokens;
    std::sregex_token_iterator iter(str.begin(), str.end(), regex, -1);
    std::sregex_token_iterator end;

    while (iter != end) {
        tokens.emplace_back(*iter);
        ++iter;
        if (limit > 0 && tokens.size() == static_cast<size_t>(limit - 1)) {
            break;
        }
    }

    if (iter != end) {
        tokens.emplace_back(iter->first, str.end());
    }

    return tokens;
}

static inline std::string replace_copy(std::string str, const std::string &target, const std::string &replacement) {
    size_t index = str.find(target, 0);
    size_t target_length = target.length();
    size_t replace_length = replacement.length();

    while (std::string::npos != index) {
        str.replace(index, target_length, replacement);
        index = str.find(target, index - target_length + replace_length + 1);
    }
    return str;
}

static inline std::string &replace(std::string &str, const std::string &target, const std::string &replacement) {
    size_t index = str.find(target, 0);
    size_t target_length = target.length();
    size_t replace_length = replacement.length();

    while (std::string::npos != index) {
        str.replace(index, target_length, replacement);
        index = str.find(target, index - target_length + replace_length + 1);
    }
    return str;
}

static inline std::string replace_first_copy(std::string str, const std::string &target,
                                             const std::string &replacement) {
    const size_t start_pos = str.find(target);
    if (start_pos == std::string::npos) {
        return str;
    }

    str.replace(start_pos, target.length(), replacement);
    return str;
}

static inline std::string replace_last_copy(std::string str, const std::string &target,
                                            const std::string &replacement) {
    size_t start_pos = str.rfind(target);
    if (start_pos == std::string::npos) {
        return str;
    }

    str.replace(start_pos, target.length(), replacement);
    return str;
}

static inline std::string &replace_first(std::string &str, const std::string &target, const std::string &replacement) {
    const size_t start_pos = str.find(target);
    if (start_pos == std::string::npos) {
        return str;
    }

    str.replace(start_pos, target.length(), replacement);
    return str;
}

static inline std::string &replace_last(std::string &str, const std::string &target, const std::string &replacement) {
    size_t start_pos = str.rfind(target);
    if (start_pos == std::string::npos) {
        return str;
    }

    str.replace(start_pos, target.length(), replacement);
    return str;
}

}  // namespace strings

}  // namespace ucpp

#endif  // UCPP_STRINGS_HPP
