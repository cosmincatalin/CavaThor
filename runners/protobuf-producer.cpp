#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include "user.pb.h"

int main()
{
    runners::User user;
    *user.mutable_dept() = "DS";
    *user.mutable_name() = "Catalin";
    std::string str;
    user.SerializeToString(&str);
    dbg(str);
    dbg("Done Proto");
    return 0;
}