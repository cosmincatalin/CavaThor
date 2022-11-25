#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include "user.pb.h"

int main()
{
    // https://gitter.im/edenhill/librdkafka?at=5508bd2677c8d5b10f4fa596
    runners::User userIn;
    *userIn.mutable_dept() = "DS";
    *userIn.mutable_name() = "Catalin";
    std::string str;
    userIn.SerializeToString(&str);
    char buff[1024];
    char* data = buff;
    userIn.SerializeToArray(data, userIn.ByteSize());

    runners::User userOut;
    userOut.ParseFromArray(data, userIn.ByteSize());
    dbg(userOut.DebugString());
    dbg(data);
    dbg(str);
    dbg("Done Proto");
    return 0;
}
