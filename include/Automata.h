//"Copyright 2025 Owner"
#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <vector>
#include <string>

using std::vector;
using std::string;

enum class STATES { OFF, WAITING, ACCEPTING, SELECTION, DISPENSING, FINISHED };

class Automata {
 private:
    int cash;
    vector<string> menu;
    vector<int> prices;
    STATES state;
    int selected_drink;
    
 public:
    Automata();
    void on();
    void off();
    void coin(int amount);
    STATES getState();
    void getMenu();
    void choice(int index);
    bool check();
    void cancel();
    void cook();
    void finish();
    int getCash();
    int getSelectedDrink();
    int getPrice(int index);
};

#endif  // INCLUDE_AUTOMATA_H_
