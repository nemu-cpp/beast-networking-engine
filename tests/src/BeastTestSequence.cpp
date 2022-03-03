/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastTestSequence.h"
#include "BeastResponseBuilderTests.h"
#include "BeastServerTests.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

BeastTestSequence::BeastTestSequence(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "boost::beast implemenation tests", environment)
{
    boost::filesystem::create_directories("../../TestOutput/BeastTests");

    append<BeastResponseBuilderTests>();
    append<BeastServerTests>();
}
