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
        std::cout << "Sending Department Update message..." << std::endl;

        Department oldDept(11235, "Staff"), newDept(12358, "Faculty");
        Employee employee(21347, 11, "Edouard Lucas");

        publisher.send(oldDept, newDept, employee);

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}
