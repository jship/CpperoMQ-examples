// Task worker in C++, using CpperoMQ
// Connects PULL socket to tcp://localhost:5557
// Collects workloads from ventilator via that socket
// Connects PUSH socket to tcp://localhost:5558
// Sends results to sink via that socket

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <sstream>
#include <thread>

int main()
{
    using namespace CpperoMQ;
    using namespace std::chrono;

    Context context;

    // Socket to receive messages on
    PullSocket receiver(context.createPullSocket());
    receiver.connect("tcp://localhost:5557");

    // Socket to send messages to
    PushSocket sender(context.createPushSocket());
    sender.connect("tcp://localhost:5558");

    // Process tasks forever
    while (true)
    {
        IncomingMessage workloadMsg;
        receiver.receive(workloadMsg);

        std::string workloadStr( static_cast<const char*>(workloadMsg.data())
                               , workloadMsg.size() );
        
        // Show progress
		std::cout << workloadStr << "." << std::flush;

        std::istringstream iss(workloadStr);
        int workload = 0;
        iss >> workload;

        // Do the work
        std::this_thread::sleep_for(milliseconds(workload));

        // Send results to sink
        sender.send(OutgoingMessage());
    }

    return 0;
}
