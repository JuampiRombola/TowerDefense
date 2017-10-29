#ifndef TOWERDEFENSE_KEYBOARDINPUT_H
#define TOWERDEFENSE_KEYBOARDINPUT_H

#include <string>

class KeyboardInput {
private:
    std::string &text;
    int activeId;
public:
    KeyboardInput(std::string &text);
    void setInput(std::string &input);
    void addCharacter(char newChar);
    ~KeyboardInput();

};


#endif //TOWERDEFENSE_KEYBOARDINPUT_H
