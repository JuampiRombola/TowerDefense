#ifndef TOWERDEFENSE_EDITORVALIDATIONEXCEPTION_H
#define TOWERDEFENSE_EDITORVALIDATIONEXCEPTION_H

#include <string>
#include <exception>
#include <typeinfo>

class EditorValidationException : public std::exception {
private:
    int _errno;
    std::string errMsg;
public:
    explicit EditorValidationException(const std::string& errMsg) noexcept;
    const char *what() noexcept;
    virtual ~EditorValidationException() noexcept {}
};


#endif //TOWERDEFENSE_EDITORVALIDATIONEXCEPTION_H
