#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <librdkafka/rdkafkacpp.h>

static volatile sig_atomic_t run = 1;

static void sigterm(int sig) {
    dbg(sig);
    run = 0;
}

int main() {
    std::string err;

    auto *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap.servers", std::getenv("BOOTSTRAP_SERVER"), err);

    auto producer = RdKafka::Producer::create(conf, err);
    auto topic = RdKafka::Topic::create(producer, "babylon", nullptr, err);
    delete conf;

    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);

    std::string message{"string message without a key"};
    producer->produce(topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char *>(message.c_str()), message.length(), nullptr, nullptr);

    message = "string message with key";
    const std::string key_for_string_message = "key for a string message";
    producer->produce(topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY, const_cast<char *>(message.c_str()), message.length(), &key_for_string_message, nullptr);

    producer->poll(0);
    producer->flush(10 * 1000 /* wait for max 10 seconds */);
    delete producer;

    dbg("Done");

    return 0;
}
