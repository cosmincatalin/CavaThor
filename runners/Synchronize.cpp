#include "Replicator.hpp"

#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <thread>

void foo(int a, int b)
{
    std::cout << a << b;
}

int main()
{
    std::thread t1(foo, 1, 2);

    CavaThor::Replicator replicator {"redis://localhost:6379"};
    replicator.start();
    t1.join();
    return 0;
}