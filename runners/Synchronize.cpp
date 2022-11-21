#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <hiredis/hiredis.h>
#include <librdkafka/rdkafka.h>

int main()
{
    // Kafka Producer
    std::string_view errstr{""};
    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    rd_kafka_t* producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));


    // Redis
    auto* context = redisConnect("redis", 6379);
    redisCommand(context, "SET hiredis:04 bar");
    redisFree(context);


    dbg("Done");
    return 0;
}