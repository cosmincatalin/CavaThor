#define DBG_MACRO_NO_WARNING
#include "Replicator.hpp"
#include <signal.h>
#include <dbg.h>
#include <thread>
#include <string_view>
#include <iostream>
#include "car.pb.h"

namespace CavaThor {

    static volatile sig_atomic_t run = 1;

    static void stop(int sig) {
        dbg("Flag change" + sig);
        run = 0;
    }

    Replicator::Replicator(rd_kafka_t* consumer, redisContext* engine): consumer(consumer), engine(engine) {}

    bool Replicator::start() {
        rd_kafka_topic_partition_list_t *subscription = rd_kafka_topic_partition_list_new(1);
        rd_kafka_topic_partition_list_add(subscription, "users-pb", RD_KAFKA_PARTITION_UA);
        rd_kafka_subscribe(this->consumer, subscription);
        rd_kafka_topic_partition_list_destroy(subscription);
        signal(SIGINT, CavaThor::stop);
        while (run) {
            rd_kafka_message_t* consumer_message;

            consumer_message = rd_kafka_consumer_poll(this->consumer, 500);
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

        rd_kafka_consumer_close(this->consumer);
        rd_kafka_destroy(this->consumer);
        return true;
    }

    bool Replicator::stop() {
        return true;
    }

}  // namespace CavaThor
