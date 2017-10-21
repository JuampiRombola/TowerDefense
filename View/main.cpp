#include <string>
#include "mainView.h"
#include "mainEditor.h"

int main(int argc, char** argv) {
    if (argc > 1 && "editor" == std::string(argv[1]))
        return mainEditor(argc, argv);
    return mainView(argc, argv);
}

