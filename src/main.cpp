//"Copyright 2025 Owner"
#include <iostream>
#include "Automata.h"

int main() {
    Automata automata;
    cout << "Initial state: " << static_cast<int>(automata.getState()) << endl;

    automata.on();
    cout << "State after on(): " << static_cast<int>(automata.getState()) << endl;

    automata.getMenu();

    automata.coin(200);
    cout << "Balance after coin(200): " << automata.getCash() << endl;

    cout << "Attempting invalid selection -1:" << endl;
    automata.choice(-1);

    cout << "Choosing valid drink 1:" << endl;
    automata.choice(1);
    cout << "State after choice(1): " << static_cast<int>(automata.getState()) << endl;

    cout << "Checking funds:" << endl;
    if (automata.check()) {
        automata.cook();
        automata.finish();
    }
    else {
        automata.cancel();
    }

    automata.off();
    cout << "State after off(): " << static_cast<int>(automata.getState()) << endl;
    return 0;
}
