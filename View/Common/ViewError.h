#ifndef TOWERDEFENSE_VIEWERROR_H
#define TOWERDEFENSE_VIEWERROR_H

#include <typeinfo>

#define BUF_LEN 256


class ViewError : public std::exception {
private:
    char msg_error[BUF_LEN];

public:
    explicit ViewError(const char *fmt, ...) noexcept;
    virtual const char *what() const noexcept;
    virtual ~ViewError() noexcept {}
};


#endif //TOWERDEFENSE_VIEWERROR_H
