//"Copyright 2025 Owner"
#include "Automata.h"
#include <iostream>

Automata::Automata()
    : cash(0),
    menu({ "Cappuccino", "Tea", "Espresso", "Latte" }),
    prices({ 120, 60, 80, 140 }),
    state(STATES::OFF),
    selected_drink(-1) {
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAITING;
        std::cout << "The machine is on" << std::endl;
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::off() {
    if (state == STATES::WAITING) {
        state = STATES::OFF;
        std::cout << "The machine is off" << std::endl;
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAITING || state == STATES::ACCEPTING) {
        cash += amount;
        state = STATES::ACCEPTING;
        std::cout << "You deposited " << amount
            << ", Current balance: " << cash << std::endl;
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

STATES Automata::getState() {
    return state;
}

void Automata::getMenu() {
    std::cout << "Menu:" << std::endl;
    for (int i = 0; i < static_cast<int>(menu.size()); ++i) {
        std::cout << i << ": " << menu[i]
            << " - " << prices[i] << std::endl;
    }
}

void Automata::choice(int index) {
    if (state == STATES::ACCEPTING) {
        if (index >= 0 && index < static_cast<int>(menu.size())) {
            selected_drink = index;
            state = STATES::SELECTION;
            std::cout << "You have chosen: " << menu[index] << std::endl;
        }
        else {
            std::cout << "Incorrect drink index" << std::endl;
        }
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

bool Automata::check() {
    if (state == STATES::SELECTION) {
        if (cash >= prices[selected_drink]) {
            std::cout << "There is enough money, preparations begin"
                << std::endl;
            return true;
        }
        else {
            std::cout << "Not enough money" << std::endl;
            return false;
        }
    }
    else {
        std::cout << "Incorrect state" << std::endl;
        return false;
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPTING || state == STATES::SELECTION) {
        std::cout << "Order cancelled, refund: " << cash << std::endl;
        cash = 0;
        selected_drink = -1;
        state = STATES::WAITING;
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::cook() {
    if (state == STATES::SELECTION) {
        state = STATES::DISPENSING;
        std::cout << "Preparing the drink: "
            << menu[selected_drink] << std::endl;
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

void Automata::finish() {
    if (state == STATES::DISPENSING) {
        std::cout << "The drink is ready" << std::endl;
        int change = cash - prices[selected_drink];
        if (change > 0) {
            std::cout << "Your change is: " << change << std::endl;
        }
        cash = 0;
        selected_drink = -1;
        state = STATES::WAITING;
    }
    else {
        std::cout << "Incorrect state" << std::endl;
    }
}

int Automata::getCash() {
    return cash;
}

int Automata::getSelectedDrink() {
    return selected_drink;
}

int Automata::getPrice(int index) {
    if (index >= 0 && index < static_cast<int>(prices.size())) {
        return prices[index];
    }
    std::cout << "Incorrect index" << std::endl;
    return 0;
}