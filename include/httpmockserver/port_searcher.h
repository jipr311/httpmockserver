/**
 * \file
 * Implementation of searching for free port of the MockServer heir.
 */

#pragma once

#include <memory>
#include <stdexcept>

namespace httpmock {


/**
 * Return mock server instance or throw the std::runtime_error if server
 * did not start.
 * First bindable port in range <port, port + tryCount> is used.
 * Class HTTPMock is required to have single parameter constructor, passing
 * the port number as an argument.
 */
template <typename HTTPMock>
std::unique_ptr<MockServer> getFirstRunningMockServer(
        unsigned port = 8080, unsigned tryCount = 1000)
{
    for (unsigned p = 0; p < tryCount; p++) {
        try {
            std::unique_ptr<MockServer> server(new HTTPMock(port + p));
            // try to run the server on current port
            server->start();
            return server;
        } catch (const std::runtime_error &) {
            // error occured, try next port number
            continue;
        }
    }
    throw std::runtime_error("MockServer did not come up!");
}


}
