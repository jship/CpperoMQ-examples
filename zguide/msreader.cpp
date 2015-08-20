// Reading from multiple sockets, using CpperoMQ
// This version uses a simple recv loop

#include <CpperoMQ/All.hpp>

#include <chrono>
#include <thread>

int main()
{
    using namespace CpperoMQ;
    using namespace std::chrono;

    // Prepare our context and sockets
    Context context;

    // Connect to task ventilator
    PullSocket receiver(context.createPullSocket());
    receiver.connect("tcp://localhost:5557");
    receiver.setReceiveTimeout(0);

    // Connect to weather server
    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.connect("tcp://localhost:5556");
    subscriber.subscribe("10001 ");
    subscriber.setReceiveTimeout(0);

    // Process messages from both sockets
    // We prioritize traffic from the task ventilator
    while (true)
    {
        IncomingMessage msg;

        // Process any waiting tasks
        while (receiver.receive(msg))
        {
            // process task
        }
        
        // Process any waiting weather updates
        while (subscriber.receive(msg))
        {
            // process weather update
        }
        
        //  No activity, so sleep for 1 msec
        std::this_thread::sleep_for(milliseconds(1));
    }

    return 0;
}
