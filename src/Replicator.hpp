#ifndef CAVATHOR_REPLICATOR_HPP
#define CAVATHOR_REPLICATOR_HPP

#include <string_view>

namespace CavaThor {

    class Replicator {
    private:
    public:
        Replicator(std::string_view url);
        bool start();
        bool stop();
    };

}

#endif //CAVATHOR_REPLICATOR_HPP
