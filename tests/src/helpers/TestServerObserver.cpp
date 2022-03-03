/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "TestServerObserver.hpp"

const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>&
TestServerObserver::connectionEvents() const
{
    return m_connectionEvents;
}

void TestServerObserver::onConnectionOpened(const Nemu::Server& source, const std::string& sourceAddress)
{
    std::lock_guard<std::mutex> guard(m_connectionEventsMutex);
    m_connectionEvents.emplace_back(eConnectionOpened, &source, sourceAddress);
}

void TestServerObserver::onConnectionClosed(const Nemu::Server& source, const std::string& sourceAddress)
{
    std::lock_guard<std::mutex> guard(m_connectionEventsMutex);
    m_connectionEvents.emplace_back(eConnectionClosed, &source, sourceAddress);
}
