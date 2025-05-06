// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"
#include <string>

TEST(task, test1_initial_state) {
    Automata automata;
    EXPECT_EQ(automata.getState(), STATES::OFF);
}

TEST(task, test2_on_transitions_to_waiting) {
    Automata automata;
    testing::internal::CaptureStdout();
    automata.on();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("The machine is on"), std::string::npos);
    EXPECT_EQ(automata.getState(), STATES::WAITING);
}

TEST(task, test3_menu_prints_items) {
    Automata automata;
    testing::internal::CaptureStdout();
    automata.getMenu();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("0: Cappuccino - 120"), std::string::npos);
    EXPECT_NE(output.find("3: Latte - 140"), std::string::npos);
}

TEST(task, test4_incorrect_choice_index) {
    Automata automata;
    automata.on();
    automata.coin(200);
    testing::internal::CaptureStdout();
    automata.choice(-1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Incorrect drink index"), std::string::npos);
}

TEST(task, test5_coin_prints_and_updates) {
    Automata automata;
    automata.on();
    testing::internal::CaptureStdout();
    automata.coin(50);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("You deposited 50, Current balance: 50"), std::string::npos);
    EXPECT_EQ(automata.getCash(), 50);
    EXPECT_EQ(automata.getState(), STATES::ACCEPTING);
}

TEST(task, test6_choice_valid_index) {
    Automata automata;
    automata.on(); automata.coin(100);
    testing::internal::CaptureStdout();
    automata.choice(2);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("You have chosen: Espresso"), std::string::npos);
    EXPECT_EQ(automata.getState(), STATES::SELECTION);
}

TEST(task, test7_check_insufficient) {
    Automata automata;
    automata.on(); automata.coin(50); automata.choice(1);
    testing::internal::CaptureStdout();
    bool result = automata.check();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(result);
    EXPECT_NE(output.find("Not enough money"), std::string::npos);
}

TEST(task, test8_check_sufficient) {
    Automata automata;
    automata.on(); automata.coin(200); automata.choice(0);
    testing::internal::CaptureStdout();
    bool result = automata.check();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(result);
    EXPECT_NE(output.find("preparations begin"), std::string::npos);
}

TEST(task, test9_cook_and_finish_prints) {
    Automata automata;
    automata.on(); automata.coin(200); automata.choice(3);
    automata.check();
    testing::internal::CaptureStdout();
    automata.cook();
    automata.finish();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Preparing the drink: Latte"), std::string::npos);
    EXPECT_NE(output.find("The drink is ready"), std::string::npos);
    EXPECT_NE(output.find("Your change is: 60"), std::string::npos);
}

TEST(task, test10_cancel_refund) {
    Automata automata;
    automata.on(); automata.coin(70);
    testing::internal::CaptureStdout();
    automata.cancel();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Order cancelled, refund: 70"), std::string::npos);
    EXPECT_EQ(automata.getState(), STATES::WAITING);
}