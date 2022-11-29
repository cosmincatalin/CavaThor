#ifndef RUNNERS_RAW2REDIS_HPP_
#define RUNNERS_RAW2REDIS_HPP_

#include <iostream>
#include "IRaw2Destination.hpp"

namespace CavaThor {

class Raw2Redis {
 public:
    Raw2Redis();
    void persist();
    ~Raw2Redis() = default;
};

}  // CavaThor

#endif  // RUNNERS_RAW2REDIS_HPP_
