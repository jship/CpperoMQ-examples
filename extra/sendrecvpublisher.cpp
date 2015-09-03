// Simple publisher that sends an Employee message each second.

#include "sendrecvclassdef.hpp"

#include <thread>

int main()
{
    using namespace CpperoMQ;

    Context context;

    PublishSocket publisher(context.createPublishSocket());
    publisher.bind("tcp://*:5559");

    while (true)
    {
        std::cout << "Sending Employee message..." << std::endl;

        Employee employee(123, 33, "John Doe");
        publisher.send(employee);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
