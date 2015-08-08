// Task ventilator in C++, using CpperoMQ
// Binds PUSH socket to tcp://localhost:5557
// Sends batch of tasks to workers via that socket

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <random>
#include <sstream>
#include <thread>

int main()
{
    using namespace CpperoMQ;

    Context context;

    // Socket to send messages on
    PushSocket sender(context.createPushSocket());
    sender.bind("tcp://*:5557");
    
    // Socket to send start of batch message on
    PushSocket sink(context.createPushSocket());
    sink.connect("tcp://localhost:5558");

    std::cout << "Press Enter when the workers are ready: " << std::endl;
    getchar();
    std::cout << "Sending tasks to workers...\n" << std::endl;

    // The first message is "0" and signals start of batch
    sink.send(OutgoingMessage("0"));

    // Initialize random number generator
    std::random_device randomDevice;
    std::mt19937 mersenneTwister(randomDevice());
    
    // Initialize uniform distributions.
    std::uniform_int_distribution<int> distWorkloadTime(1, 100);

    // Send 100 tasks
    int totalMsec = 0; //  Total expected cost in msecs
    for (int taskNumber = 0; taskNumber < 100; ++taskNumber)
    {
        int workload;

        // Random workload from 1 to 100msecs
        workload = distWorkloadTime(mersenneTwister);
        totalMsec += workload;

        std::ostringstream ss;
        ss << workload;

        sender.send(OutgoingMessage(ss.str().c_str()));
    }

    std::cout << "Total expected cost: " << totalMsec << " msec" << std::endl;
    return 0;
}
