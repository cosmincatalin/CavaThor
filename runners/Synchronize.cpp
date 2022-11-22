#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <hiredis/hiredis.h>
#include <librdkafka/rdkafka.h>

int main()
{
    // Kafka Producer
    char errstr[512];
    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    if (rd_kafka_conf_set(conf, "bootstrap.servers", "kafka:9092", errstr, sizeof(errstr)) != RD_KAFKA_CONF_OK)
    {
        dbg(errstr);
    }
    rd_kafka_t* producer = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    conf = nullptr;
    rd_kafka_resp_err_t err;
    char const* value = "sadsa";
    size_t value_len{6};
    err = rd_kafka_producev(producer,
                            RD_KAFKA_V_TOPIC("dummy"),
                            RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
                            RD_KAFKA_V_VALUE((void*)value, value_len),
                            RD_KAFKA_V_END);
    if (err) {
        dbg("Failed to produce to topic");
        return 1;
    } else {
        dbg("Produced event to topic");
    }
    rd_kafka_flush(producer, 10 * 1000);

    // Redis
    auto* context = redisConnect("redis", 6379);
    redisCommand(context, "SET hiredis:04 bar");
    redisFree(context);


    dbg("Done");
    return 0;
}