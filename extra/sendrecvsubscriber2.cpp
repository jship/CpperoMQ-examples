// Simple subscriber that consumes 10 Employee messages from the publisher.

#include "sendrecvclassdef.hpp"

int main()
{
    using namespace CpperoMQ;

    Context context;

    SubscribeSocket subscriber(context.createSubscribeSocket());
    subscriber.subscribe(); // Subscribe to all messages.
    subscriber.connect("tcp://localhost:5559");

    for (int i = 0; i < 10; ++i)
    {
        Department oldDept, newDept;
        Employee employee;
        subscriber.receive(oldDept, newDept, employee);

        std::cout << "Received Department Update message " << i << ": ";
        std::cout << oldDept << "|" << newDept << "|" << employee << std::endl;
    }

    return 0;
}
