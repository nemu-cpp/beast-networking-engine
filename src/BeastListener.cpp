/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastListener.h"
#include "BeastServer.h"
#include "BeastSession.h"

namespace Nemu
{

BeastListener::BeastListener(BeastServer& server, boost::asio::io_context& ioContext,
    boost::asio::ip::tcp::endpoint endpoint, Ishiko::Error& error)
    : m_server(server), m_acceptor(ioContext), m_socket(ioContext)
{
    boost::system::error_code ec;
    m_acceptor.open(endpoint.protocol(), ec);
    if (ec)
    {
        // TODO: appropriate error
        Fail(error, ErrorCategory::eGeneric, ec.message(), __FILE__, __LINE__);
        return;
    }
    m_acceptor.set_option(boost::asio::socket_base::reuse_address(true), ec);
    if (ec)
    {
        m_acceptor.close();
        // TODO: appropriate error
        Fail(error, ErrorCategory::eGeneric, ec.message(), __FILE__, __LINE__);
        return;
    }
    m_acceptor.bind(endpoint, ec);
    if (ec)
    {
        m_acceptor.close();
        // TODO: appropriate error
        Fail(error, ErrorCategory::eGeneric, ec.message(), __FILE__, __LINE__);
        return;
    }
    m_acceptor.listen(boost::asio::socket_base::max_listen_connections, ec);
    if (ec)
    {
        m_acceptor.close();
        // TODO: appropriate error
        Fail(error, ErrorCategory::eGeneric, ec.message(), __FILE__, __LINE__);
        return;
    }
}

void BeastListener::run()
{
    if (m_acceptor.is_open())
    {
        accept();
    }
}

void BeastListener::accept()
{
    m_acceptor.async_accept(m_socket, std::bind(&BeastListener::onAccept, this, std::placeholders::_1));
}

void BeastListener::onAccept(boost::system::error_code ec)
{
    if (!ec)
    {
        const std::string& sourceAddress = m_socket.remote_endpoint().address().to_string() + ":" +
            std::to_string(m_socket.remote_endpoint().port());
        m_server.observers().notify(&Server::Observer::onConnectionOpened, m_server, sourceAddress);
        std::shared_ptr<BeastSession> session = std::make_shared<BeastSession>(m_server, std::move(m_socket));
        session->run();
    }

    accept();
}

}
