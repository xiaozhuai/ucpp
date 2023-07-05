//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>
#include <sstream>

#include "ucpp/tuple_foreach.hpp"

int main() {
    auto tp = std::make_tuple(1, "a", 33);
    std::stringstream ss;
    ucpp::tuple_for_each(tp, [&ss](auto&& elem) { ss << elem; });
    assert(ss.str() == "1a33");
    return 0;
}
