#include "Replicator.hpp"

#define DBG_MACRO_NO_WARNING
#include <dbg.h>

int main()
{

    CavaThor::Replicator replicator {"redis://localhost:6379"};
    dbg(replicator.start());
    return 0;
}