#ifndef SRC_REPLICATOR_HPP_
#define SRC_REPLICATOR_HPP_

#include <string_view>

namespace CavaThor {

class Replicator {
 public:
    explicit Replicator(std::string_view url);
    bool start();
    bool stop();
};

}

#endif  // SRC_REPLICATOR_HPP_
