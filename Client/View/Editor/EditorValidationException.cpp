#include "EditorValidationException.h"
#include <cstdarg>
#include <iostream>

EditorValidationException::EditorValidationException(const std::string& errMsg)
noexcept {
    _errno = errno;
    this->errMsg = errMsg;
}

const char* EditorValidationException::what() noexcept {
    return errMsg.c_str();
}