#include <string_view>
#include <thread>
#include <iostream>
#include "Replicator.hpp"

namespace CavaThor {

    void foo(int a, int b)
    {
        std::cout << a << b;
    }

    Replicator::Replicator(std::string_view url)
    {
        std::thread t1(CavaThor::foo, 1, 2);
    }

    bool Replicator::start() {
        return true;
    }

    bool Replicator::stop() {
        return true;
    }

}