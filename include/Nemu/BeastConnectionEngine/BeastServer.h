/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTSERVER_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTSERVER_H_

#include "BeastListener.h"
#include <Ishiko/Errors.hpp>
#include <Nemu/Core.h>
#include <boost/asio/io_context.hpp>
#include <thread>
#include <memory>

namespace Nemu
{

class BeastServer : public Server
{
public:
    BeastServer(size_t numberOfThreads, const std::string& address, unsigned int port, Routes& routes, Views& views,
        std::shared_ptr<Observer> observer, Ishiko::Error& error);

    void start() override;
    void stop() override;
    void join() override;

    bool isRunning() const override;

    const Routes& routes() const;
    const Views& views() const;
    AccessLog& accessLog();

private:
    Routes& m_routes;
    Views& m_views;
    boost::asio::io_context m_ioContext;
    BeastListener m_listener;
    std::vector<std::thread> m_threads;
    AccessLog m_accessLog;
};

}

#endif
