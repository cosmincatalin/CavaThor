#include <string_view>
#include <thread>
#include <iostream>
#include "Replicator.hpp"

namespace CavaThor {

    Replicator::Replicator(std::string_view url) {
    }

    bool Replicator::start() {
        return true;
    }

    bool Replicator::stop() {
        return true;
    }

}  // namespace CavaThor
