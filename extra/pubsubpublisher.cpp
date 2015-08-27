// Simple publisher that sends 10 multipart messages to the pub/sub queue.

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <string>
#include <thread>

int main()
{
    using namespace CpperoMQ;

    Context context;

    PublishSocket publisher(context.createPublishSocket());
    publisher.connect("tcp://localhost:5559");
    
    // Allow time for ZMQ to establish a connection. Don't do this in
    // real software!
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    for (int i = 0; i < 10; ++i)
    {
        std::cout << "Sending message " << i << std::endl;

        publisher.send( OutgoingMessage("This")
                      , OutgoingMessage("is")
                      , OutgoingMessage("a")
                      , OutgoingMessage("multipart")
                      , OutgoingMessage("message") );

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
