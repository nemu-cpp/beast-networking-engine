/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_HELPERS_TESTROUTES_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_HELPERS_TESTROUTES_H_

#include "Nemu/Core/Routes.h"
#include <mutex>
#include <vector>
#include <string>
#include <memory>

class TestRoutes : public Nemu::Routes
{
public:
    TestRoutes();

    const std::vector<std::string>& visitedRoutes() const;

private:
    std::mutex m_visitedRoutesMutex;
    std::shared_ptr<std::vector<std::string>> m_visitedRoutes;
};

#endif
