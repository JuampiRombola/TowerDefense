#include <string>
#include "mainView.h"
#include "mainEditor.h"

int main(int argc, char** argv) {
    if (argc > 0 && "editor" == std::string(argv[0]))
        return mainEditor(argc, argv);
    return mainView(argc, argv);
}

