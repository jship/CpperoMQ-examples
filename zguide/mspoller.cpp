// Reading from multiple sockets, using CpperoMQ
// This version uses zmq_poll()

#include <CpperoMQ/All.hpp>

#include <iostream>

int main()
{
    using namespace CpperoMQ;

    Context context;

    // Connect to task ventilator
    PullSocket receiver(context.createPullSocket());
    receiver.connect("tcp://localhost:5557");

    // Connect to weather server
    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.connect("tcp://localhost:5556");
    subscriber.subscribe("10001 ");

    // Process messages from both sockets
    while (true)
    {
        auto receiverPollItem = isReceiveReady(receiver, [&receiver]()
        {
            // Process task
            IncomingMessage task;
            if (receiver.receive(task))
            {
                std::cout << "Received task" << std::endl;
            }
        });

        auto subscriberPollItem = isReceiveReady(subscriber, [&subscriber]()
        {
            // Process weather update
            IncomingMessage update;
            if (subscriber.receive(update))
            {
                std::cout << "Received update" << std::endl;
            }
        });

        Poller poller;
        poller.poll(receiverPollItem, subscriberPollItem);
    }

    return 0;
}
