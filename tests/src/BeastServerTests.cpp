/*
    Copyright (c) 2019-2022 Xavier Leclercq
    Released under the MIT License
    See https://github.com/nemu-cpp/beast-connection-engine/blob/main/LICENSE.txt
*/

#include "BeastServerTests.h"
#include "helpers/TestRoutes.h"
#include "helpers/TestServerObserver.h"
#include "Nemu/BeastConnectionEngine/BeastServer.h"
#include <Ishiko/HTTP/HTTPClient.hpp>
#include <fstream>
#include <thread>

using namespace boost::filesystem;
using namespace Ishiko::HTTP;
using namespace Ishiko::Tests;

BeastServerTests::BeastServerTests(const TestNumber& number, const TestContext& context)
    : TestSequence(number, "BeastServer tests", context)
{
    append<HeapAllocationErrorsTest>("Creation test 1", CreationTest1);
    append<HeapAllocationErrorsTest>("start test 1", StartTest1);
    append<HeapAllocationErrorsTest>("start test 2", StartTest2);
    append<HeapAllocationErrorsTest>("start test 3", StartTest3);
    append<FileComparisonTest>("Request test 1", RequestTest1);
    append<FileComparisonTest>("Request test 2", RequestTest2);
    append<HeapAllocationErrorsTest>("Request test 3", RequestTest3);
    append<HeapAllocationErrorsTest>("Request test 4", RequestTest4);
    append<HeapAllocationErrorsTest>("Request test 5", RequestTest5);
}

void BeastServerTests::CreationTest1(Test& test)
{
    Nemu::Routes routes;
    Nemu::Views views;
    std::shared_ptr<Nemu::Server::Observer> observer;
    Ishiko::Error error;
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_FAIL_IF(error);
    ISHIKO_PASS();
}

void BeastServerTests::StartTest1(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();
    server.stop();
    server.join();

    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 0);
    ISHIKO_FAIL_IF_NEQ(observer->connectionEvents().size(), 0);
    ISHIKO_PASS();
}

void BeastServerTests::StartTest2(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(16, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();
    server.stop();
    server.join();

    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 0);
    ISHIKO_FAIL_IF_NEQ(observer->connectionEvents().size(), 0);
    ISHIKO_PASS();
}

void BeastServerTests::StartTest3(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(128, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();
    server.stop();
    server.join();

    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 0);
    ISHIKO_FAIL_IF_NEQ(observer->connectionEvents().size(), 0);
    ISHIKO_PASS();
}

void BeastServerTests::RequestTest1(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputPath("BeastTests/BeastServerTests_RequestTest1.txt"));
    path referencePath(test.context().getReferenceDataPath("BeastTests/BeastServerTests_RequestTest1.txt"));

    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();

    std::ofstream responseFile(outputPath.string());
    HTTPClient::Get("127.0.0.1", 8088, "/", responseFile, error);
    responseFile.close();

    server.stop();
    server.join();

    ISHIKO_ABORT_IF(error);

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();

    ISHIKO_FAIL_IF_NEQ(events.size(), 2);
    ISHIKO_FAIL_IF_NEQ(std::get<0>(events[0]), TestServerObserver::eConnectionOpened);
    ISHIKO_FAIL_IF_NEQ(std::get<1>(events[0]), &server);
    ISHIKO_FAIL_IF_NEQ(std::get<2>(events[0]).substr(0, 10), "127.0.0.1:");
    ISHIKO_FAIL_IF_NEQ(std::get<0>(events[1]), TestServerObserver::eConnectionClosed);
    ISHIKO_FAIL_IF_NEQ(std::get<1>(events[1]), &server);
    ISHIKO_FAIL_IF_NEQ(std::get<2>(events[0]), std::get<2>(events[1]));
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 1);
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes()[0], "/");

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_PASS();
}

