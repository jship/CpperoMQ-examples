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
        DepartmentUpdate deptUpdate;
        subscriber.receive(deptUpdate);

        std::cout << "Received Department Update message " << i << ": ";
        std::cout << deptUpdate << std::endl;
    }

    return 0;
}
