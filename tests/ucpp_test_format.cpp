//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>

#include "ucpp/format.hpp"

int main() {
    char str[1024] = {0};
    snprintf(str, sizeof(str), "Hello %s %d", "ucpp", 1024);

    auto str2 = ucpp::format("Hello %s %d", "ucpp", 1024);

    assert(str2 == str);
    return 0;
}
