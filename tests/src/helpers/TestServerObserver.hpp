/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_HELPERS_TESTSERVEROBSERVER_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_TESTS_HELPERS_TESTSERVEROBSERVER_H_

#include "Nemu/Core/Server.h"
#include <mutex>
#include <vector>
#include <tuple>

class TestServerObserver : public Nemu::Server::Observer
{
public:
    enum EEventType
    {
        eConnectionOpened,
        eConnectionClosed
    };

    const std::vector<std::tuple<EEventType, const Nemu::Server*, std::string>>& connectionEvents() const;

    void onConnectionOpened(const Nemu::Server& source, const std::string& sourceAddress) override;
    void onConnectionClosed(const Nemu::Server& source, const std::string& sourceAddress) override;

private:
    std::mutex m_connectionEventsMutex;
    std::vector<std::tuple<EEventType, const Nemu::Server*, std::string>> m_connectionEvents;
};

#endif
