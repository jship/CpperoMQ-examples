// Hello World server in C++, using CpperoMQ
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World"

#include <CpperoMQ/All.hpp>

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    using namespace CpperoMQ;

    Context context;

    ReplySocket socket(context.createReplySocket());
    socket.bind("tcp://*:5555");

    while (true)
    {
        IncomingMessage request;

        // Wait for next request from client.
        socket.receive(request);
        std::cout << "Received Hello" << std::endl;

        // Do some 'work'.
    	std::this_thread::sleep_for(std::chrono::seconds(1));;

        // Send reply back to client.
        OutgoingMessage reply("World");
        socket.send(reply);
    }

    return 0;
}
