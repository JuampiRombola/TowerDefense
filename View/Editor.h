#ifndef TOWERDEFENSE_EDITOR_H
#define TOWERDEFENSE_EDITOR_H

#include <string>

class Editor {
private:
    std::string superficie;
public:
    Editor();
    ~Editor();
    void setSuperficie(const std::string &superficie);
};


#endif //TOWERDEFENSE_EDITOR_H
