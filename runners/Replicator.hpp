#ifndef RUNNERS_REPLICATOR_HPP_
#define RUNNERS_REPLICATOR_HPP_

#include <thread>
#include <librdkafka/rdkafka.h>
#include <hiredis/hiredis.h>

namespace CavaThor {

class Replicator {
 private:
    rd_kafka_t* consumer;
    redisContext* engine;
    void thread_fn() const;
    std::thread task_;
 public:
    explicit Replicator(rd_kafka_t* consumer, redisContext* engine);
    bool start();
    bool stop();
};

}  // namespace CavaThor

#endif  // RUNNERS_REPLICATOR_HPP_
