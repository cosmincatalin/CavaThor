#define DBG_MACRO_NO_WARNING
#include "Replicator.hpp"
#include "proto/car.pb.h"
#include <dbg.h>
#include <iostream>
#include <signal.h>
#include <string_view>
#include <thread>
#include <unistd.h>

namespace CavaThor {

    void Replicator::thread_fn() const {
        while (run) {
            dbg("In Thread");
            sleep(2);
        }
    }

    Replicator::Replicator(rd_kafka_t* consumer, redisContext* engine): consumer(consumer), engine(engine) {}

    bool Replicator::start() {
        dbg("Starting");
//        task_ = std::thread(&CavaThor::Replicator::thread_fn, this);
        {
                    rd_kafka_topic_partition_list_t *subscription = rd_kafka_topic_partition_list_new(1);
                    rd_kafka_topic_partition_list_add(subscription, "test_users", RD_KAFKA_PARTITION_UA);
                    rd_kafka_subscribe(this->consumer, subscription);
                    rd_kafka_topic_partition_list_destroy(subscription);
                    signal(SIGTERM, CavaThor::stop);
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
                            dbg(consumer_message->payload);
                        }

                        // Free the message when we're done.
                        rd_kafka_message_destroy(consumer_message);
                    }

                    rd_kafka_consumer_close(this->consumer);
                    rd_kafka_destroy(this->consumer);
        }
        return true;
    }

    bool Replicator::stop() {
        dbg("Stopping");
        CavaThor::stop(1);
        task_.join();
        dbg("Joined");
        return true;
    }

}  // namespace CavaThor