void BeastServerTests::RequestTest2(FileComparisonTest& test)
{
    path outputPath(test.context().getTestOutputPath("BeastTests/BeastServerTests_RequestTest2.txt"));
    path referencePath(test.context().getReferenceDataPath("BeastTests/BeastServerTests_RequestTest2.txt"));

    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();

    std::ofstream responseFile(outputPath.string());
    HTTPClient::Get("127.0.0.1", 8088, "/", responseFile, error);
    HTTPClient::Get("127.0.0.1", 8088, "/", responseFile, error);
    responseFile.close();

    server.stop();
    server.join();

    ISHIKO_ABORT_IF(error);

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();
    ISHIKO_FAIL_IF_NEQ(events.size(), 4);
    ISHIKO_FAIL_IF_NEQ(std::get<0>(events[0]), TestServerObserver::eConnectionOpened);
    ISHIKO_FAIL_IF_NEQ(std::get<1>(events[0]), &server);
    ISHIKO_FAIL_IF_NEQ(std::get<2>(events[0]).substr(0, 10), "127.0.0.1:");
    ISHIKO_FAIL_IF_NEQ(std::get<0>(events[1]), TestServerObserver::eConnectionClosed);
    ISHIKO_FAIL_IF_NEQ(std::get<1>(events[1]), &server);
    ISHIKO_FAIL_IF_NEQ(std::get<2>(events[0]), std::get<2>(events[1]));
    ISHIKO_FAIL_IF_NEQ(std::get<0>(events[2]), TestServerObserver::eConnectionOpened);
    ISHIKO_FAIL_IF_NEQ(std::get<1>(events[2]), &server);
    ISHIKO_FAIL_IF_NEQ(std::get<2>(events[2]).substr(0, 10), "127.0.0.1:");
    ISHIKO_FAIL_IF_NEQ(std::get<0>(events[3]), TestServerObserver::eConnectionClosed);
    ISHIKO_FAIL_IF_NEQ(std::get<1>(events[3]), &server);
    ISHIKO_FAIL_IF_NEQ(std::get<2>(events[2]), std::get<2>(events[3]));
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 2);
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes()[0], "/");
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes()[1], "/");
    
    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHIKO_PASS();
}

void BeastServerTests::RequestTest3(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();

    for (size_t i = 0; i < 100; ++i)
    {
        std::stringstream response;
        HTTPClient::Get("127.0.0.1", 8088, "/", response, error);

        ISHIKO_ABORT_IF(error);
    }

    server.stop();
    server.join();

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();

    ISHIKO_FAIL_IF_NEQ(events.size(), 200);
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 100);
    ISHIKO_PASS();
}

void BeastServerTests::RequestTest4(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(1, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 4; ++i)
    {
        threads.push_back(std::thread(
            []()
        {
            for (size_t i = 0; i < 25; ++i)
            {
                Ishiko::Error error(0);
                std::stringstream response;
                HTTPClient::Get("127.0.0.1", 8088, "/", response, error);
            }
        }));
    }
    for (std::thread& t : threads)
    {
        t.join();
    }

    server.stop();
    server.join();

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();

    ISHIKO_FAIL_IF_NEQ(events.size(), 200);
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 100);
    ISHIKO_PASS();
}

void BeastServerTests::RequestTest5(Test& test)
{
    TestRoutes routes;
    Nemu::Views views;
    std::shared_ptr<TestServerObserver> observer = std::make_shared<TestServerObserver>();
    Ishiko::Error error;
    Nemu::BeastServer server(16, "127.0.0.1", 8088, routes, views, observer, error);

    ISHIKO_ABORT_IF(error);

    server.start();

    std::vector<std::thread> threads;
    for (size_t i = 0; i < 4; ++i)
    {
        threads.push_back(std::thread(
            []()
        {
            for (size_t i = 0; i < 25; ++i)
            {
                Ishiko::Error error(0);
                std::stringstream response;
                HTTPClient::Get("127.0.0.1", 8088, "/", response, error);
            }
        }));
    }
    for (std::thread& t : threads)
    {
        t.join();
    }

    server.stop();
    server.join();

    const std::vector<std::tuple<TestServerObserver::EEventType, const Nemu::Server*, std::string>>& events =
        observer->connectionEvents();

    ISHIKO_FAIL_IF_NEQ(events.size(), 200);
    ISHIKO_FAIL_IF_NEQ(routes.visitedRoutes().size(), 100);
    ISHIKO_PASS();
}
