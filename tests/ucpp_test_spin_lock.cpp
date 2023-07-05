//
// Copyright (c) 2023 xiaozhuai
//

#include <cassert>
#include <thread>

#include "ucpp/spin_lock.hpp"
#include "ucpp/synchronized.hpp"

#define LOOP (10000000)

int main() {
    int64_t a = 0;
    ucpp::SpinLock lock;
    auto t1 = std::thread([&] {
        for (int i = 0; i < LOOP; ++i) {
            synchronized(lock) { a++; }
        }
    });
    auto t2 = std::thread([&] {
        for (int i = 0; i < LOOP; ++i) {
            synchronized(lock) { a++; }
        }
    });

    t1.join();
    t2.join();
    assert(a == LOOP * 2);
    return 0;
}
