// Simple subscriber that consumes 10 messages from the publisher.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <string>

int main()
{
    using namespace CpperoMQ;

    Context context;

    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.subscribe(); // Subscribe to all messages.
    subscriber.connect("tcp://localhost:5559");

    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Received message " << i << ": ";

        // 'receive' treats all of its parameters as the parts of a single,
        // multipart message.
        IncomingMessage inMsg1, inMsg2, inMsg3, inMsg4, inMsg5;
        subscriber.receive(inMsg1, inMsg2, inMsg3, inMsg4, inMsg5);

        // In many cases, it is undesirable to have to know up-front how many
        // message parts are expected when receiving on a socket.  Additional
        // examples are provided that cleanly tackle the problem.

        std::cout << std::string(inMsg1.charData(), inMsg1.size()) << "|"
                  << std::string(inMsg2.charData(), inMsg2.size()) << "|"
                  << std::string(inMsg3.charData(), inMsg3.size()) << "|"
                  << std::string(inMsg4.charData(), inMsg4.size()) << "|"
                  << std::string(inMsg5.charData(), inMsg5.size()) << std::endl;
    }

    return 0;
}
