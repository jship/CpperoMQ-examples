// Request-reply service in C++, using CpperoMQ
// Connects REP socket to tcp://localhost:5560
// Expects "Hello" from client, replies with "World"

#include <CpperoMQ/All.hpp>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    using namespace CpperoMQ;
    using namespace std::chrono;

    Context context;

    // Socket to talk to clients.
    ReplySocket responder(context.createReplySocket());
    responder.connect("tcp://localhost:5560");

    while (true)
    {
        // Wait for next request from client.
        IncomingMessage requestMessage;
        responder.receive(requestMessage);

        std::string requestStr(requestMessage.charData(), requestMessage.size());
        std::cout << "Received request: [" << requestStr << "]" << std::endl;
        
        // Do some 'work'.
        std::this_thread::sleep_for(seconds(1));

        // Send reply back to client.
        responder.send(OutgoingMessage("World"));
    }

    return 0;
}

