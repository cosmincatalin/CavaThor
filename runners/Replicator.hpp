#ifndef RUNNERS_REPLICATOR_HPP_
#define RUNNERS_REPLICATOR_HPP_

#include <hiredis/hiredis.h>
#include <librdkafka/rdkafka.h>

namespace CavaThor {

class Replicator {
 private:
    rd_kafka_t* consumer;
    redisContext* engine;
 public:
    explicit Replicator(rd_kafka_t* consumer, redisContext* engine);
    bool start();
    bool stop();
};

}  // namespace CavaThor

#endif  // RUNNERS_REPLICATOR_HPP_
