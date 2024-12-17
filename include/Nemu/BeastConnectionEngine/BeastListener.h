/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTLISTENER_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTLISTENER_H_

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <Ishiko/Errors.hpp>

namespace Nemu
{

class BeastServer;

class BeastListener
{
public:
    BeastListener(BeastServer& server, boost::asio::io_context& ioContext, boost::asio::ip::tcp::endpoint endpoint,
        Ishiko::Error& error);

    void run();

private:
    void accept();
    void onAccept(boost::system::error_code ec);

private:
    BeastServer& m_server;
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::ip::tcp::socket m_socket;
};

}

#endif
