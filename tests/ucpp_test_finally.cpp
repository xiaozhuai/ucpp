//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>

#include "ucpp/finally.hpp"

int main() {
    int a = 0;
    {
        finally { a = 100; };
        assert(a == 0);
    }
    assert(a == 100);
    return 0;
}
