// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"
#include <string>

TEST(task, test1) {
    Automata automata;
    EXPECT_EQ(automata.getState(), OFF);
}

TEST(task, test2) {
    Automata automata;
    automata.on();
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(task, test3) {
    Automata automata;
    automata.on();
    automata.coin(100);
    EXPECT_EQ(automata.getState(), ACCEPT);
}

TEST(task, test4) {
    Automata automata;
    automata.on();
    automata.coin(200);
    testing::internal::CaptureStdout();
    automata.choice(-1);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Incorrect drink index"), std::string::npos);
}

TEST(task, test5) {
    Automata automata;
    automata.on();
    automata.coin(60);
    testing::internal::CaptureStdout();
    automata.choice(0);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("You have chosen: Tea"), std::string::npos);
}

TEST(task, test6) {
    Automata automata;
    automata.on();
    automata.coin(60);
    automata.choice(0);
    EXPECT_EQ(automata.getState(), CHECK);
}

TEST(task, test7) {
    Automata automata;
    automata.on();
    automata.coin(200);
    automata.choice(0);
    testing::internal::CaptureStdout();
    automata.cancel();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Order cancelled, refund: 200"), std::string::npos);
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(task, test8) {
    Automata automata;
    automata.on();
    automata.coin(200);
    automata.choice(0);
    automata.check();
    automata.cook();
    EXPECT_EQ(automata.getState(), COOK);
}

TEST(task, test9) {
    Automata automata;
    automata.on();
    automata.coin(200);
    automata.choice(2);
    automata.check();
    automata.cook();

    testing::internal::CaptureStdout();
    automata.finish();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Your change is: 100"), std::string::npos);
    EXPECT_EQ(automata.getState(), WAIT);
}

TEST(task, test10) {
    Automata automata;
    automata.on();
    automata.coin(200);
    automata.choice(2);
    automata.check();
    automata.cook();
    automata.finish();
    automata.off();
    EXPECT_EQ(automata.getState(), OFF);
}
