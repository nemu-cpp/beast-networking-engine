/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#ifndef _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTREQUEST_H_
#define _NEMU_CPP_BEASTCONNECTIONENGINE_BEASTREQUEST_H_

#include <boost/beast/http.hpp>
#include <Nemu/Core.h>

namespace Nemu
{

class BeastRequest : public WebRequest
{
public:
    BeastRequest();
    BeastRequest(boost::beast::http::request<boost::beast::http::string_body>&& request);

    std::string URI() const override;

    const boost::beast::http::request<boost::beast::http::string_body>& request() const;
    boost::beast::http::request<boost::beast::http::string_body>& request();

private:
    boost::beast::http::request<boost::beast::http::string_body> m_request;
};

}

#endif
