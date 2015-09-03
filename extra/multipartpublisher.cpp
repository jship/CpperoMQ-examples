// Simple publisher that sends a multipart message each second.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <thread>

int main()
{
    using namespace CpperoMQ;

    Context context;

    PublishSocket publisher(context.createPublishSocket());
    publisher.bind("tcp://*:5559");

    while (true)
    {
        std::cout << "Sending multipart message..." << std::endl;

        // 'send' treats all of its parameters as a single, multipart message.
        // No need to build up a list of message parts before-hand.
        publisher.send( OutgoingMessage("This")
                      , OutgoingMessage("is")
                      , OutgoingMessage("a")
                      , OutgoingMessage("multipart")
                      , OutgoingMessage("message") );

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
