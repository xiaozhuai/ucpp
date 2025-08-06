//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>
#include <iostream>

#include "ucpp/secstr.hpp"

int main() {
    std::cout << SECSTR("Hello, world! 111111") << std::endl;
    std::cout << "Hello, world! 222222" << std::endl;
    return 0;
}
