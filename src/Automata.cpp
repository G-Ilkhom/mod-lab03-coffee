//"Copyright 2025 Owner"
#include <iostream>
#include "Automata.h"

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
        cout << "The machine is on" << endl;
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

void Automata::off() {
    if (state == STATES::WAITING) {
        state = STATES::OFF;
        cout << "The machine is off" << endl;
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAITING || state == STATES::ACCEPTING) {
        cash += amount;
        state = STATES::ACCEPTING;
        cout << "You deposited " << amount << ", Current balance: " << cash << endl;
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

STATES Automata::getState() {
    return state;
}

void Automata::getMenu() {
    cout << "Menu:" << endl;
    for (int i = 0; i < (int)menu.size(); ++i) {
        cout << i << ": " << menu[i] << " - " << prices[i] << endl;
    }
}

void Automata::choice(int index) {
    if (state == STATES::ACCEPTING) {
        if (index >= 0 && index < (int)menu.size()) {
            selected_drink = index;
            state = STATES::SELECTION;
            cout << "You have chosen: " << menu[index] << endl;
        }
        else {
            cout << "Incorrect drink index" << endl;
        }
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

bool Automata::check() {
    if (state == STATES::SELECTION) {
        if (cash >= prices[selected_drink]) {
            cout << "There is enough money, preparations begin" << endl;
            return true;
        }
        else {
            cout << "Not enough money" << endl;
            return false;
        }
    }
    else {
        cout << "Incorrect state" << endl;
        return false;
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPTING || state == STATES::SELECTION) {
        cout << "Order cancelled, refund: " << cash << endl;
        cash = 0;
        selected_drink = -1;
        state = STATES::WAITING;
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

void Automata::cook() {
    if (state == STATES::SELECTION) {
        state = STATES::DISPENSING;
        cout << "Preparing the drink: " << menu[selected_drink] << endl;
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

void Automata::finish() {
    if (state == STATES::DISPENSING) {
        cout << "The drink is ready" << endl;
        int change = cash - prices[selected_drink];
        if (change > 0) {
            cout << "Your change is: " << change << endl;
        }
        cash = 0;
        selected_drink = -1;
        state = STATES::WAITING;
    }
    else {
        cout << "Incorrect state" << endl;
    }
}

int Automata::getCash() {
    return cash;
}

int Automata::getSelectedDrink() {
    return selected_drink;
}

int Automata::getPrice(int index) {
    if (index >= 0 && index < (int)prices.size()) {
        return prices[index];
    }
    else {
        cout << "Incorrect index" << endl;
        return 0;
    }
}