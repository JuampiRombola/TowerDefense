#ifndef TOWERDEFENSE_FILE_H
#define TOWERDEFENSE_FILE_H


#include <fstream>

class File {
private:
    std::fstream file;
public:
    File(const std::string& fileName);
    ~File();
    void write(const std::string& content);
};


#endif //TOWERDEFENSE_FILE_H
