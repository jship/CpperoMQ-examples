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
        Employee employee;
        subscriber.receive(employee);

        std::cout << "Received Employee message " << i << ": ";
        std::cout << employee << std::endl;
    }

    return 0;
}
