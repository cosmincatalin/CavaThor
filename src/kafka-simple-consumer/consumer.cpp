#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <librdkafka/rdkafkacpp.h>

int main() {
    std::string err;

    auto *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("bootstrap.servers", std::getenv("BOOTSTRAP_SERVER"), err);
    conf->set("group.id", "00001", err);

    auto consumer = RdKafka::KafkaConsumer::create(conf, err);

    std::vector<std::string> topics;
    topics.push_back("babylon");

    consumer->subscribe(topics);

    while (true) {
        RdKafka::Message *msg = consumer->consume(1000);
        dbg(msg->payload());
        delete msg;
    }

    dbg("Done");

    return 0;
}
