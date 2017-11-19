#ifndef TOWERDEFENSE_DEPTHLEVELERROR_H
#define TOWERDEFENSE_DEPTHLEVELERROR_H

#include <typeinfo>

#define BUFFER_LEN 256

class DepthLevelError : public std::exception {
private:
    char msg_error[BUFFER_LEN];

public:
    explicit DepthLevelError(const char *msg) noexcept;
    virtual const char *what() const noexcept;
};


#endif //TOWERDEFENSE_DEPTHLEVELERROR_H
