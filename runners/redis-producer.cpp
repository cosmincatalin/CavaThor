#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <hiredis/hiredis.h>

int main() {
    auto* context = redisConnect("redis", 6379);
    redisCommand(context, "SET hiredis:04 bar");
    redisFree(context);
    dbg("Done Redis");
    return 0;
}
