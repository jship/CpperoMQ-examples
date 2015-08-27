// Simple controller to allow pause, resume, and termination of pub/sub queue.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <string>

int main()
{
    using namespace CpperoMQ;

    Context context;

    PublishSocket controller(context.createPublishSocket());
    controller.bind("tcp://*:5561");

    std::string command;
    while (std::getline(std::cin, command) && command[0] != 'q')
    {
        controller.send(OutgoingMessage(command.c_str()));
    }

    return 0;
}
