// Weather update client in C++, using CpperoMQ
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode

#include <CpperoMQ/All.hpp>

#include <iostream>
#include <sstream>

int main(int argc, char *argv[])
{
    using namespace CpperoMQ;

    std::cout << "Collecting updates from weather server..." << std::endl;

    // Prepare context and socket to talk to server
    Context context;
    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.connect("tcp://localhost:5556");

    // Subscribe to zip code, default is NYC, 10001
    const char* filter = (argc > 1) ? argv[1] : "10001 ";
    subscriber.subscribe(filter);

    // Process 100 updates
    int updateNumber = 0;
    long totalTemp = 0;

    for (updateNumber = 0; updateNumber < 100; updateNumber++)
    {
        IncomingMessage update;
        subscriber.receive(update);

        int zipCode = 0, temperature = 0, relativeHumidity = 0;
        std::istringstream iss(std::string(update.charData(), update.size()));
        iss >> zipCode >> temperature >> relativeHumidity ;

        totalTemp += temperature;
    }

    std::cout << "Average temperature for zipCode '"<< filter
              << "' was "<<(int) (totalTemp / updateNumber) <<"F"
              << std::endl;

    return 0;
}
