#ifndef RUNNERS_IRAW2DESTINATION_HPP_
#define RUNNERS_IRAW2DESTINATION_HPP_

namespace CavaThor {

class IRaw2Destination {
 public:
    virtual void persist() = 0;
    virtual ~IRaw2Destination() = default;
};

}  // CavaThor

#endif  // RUNNERS_IRAW2DESTINATION_HPP_
