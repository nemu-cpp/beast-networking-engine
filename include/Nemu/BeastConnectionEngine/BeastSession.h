/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTSESSION_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTSESSION_H_

#include "BeastRequest.h"
#include "BeastResponseBuilder.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <memory>

namespace Nemu
{

class BeastServer;

class BeastSession : public std::enable_shared_from_this<BeastSession>
{
public:
    BeastSession(BeastServer& server, boost::asio::ip::tcp::socket&& socket);
    void run();

private:
    void handleRequest(BeastRequest&& request);

    void read();
    void onRead(boost::system::error_code ec, size_t bytesTransferred);
    void onWrite(boost::system::error_code ec, size_t bytesTransferred, bool closed);
    void close();

private:
    BeastServer& m_server;
    boost::asio::ip::tcp::socket m_socket;
    //boost::asio::strand<boost::asio::io_context::executor_type> m_strand;
    boost::beast::flat_buffer m_buffer;
    BeastRequest m_request;
    BeastResponseBuilder m_response;
};

}

#endif
