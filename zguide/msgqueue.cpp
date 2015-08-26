// Simple message queuing broker in C++, using CpperoMQ
// Same as request-reply broker but using shared queue proxy

#include <CpperoMQ/All.hpp>

int main()
{
    using namespace CpperoMQ;

    Context context;

    // Socket facing clients.
    RouterSocket frontend(context.createRouterSocket());
    frontend.bind("tcp://*:5559");

    // Socket facing services.
    DealerSocket backend(context.createDealerSocket());
    backend.bind("tcp://*:5560");

    // Start the proxy.
    Proxy proxy;
    proxy.run(frontend, backend);

    return 0;
}
