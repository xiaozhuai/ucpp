//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>
#include <iostream>

#include "ucpp/endian.hpp"

int main() {
    std::cout << "IS_LITTLE: " << ucpp::endian::IS_LITTLE << std::endl;
    std::cout << "IS_BIG: " << ucpp::endian::IS_BIG << std::endl;
    return 0;
}
