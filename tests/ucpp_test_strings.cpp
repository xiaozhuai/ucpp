//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>

#include "ucpp/strings.hpp"

bool string_list_equals(const std::vector<std::string> &list1, const std::vector<std::string> &list2) {
    if (list1.size() != list2.size()) {
        return false;
    }
    for (size_t i = 0; i < list1.size(); ++i) {
        if (list1[i] != list2[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    assert(ucpp::strings::to_string(1) == "1");
    assert(ucpp::strings::to_string('c') == "c");

    assert(ucpp::strings::parse<char>("c") == 'c');
    assert(ucpp::strings::parse<char>("99") == '9');
    assert(ucpp::strings::parse<int>("100") == 100);
    assert(ucpp::strings::parse<short>("8000") == 8000);

    assert(ucpp::strings::to_lower_copy("a23423SDFSsdf") == "a23423sdfssdf");
    {
        std::string s = "a23423SDFSsdf";
        ucpp::strings::to_lower(s);
        assert(s == "a23423sdfssdf");
    }

    assert(ucpp::strings::to_upper_copy("a23423SDFSsdf") == "A23423SDFSSDF");
    {
        std::string s = "a23423SDFSsdf";
        ucpp::strings::to_upper(s);
        assert(s == "A23423SDFSSDF");
    }

    assert(ucpp::strings::trim_copy("   \t\t\r\n  123  \t\r\n\r\t  ") == "123");
    {
        std::string s = "   \t\t\r\n  123  \t\r\n\r\t  ";
        ucpp::strings::trim(s);
        assert(s == "123");
    }

    assert(ucpp::strings::trim_left_copy("   \t\t\r\n  123  \t\r\n\r\t  ") == "123  \t\r\n\r\t  ");
    {
        std::string s = "   \t\t\r\n  123  \t\r\n\r\t  ";
        ucpp::strings::trim_left(s);
        assert(s == "123  \t\r\n\r\t  ");
    }

    assert(ucpp::strings::trim_right_copy("   \t\t\r\n  123  \t\r\n\r\t  ") == "   \t\t\r\n  123");
    {
        std::string s = "   \t\t\r\n  123  \t\r\n\r\t  ";
        ucpp::strings::trim_right(s);
        assert(s == "   \t\t\r\n  123");
    }

    assert(ucpp::strings::starts_with("abcdefg", "abc"));
    assert(!ucpp::strings::starts_with("abcdefg", "bcd"));
    assert(ucpp::strings::starts_with("abcdefg", 'a'));
    assert(!ucpp::strings::starts_with("abcdefg", 'b'));
    assert(ucpp::strings::ends_with("abcdefg", "efg"));
    assert(!ucpp::strings::ends_with("abcdefg", "efh"));
    assert(ucpp::strings::ends_with("abcdefg", 'g'));
    assert(!ucpp::strings::ends_with("abcdefg", 'h'));
    assert(ucpp::strings::starts_with("abcdefg", "ABC", true));
    assert(!ucpp::strings::starts_with("abcdefg", "BCD", true));
    assert(ucpp::strings::starts_with("abcdefg", 'A', true));
    assert(!ucpp::strings::starts_with("abcdefg", 'B', true));
    assert(ucpp::strings::ends_with("abcdefg", "EFG", true));
    assert(!ucpp::strings::ends_with("abcdefg", "EFH", true));
    assert(ucpp::strings::ends_with("abcdefg", 'G', true));
    assert(!ucpp::strings::ends_with("abcdefg", 'H', true));

    assert(ucpp::strings::contains("abcdefg", "bcd"));
    assert(!ucpp::strings::contains("abcdefg", "bce"));
    assert(ucpp::strings::contains("abcdefg", 'b'));
    assert(!ucpp::strings::contains("abcdefg", 'n'));
    assert(ucpp::strings::contains("abcdefg", "BCD", true));
    assert(!ucpp::strings::contains("abcdefg", "BCE", true));
    assert(ucpp::strings::contains("abcdefg", 'B', true));
    assert(!ucpp::strings::contains("abcdefg", 'N', true));

    assert(ucpp::strings::equals("AbCdEfG", "aBcDeFg", true));
    assert(!ucpp::strings::equals("AbCdEfG", "aBcDeFg", false));
    assert(ucpp::strings::equals("AbCdEfG", "AbCdEfG"));
    assert(!ucpp::strings::equals("AbCdEfG", "AbCdEfo"));

    assert(ucpp::strings::pad_left("123", '0', 5) == "00123");
    assert(ucpp::strings::pad_left("abc", ' ', 5) == "  abc");
    assert(ucpp::strings::pad_right("123", ' ', 5) == "123  ");
    assert(ucpp::strings::pad_right("abc", '0', 5) == "abc00");
    assert(ucpp::strings::pad_left("123456", '0', 3) == "123456");
    assert(ucpp::strings::pad_right("123456", '0', 3) == "123456");

    assert(ucpp::strings::repeat("abc", 3) == "abcabcabc");
    assert(ucpp::strings::repeat('a', 3) == "aaa");

    assert(ucpp::strings::join({"a", "b", "c"}, ",") == "a,b,c");
    assert(ucpp::strings::join(",", "a", "b", "c") == "a,b,c");

    assert(string_list_equals(ucpp::strings::split("a, b, c", ", "), {"a", "b", "c"}));
    assert(string_list_equals(ucpp::strings::split("a, b, c", ", ", 2), {"a", "b, c"}));
    assert(string_list_equals(ucpp::strings::split("a, b, c", ", ", 1), {"a, b, c"}));
    assert(string_list_equals(ucpp::strings::split("a, b, c", ", ", 0), {}));

    assert(string_list_equals(ucpp::strings::split("a,b,c", ','), {"a", "b", "c"}));
    assert(string_list_equals(ucpp::strings::split("a,b,c", ',', 2), {"a", "b,c"}));
    assert(string_list_equals(ucpp::strings::split("a,b,c", ',', 1), {"a,b,c"}));
    assert(string_list_equals(ucpp::strings::split("a,b,c", ',', 0), {}));

    assert(string_list_equals(ucpp::strings::regex_split("Hello,123,world,456,!", ",", 3),
                              {"Hello", "123", "world,456,!"}));
    assert(string_list_equals(ucpp::strings::regex_split("a,\r b,\n \tc", ",\\s+"), {"a", "b", "c"}));
    assert(string_list_equals(ucpp::strings::regex_split("a,\r b,\n \tc", ",\\s+", 2), {"a", "b,\n \tc"}));
    assert(string_list_equals(ucpp::strings::regex_split("a,\r b,\n \tc", ",\\s+", 1), {"a,\r b,\n \tc"}));
    assert(string_list_equals(ucpp::strings::regex_split("a,\r b,\n \tc", ",\\s+", 0), {}));

    assert(ucpp::strings::replace_copy("Hello, world!", "world", "123") == "Hello, 123!");
    {
        std::string s = "Hello, world!";
        ucpp::strings::replace(s, "world", "123");
        assert(s == "Hello, 123!");
    }

    assert(ucpp::strings::replace_first_copy("Hello, world!", "o", "123") == "Hell123, world!");
    {
        std::string s = "Hello, world!";
        ucpp::strings::replace_first(s, "o", "123");
        assert(s == "Hell123, world!");
    }

    assert(ucpp::strings::replace_last_copy("Hello, world!", "o", "123") == "Hello, w123rld!");
    {
        std::string s = "Hello, world!";
        ucpp::strings::replace_last(s, "o", "123");
        assert(s == "Hello, w123rld!");
    }

    assert(ucpp::strings::replace_copy("Hello, world!", "world111", "123") == "Hello, world!");
    {
        std::string s = "Hello, world!";
        ucpp::strings::replace(s, "world111", "123");
        assert(s == "Hello, world!");
    }

    assert(ucpp::strings::replace_first_copy("Hello, world!", "oo", "123") == "Hello, world!");
    {
        std::string s = "Hello, world!";
        ucpp::strings::replace_first(s, "oo", "123");
        assert(s == "Hello, world!");
    }

    assert(ucpp::strings::replace_last_copy("Hello, world!", "oo", "123") == "Hello, world!");
    {
        std::string s = "Hello, world!";
        ucpp::strings::replace_last(s, "oo", "123");
        assert(s == "Hello, world!");
    }

    return 0;
}
