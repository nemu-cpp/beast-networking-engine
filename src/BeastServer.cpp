/*
    Copyright (c) 2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastServer.h"

using namespace boost::asio;

namespace Nemu
{

BeastServer::BeastServer(size_t numberOfThreads, const std::string& address, unsigned int port, Routes& routes,
    Views& views, std::shared_ptr<Observer> observer, Ishiko::Error& error)
    : Server(observer), m_routes(routes), m_views(views), m_ioContext((int)numberOfThreads),
    m_listener(*this, m_ioContext, ip::tcp::endpoint(ip::make_address(address), port), error)
{
    m_threads.resize(numberOfThreads);
}

void BeastServer::start()
{
    m_listener.run();

    // Run the I/O service on the requested number of threads
    for (std::thread& t : m_threads)
    {
        t = std::thread([this]{ m_ioContext.run(); });
    }

    observers().notify(&Observer::onServerStarted, *this);
}

void BeastServer::stop()
{
    m_ioContext.stop();
}

void BeastServer::join()
{
    for (std::thread& t : m_threads)
    {
        t.join();
    }

    observers().notify(&Observer::onServerStopped, *this);
}

bool BeastServer::isRunning() const
{
    return !m_ioContext.stopped();
}

const Routes& BeastServer::routes() const
{
    return m_routes;
}

const Views& BeastServer::views() const
{
    return m_views;
}

AccessLog& BeastServer::accessLog()
{
    return m_accessLog;
}

}
