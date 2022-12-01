#ifndef RUNNERS_RAW2REDIS_HPP_
#define RUNNERS_RAW2REDIS_HPP_

#include <iostream>
#include "IRaw2Destination.hpp"

namespace CavaThor {

class Raw2Redis : public CavaThor::IRaw2Destination {
 public:
    Raw2Redis();
    void persist() override;
    ~Raw2Redis() override = default;
};

}  // CavaThor

#endif  // RUNNERS_RAW2REDIS_HPP_
