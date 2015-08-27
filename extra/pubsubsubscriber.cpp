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

        std::string curFrame;
        bool more = true;

        while (more)
        {
            IncomingMessage inMsg;
            inMsg.receive(subscriber, more);
        
            std::cout << std::string(inMsg.charData(), inMsg.size());

            if (more)
            {
                std::cout << "|";
            }
        }

        std::cout << std::endl;
    }

    return 0;
}
