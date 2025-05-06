//"Copyright 2025 Owner"
#include <iostream>
#include "Automata.h"

int main() {
    Automata machine;
    std::cout << "Initial state: "
        << static_cast<int>(machine.getState()) << std::endl;

    machine.on();
    std::cout << "State after on(): "
        << static_cast<int>(machine.getState()) << std::endl;

    machine.getMenu();

    machine.coin(200);
    std::cout << "Balance after coin(200): "
        << machine.getCash() << std::endl;

    std::cout << "Attempting invalid selection -1:" << std::endl;
    machine.choice(-1);

    std::cout << "Choosing valid drink 1:" << std::endl;
    machine.choice(1);
    std::cout << "State after choice(1): "
        << static_cast<int>(machine.getState()) << std::endl;

    std::cout << "Checking funds:" << std::endl;
    if (machine.check()) {
        machine.cook();
        machine.finish();
    }
    else {
        machine.cancel();
    }

    machine.off();
    std::cout << "State after off(): "
        << static_cast<int>(machine.getState()) << std::endl;
    return 0;
}