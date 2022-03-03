/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_BEASTSERVERTESTS_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_BEASTSERVERTESTS_H_

#include <Ishiko/Tests.hpp>

class BeastServerTests : public Ishiko::Tests::TestSequence
{
public:
    BeastServerTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
    static void StartTest1(Ishiko::Tests::Test& test);
    static void StartTest2(Ishiko::Tests::Test& test);
    static void StartTest3(Ishiko::Tests::Test& test);
    static void RequestTest1(Ishiko::Tests::FileComparisonTest& test);
    static void RequestTest2(Ishiko::Tests::FileComparisonTest& test);
    static void RequestTest3(Ishiko::Tests::Test& test);
    static void RequestTest4(Ishiko::Tests::Test& test);
    static void RequestTest5(Ishiko::Tests::Test& test);
};

#endif
