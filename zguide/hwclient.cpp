// Hello World client in C++, using CpperoMQ
// Connects REQ socket to tcp://localhost:5555
// Sends "Hello" to server, expects "World" back

#include <CpperoMQ/All.hpp>

#include <iostream>

int main()
{
    using namespace CpperoMQ;

    Context context;
    RequestSocket socket(context.createRequestSocket());

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    // Do 10 requests, waiting each time for a response.
    for (int requestNumber = 0; requestNumber != 10; ++requestNumber)
    {
        std::cout << "Sending Hello " << requestNumber << "..." << std::endl;
        OutgoingMessage request(5, "Hello");
        socket.send(request);

        IncomingMessage reply;
        socket.receive(reply);
        std::cout << "Received World " << requestNumber << std::endl;
    }

    return 0;
}
