#define DBG_MACRO_NO_WARNING
#include "proto/car.pb.h"
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

    proto::Car car;
    *car.mutable_brand() = "BMW";
    char buff[car.ByteSizeLong()];
    char* data = buff;
    car.SerializeToArray(data, car.ByteSizeLong());

    // Gotta check the rror codes
    producer->produce(topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_COPY,
                      data,
                      car.ByteSizeLong(),
                      nullptr, nullptr);

    producer->poll(0);
    producer->flush(10 * 1000);
    delete producer;

    dbg("Done");

    return 0;
}
