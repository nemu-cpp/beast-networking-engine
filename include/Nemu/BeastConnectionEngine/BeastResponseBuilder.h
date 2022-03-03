/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/


#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTRESPONSEBUILDER_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTRESPONSEBUILDER_H_

#include <boost/beast/http.hpp>
#include <Nemu/Core.h>

namespace Nemu
{

class BeastResponseBuilder : public WebResponseBuilder
{
public:
    BeastResponseBuilder(const Views& views);
    void initialize(const boost::beast::http::request<boost::beast::http::string_body>& request);
    void reset();

    void setStatus(unsigned int status) override;
    std::string& body() override;

    boost::beast::http::response<boost::beast::http::string_body>& response();

private:
    boost::beast::http::response<boost::beast::http::string_body> m_response;
};

}

#endif
