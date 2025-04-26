//"Copyright 2025 Owner"
#include <iostream>
#include <string>
#include <vector>
#include "Automata.h"

Automata::Automata() {
    state = OFF;
    cash = 0;
    currentDrink = -1;

    menu.push_back("Tea");
    menu.push_back("Espresso");
    menu.push_back("Latte");

    prices.push_back(30);
    prices.push_back(60);
    prices.push_back(100);
}

STATES Automata::getState() {
    return state;
}

void Automata::getMenu() {
    std::cout << "Menu:" << std::endl;
    for (int i = 0; i < menu.size(); i++) {
        std::cout << i << ": " << menu[i]
            << " - " << prices[i] << std::endl;
    }
}

void Automata::on() {
    if (state == OFF) {
        state = WAIT;
        std::cout << "The machine is on" << std::endl;
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::off() {
    if (state == WAIT) {
        state = OFF;
        std::cout << "The machine is off" << std::endl;
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::coin(int sum) {
    if (state == WAIT || state == ACCEPT) {
        state = ACCEPT;
        cash += sum;
        std::cout << "You deposited " << sum
            << ", Current balance: " << cash << std::endl;
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::cancel() {
    if (state == ACCEPT || state == CHECK) {
        std::cout << "Order cancelled, refund: " << cash << std::endl;
        cash = 0;
        state = WAIT;
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::choice(int drinkIndex) {
    if (state == ACCEPT) {
        if (drinkIndex >= 0 && drinkIndex < menu.size()) {
            std::cout << "You have chosen: " << menu[drinkIndex] << std::endl;
            currentDrink = drinkIndex;
            state = CHECK;
        } else {
            std::cout << "Incorrect drink index" << std::endl;
        }
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::check() {
    if (state == CHECK) {
        if (cash >= prices[currentDrink]) {
            std::cout <<
                "There is enough money, preparations begin" << std::endl;
        } else {
            std::cout << "Not enough money" << std::endl;
        }
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::cook() {
    if (state == CHECK) {
        state = COOK;
        std::cout << "Preparing the drink: "
            << menu[currentDrink] << std::endl;
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::finish() {
    if (state == COOK) {
        std::cout << "The drink is ready" << std::endl;
        if (cash > prices[currentDrink]) {
            std::cout << "Your change is: " <<
                cash - prices[currentDrink] << std::endl;
        }
        cash = 0;
        state = WAIT;
        currentDrink = -1;
    } else {
        std::cout << "Incorrect state" << std::endl;
    }
}
