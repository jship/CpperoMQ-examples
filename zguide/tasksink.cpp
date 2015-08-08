// Task sink in C++, using CpperoMQ
// Binds PULL socket to tcp://localhost:5558
// Collects results from workers via that socket

#include <CpperoMQ/All.hpp>

#include <chrono>
#include <iostream>

int main()
{
    using namespace CpperoMQ;
    using namespace std::chrono;

    // Prepare our context and socket
    Context context;
    PullSocket receiver(context.createPullSocket());
	receiver.bind("tcp://*:5558");

    // Wait for start of batch
    IncomingMessage message;
    receiver.receive(message);

    // Start our clock now
    auto startTime = high_resolution_clock::now();

    // Process 100 confirmations
    for (int taskNumber = 0; taskNumber < 100; ++taskNumber)
    {
        receiver.receive(message);

        if ((taskNumber / 10) * 10 == taskNumber)
        {
            std::cout << ":";
        }
        else
        {
            std::cout << ".";
        }
        
        std::cout << std::flush;
    }
    std::cout << std::endl;
    
    auto endTime = high_resolution_clock::now();

    auto msec = duration_cast<milliseconds>(endTime - startTime).count();
    std::cout << "Total elapsed time: " << msec << " msec"
              << std::endl;

    return 0;
}
