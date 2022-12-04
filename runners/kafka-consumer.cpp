#define DBG_MACRO_NO_WARNING
#include <hiredis/hiredis.h>
#include <dbg.h>
#include <librdkafka/rdkafka.h>
#include "Replicator.hpp"

int main() {
    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "bootstrap.servers", "kafka:9092", nullptr, 0);
    rd_kafka_conf_set(conf, "group.id", "dummy-group-id", nullptr, 0);
    rd_kafka_conf_set(conf, "auto.offset.reset", "earliest", nullptr, 0);
    auto consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, nullptr, 0);
    conf = nullptr;

    auto context = redisConnect("redis", 6379);
    auto replicator = CavaThor::Replicator(consumer, context);
    replicator.start();

    dbg("Done Kafka");
    return 0;
}
