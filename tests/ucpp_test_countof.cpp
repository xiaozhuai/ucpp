//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>

#include "ucpp/countof.hpp"

int main() {
    int arr[1024] = {0};
    static_assert(ucpp::countof(arr) == 1024);
    return 0;
}
