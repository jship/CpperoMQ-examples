// Request-reply client in C++, using CpperoMQ
// Connects REQ socket to tcp://localhost:5559
// Sends "Hello" to server, expects "World" back

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <string>

int main()
{
    using namespace CpperoMQ;

    Context context;

    // Socket to talk to server.
    RequestSocket requester(context.createRequestSocket());
    requester.connect("tcp://localhost:5559");

    for (int request = 0; request < 10; ++request)
    {
        requester.send(OutgoingMessage("Hello"));

        IncomingMessage replyMessage;
        requester.receive(replyMessage);

        std::string replyStr(replyMessage.charData(), replyMessage.size());
        std::cout << "Received reply " << request
                  << " [" << replyStr << "]" << std::endl;
    }

    return 0;
}
