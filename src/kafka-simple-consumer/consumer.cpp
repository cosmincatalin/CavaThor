#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <librdkafka/rdkafkacpp.h>

static volatile sig_atomic_t run = 1;

static void sigterm(int sig) {
  run = 0;
}

int main() {

    signal(SIGINT, sigterm);
    signal(SIGTERM, sigterm);

    std::string err;

    auto *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap.servers", std::getenv("BOOTSTRAP_SERVER"), err);
    conf->set("group.id", "00001", err);

    auto consumer = RdKafka::KafkaConsumer::create(conf, err);

    std::vector<std::string> topics;
    topics.push_back("babylon");

    consumer->subscribe(topics);

    while (run) {
        RdKafka::Message *msg = consumer->consume(1000);
        if(auto message = msg->payload(); message != nullptr) {
            dbg(std::string(static_cast<const char*>(msg->payload())));
            dbg(msg->len());
            if(msg->key_len() > 0) {
                dbg(*msg->key());
            }
        }
        delete msg;
    }

    consumer->close();
    delete consumer;

    dbg("Done");

    return 0;
}
