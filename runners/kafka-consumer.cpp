#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <signal.h>
#include <librdkafka/rdkafka.h>

static volatile sig_atomic_t run = 1;

static void stop(int sig) {
    dbg("Flag change");
    run = 0;
}

int main()
{
    char errstr[512];
    rd_kafka_resp_err_t err;
    rd_kafka_conf_t* conf = rd_kafka_conf_new();
    rd_kafka_conf_set(conf, "bootstrap.servers", "kafka:9092", errstr, sizeof(errstr));
    rd_kafka_conf_set(conf, "group.id", "dummy-group-id", errstr, sizeof(errstr));
    rd_kafka_conf_set(conf, "auto.offset.reset", "earliest", nullptr, 0);
    rd_kafka_t* consumer = rd_kafka_new(RD_KAFKA_CONSUMER, conf, errstr, sizeof(errstr));
    conf = nullptr;
    const char *topic = "users";
    rd_kafka_topic_partition_list_t *subscription = rd_kafka_topic_partition_list_new(1);
    rd_kafka_topic_partition_list_add(subscription, topic, RD_KAFKA_PARTITION_UA);
    err = rd_kafka_subscribe(consumer, subscription);
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
            dbg((char *)consumer_message->payload);
            dbg(consumer_message->len);
        }

        // Free the message when we're done.
        rd_kafka_message_destroy(consumer_message);
    }

    rd_kafka_consumer_close(consumer);
    rd_kafka_destroy(consumer);

    dbg("Done Kafka");
    return 0;
}