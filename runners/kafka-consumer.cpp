#define DBG_MACRO_NO_WARNING
#include <hiredis/hiredis.h>
#include <dbg.h>
#include <unistd.h>
#include <librdkafka/rdkafka.h>
#include "Replicator.hpp"

int main() {
    char errstr[512];
    rd_kafka_resp_err_t err;
    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "bootstrap.servers", std::getenv("BOOTSTRAP_SERVER"), errstr, sizeof(errstr));
    rd_kafka_conf_set(conf, "group.id", "dummy-group-id", errstr, sizeof(errstr));
    rd_kafka_t* consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    conf = nullptr;

    const char *topic = "test_users";
    rd_kafka_topic_partition_list_t *subscription = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(subscription, topic, RD_KAFKA_PARTITION_UA);
    rd_kafka_subscribe(consumer, subscription);
    rd_kafka_topic_partition_list_destroy(subscription);
    while (true) {
        rd_kafka_message_t *consumer_message;

        consumer_message = rd_kafka_consumer_poll(consumer, 500);
        if (!consumer_message) {
            dbg("Waiting...");
            continue;
        }

        if (consumer_message->err) {
            if (consumer_message->err == RD_KAFKA_RESP_ERR__PARTITION_EOF) {
                /* We can ignore this error - it just means we've read
                 * everything and are waiting for more data.
                 */
            } else {
                dbg("Consumer error: %s", rd_kafka_message_errstr(consumer_message));
                return 1;
            }
        } else {
            dbg(consumer_message->payload);
        }

        // Free the message when we're done.
        rd_kafka_message_destroy(consumer_message);
    }

    rd_kafka_consumer_close(consumer);
    rd_kafka_destroy(consumer);

//    auto context = redisConnect(std::getenv("REDIS_HOST"), std::stoi(std::getenv("REDIS_PORT")));
//    auto replicator = CavaThor::Replicator(consumer, context);
//    replicator.start();
//
//    dbg("Done Kafka");
//    dbg("Done sleeping");
////    replicator.stop();
//    CavaThor::stop(1);
    dbg("Stopped?");
    return 0;
}
