// Simple subscriber that consumes 10 messages from the pub/sub queue.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <string>

int main()
{
    using namespace CpperoMQ;

    Context context;

    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.subscribe(); // Subscribe to all messages.
    subscriber.connect("tcp://localhost:5560");

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Received message " << i << ": ";

        IncomingMessage inMsg1, inMsg2, inMsg3, inMsg4, inMsg5;
        subscriber.receive(inMsg1, inMsg2, inMsg3, inMsg4, inMsg5);

        std::cout << std::string(inMsg1.charData(), inMsg1.size()) << "|"
                  << std::string(inMsg2.charData(), inMsg2.size()) << "|"
                  << std::string(inMsg3.charData(), inMsg3.size()) << "|"
                  << std::string(inMsg4.charData(), inMsg4.size()) << "|"
                  << std::string(inMsg5.charData(), inMsg5.size()) << std::endl;
    }

    return 0;
}
