// Simple request-reply broker in C++, using CpperoMQ

#include <CpperoMQ/All.hpp>

int main()
{
    using namespace CpperoMQ;

    // Prepare our context and sockets.
    Context context;
    RouterSocket frontend(context.createRouterSocket());
    DealerSocket backend(context.createDealerSocket());

    frontend.bind("tcp://*:5559");
    backend.bind("tcp://*:5560");

    auto frontendPollItem = isReceiveReady(frontend, [&frontend, &backend]()
    {
        bool more = true;

        while (more)
        {
            // Process all parts of the message.
            IncomingMessage inMsg;
            inMsg.receive(frontend, more);

            OutgoingMessage outMsg(inMsg.size(), inMsg.data());
            outMsg.send(backend, more);
        }
    });

    auto backendPollItem = isReceiveReady(backend, [&frontend, &backend]()
    {
        bool more = true;

        while (more)
        {
            // Process all parts of the message.
            IncomingMessage inMsg;
            inMsg.receive(backend, more);

            OutgoingMessage outMsg(inMsg.size(), inMsg.data());
            outMsg.send(frontend, more);
        }
    });

    Poller poller;
    while (true)
    {
        poller.poll(frontendPollItem, backendPollItem);
    }

    return 0;
}
