#include "File.h"

File::File(const std::string &fileName) {
    this->file.open(fileName, std::fstream::out);
}

void File::write(const std::string &content) {
    file << content;
}

File::~File() {
    file.close();
}