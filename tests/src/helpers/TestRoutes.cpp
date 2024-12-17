/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "TestRoutes.hpp"

TestRoutes::TestRoutes()
    : m_visitedRoutes(std::make_shared<std::vector<std::string>>())
{
    setDefaultRoute(Nemu::Route("",
        [](const Nemu::WebRequest& request, Nemu::WebResponseBuilder& response, void* handlerData)
        {
            response.setStatus(404);

            TestRoutes* routes = reinterpret_cast<TestRoutes*>(handlerData);
            std::lock_guard<std::mutex> guard(routes->m_visitedRoutesMutex);
            routes->m_visitedRoutes->push_back(request.URI());
        },
        std::shared_ptr<TestRoutes>(this, [](TestRoutes*) {})));
}

const std::vector<std::string>& TestRoutes::visitedRoutes() const
{
    return *m_visitedRoutes;
}
