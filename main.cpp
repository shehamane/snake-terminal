#include <iostream>
#include "src/lib/Controller.h"
#include "src/lib/Level.h"

std::vector<std::string> TEST_PATTERN = {
        "############################################################",
        "#                                                          #",
        "#                                                          #",
        "#                                                          #",
        "#                            *                             #",
        "#                                                          #",
        "#                                                          #",
        "#                                                          #",
        "#                                                          #",
        "############################################################"
};

int main() {
    try {
        Controller game(TEST_PATTERN, 15);
        game.start();
    }
    catch (char const *e) {
        std::cout << e;
    }


    return 0;
}
