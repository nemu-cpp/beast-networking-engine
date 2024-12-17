/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_BEASTRESPONSEBUILDERTESTS_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_BEASTRESPONSEBUILDERTESTS_H_

#include <Ishiko/Tests.hpp>

class BeastResponseBuilderTests : public Ishiko::Tests::TestSequence
{
public:
    BeastResponseBuilderTests(const Ishiko::Tests::TestNumber& number, const Ishiko::Tests::TestContext& context);

private:
    static void CreationTest1(Ishiko::Tests::Test& test);
};

#endif
