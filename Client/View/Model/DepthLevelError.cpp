#include "DepthLevelError.h"

#include <cstdio>
#include <cstring>

DepthLevelError::DepthLevelError(const char *msg) noexcept {
    strncpy(msg_error, msg, BUFFER_LEN-1);
    msg_error[BUFFER_LEN-1] = 0;
}

const char *DepthLevelError::what() const noexcept {
    return msg_error;
}
