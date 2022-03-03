/*
    Copyright (c) 2019 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastResponseBuilder.h"

namespace Nemu
{

BeastResponseBuilder::BeastResponseBuilder(const Views& views)
    : WebResponseBuilder(views)
{
}

void BeastResponseBuilder::initialize(const boost::beast::http::request<boost::beast::http::string_body>& request)
{
    m_response = boost::beast::http::response<boost::beast::http::string_body>();
    m_response.keep_alive(request.keep_alive());
}

void BeastResponseBuilder::reset()
{
    m_response = boost::beast::http::response<boost::beast::http::string_body>();
}

void BeastResponseBuilder::setStatus(unsigned int status)
{
    m_response.result(status);
}

std::string& BeastResponseBuilder::body()
{
    return m_response.body();
}

boost::beast::http::response<boost::beast::http::string_body>& BeastResponseBuilder::response()
{
    return m_response;
}

}
