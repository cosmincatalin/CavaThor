#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <signal.h>
#include <librdkafka/rdkafka.h>
#include "car.pb.h"
#include "IRaw2Destination.hpp"
#include "Raw2Redis.hpp"

static volatile sig_atomic_t run = 1;

static void stop(int sig) {
    dbg("Flag change" + sig);
    run = 0;
}

int main() {
    auto sd = CavaThor::Raw2Redis();

    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "bootstrap.servers", "kafka:9092", nullptr, 0);
    rd_kafka_conf_set(conf, "group.id", "dummy-group-id", nullptr, 0);
    rd_kafka_conf_set(conf, "auto.offset.reset", "earliest", nullptr, 0);
    rd_kafka_t* consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, nullptr, 0);
    conf = nullptr;
    rd_kafka_topic_partition_list_t *subscription = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(subscription, "users-pb", RD_KAFKA_PARTITION_UA);
    rd_kafka_subscribe(consumer, subscription);
    rd_kafka_topic_partition_list_destroy(subscription);
    signal(SIGINT, stop);
    while (run) {
        rd_kafka_message_t* consumer_message;

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
            example::Car car_out;
            car_out.ParseFromArray(consumer_message->payload, consumer_message->len);
            dbg(car_out.DebugString());
        }

        // Free the message when we're done.
        rd_kafka_message_destroy(consumer_message);
    }

    rd_kafka_consumer_close(consumer);
    rd_kafka_destroy(consumer);

    dbg("Done Kafka");
    return 0;
}
