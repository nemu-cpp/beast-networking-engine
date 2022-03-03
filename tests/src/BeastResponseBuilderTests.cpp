/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastResponseBuilderTests.h"
#include "Nemu/BeastConnectionEngine/BeastResponseBuilder.h"

using namespace Ishiko::Tests;

BeastResponseBuilderTests::BeastResponseBuilderTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BeastResponseBuilder tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
}

void BeastResponseBuilderTests::CreationTest1(Test& test)
{
    Nemu::Views views;
    Nemu::BeastResponseBuilder response(views);

    ISHIKO_PASS();
}
