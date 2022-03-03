/*
    Copyright (c) 2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastSession.h"
#include "BeastServer.h"
#include <boost/asio/bind_executor.hpp>

namespace Nemu
{

BeastSession::BeastSession(BeastServer& server, boost::asio::ip::tcp::socket&& socket)
    : m_server(server), m_socket(std::move(socket))/*, m_strand(m_socket.get_executor())*/, m_response(server.views())
{
    boost::asio::make_strand(m_socket.get_executor());
}

void BeastSession::run()
{
    read();
}

void BeastSession::handleRequest(BeastRequest&& request)
{
    m_response.initialize(request.request());

    const Route& route = m_server.routes().match(request.URI());
    route.runHandler(request, m_response);
    m_response.response().prepare_payload();

    std::string requestLine = request.request().method_string().to_string() + " "
        + request.request().target().to_string();
    if (request.request().version() == 11)
    {
        requestLine += " HTTP/1.1";
    }
    else
    {
        requestLine += " HTTP/1.0";
    }
    
    auto handler = boost::asio::bind_executor(m_strand,
        std::bind(&BeastSession::onWrite, shared_from_this(), std::placeholders::_1, std::placeholders::_2,
            m_response.response().need_eof()));

    m_server.accessLog().log(m_socket.remote_endpoint().address().to_string(), requestLine,
        m_response.response().result_int(), m_response.response().payload_size().value());

    boost::beast::http::async_write(m_socket, m_response.response(), handler);
}

void BeastSession::read()
{
    m_request = BeastRequest();

    auto handler = boost::asio::bind_executor(m_strand,
        std::bind(&BeastSession::onRead, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
    boost::beast::http::async_read(m_socket, m_buffer, m_request.request(), handler);
}

void BeastSession::onRead(boost::system::error_code ec, size_t bytesTransferred)
{
    if (!ec)
    {
        handleRequest(std::move(m_request));
    }
    else if (ec == boost::beast::http::error::end_of_stream)
    {
        return close();
    }
}

void BeastSession::onWrite(boost::system::error_code ec, size_t bytesTransferred, bool closed)
{
    if (closed)
    {
        close();
    }

    m_response.reset();

    read();
}

void BeastSession::close()
{
    boost::system::error_code ec;
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send, ec);

    const std::string& sourceAddress = m_socket.remote_endpoint().address().to_string() + ":" +
        std::to_string(m_socket.remote_endpoint().port());
    m_server.observers().notify(&Server::Observer::onConnectionClosed, m_server, sourceAddress);
}

}
