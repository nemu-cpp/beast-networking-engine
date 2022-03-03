/*
    Copyright (c) 2021-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastResponseBuilderTests.h"
#include "BeastServerTests.h"
#include "Nemu/BeastConnectionEngine/linkoptions.hpp"
#include <Ishiko/Tests.hpp>

using namespace Ishiko::Tests;

int main(int argc, char* argv[])
{
    TestHarness theTestHarness("NemuBeastConnectionEngine");

    TestSequence& theTests = theTestHarness.tests();
    theTests.append<BeastResponseBuilderTests>();
    theTests.append<BeastServerTests>();

    return theTestHarness.run();
}
