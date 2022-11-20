#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include "hiredis/hiredis.h"

int main()
{
    auto *context = redisConnect("127.0.0.1", 6379);
    if (context == nullptr || context->err) {
        if (context) {
            std::cout << (context->errstr) << "\n";
        } else {
            dbg("Can't allocate redis context\n");
        }
    }
    auto reply = redisCommand(context, "SET hiredis:03 bar");
    if (context == nullptr || context->err) {
        if (context) {
            std::cout << (context->errstr) << "\n";
        } else {
            dbg("Can't allocate redis context\n");
        }
    }
    redisFree(context);
    dbg(reply);

    return 0;
}