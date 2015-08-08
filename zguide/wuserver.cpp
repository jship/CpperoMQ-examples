// Weather update server in C++, using CpperoMQ
// Binds PUB socket to tcp://*:5556
// Publishes random weather updates

#include <CpperoMQ/All.hpp>

#include <random>
#include <sstream>

int main()
{
    using namespace CpperoMQ;

    // Prepare our context and publisher
    Context context;
    PublishSocket publisher(context.createPublishSocket());
    publisher.bind("tcp://*:5556");

    // Initialize random number generator
    std::random_device randomDevice;
    std::mt19937 mersenneTwister(randomDevice());

    // Initialize uniform distributions.
    std::uniform_int_distribution<int> distZipCode(1, 99999);
    std::uniform_int_distribution<int> distTemp(1, 215);
    std::uniform_int_distribution<int> distHumidity(1, 50);

    while (true)
    {
        // Get values that will fool the boss
        int zipCode          = distZipCode(mersenneTwister);
        int temperature      = distTemp(mersenneTwister) - 80;
        int relativeHumidity = distHumidity(mersenneTwister) + 10;

        std::ostringstream ss;
        ss << zipCode << " " << temperature << " " << relativeHumidity;

        // Send message to all subscribers
        OutgoingMessage message(ss.str().c_str());
        publisher.send(message);
    }

    return 0;
}
