// Simple pub/sub broker.

#include <CpperoMQ/All.hpp>

int main()
{
    using namespace CpperoMQ;

    Context context;

    ExtendedSubscribeSocket frontend(context.createExtendedSubscribeSocket());
    frontend.bind("tcp://*:5559");

    ExtendedPublishSocket backend(context.createExtendedPublishSocket());
    backend.bind("tcp://*:5560");

    SubscribeSocket control(context.createSubscribeSocket());
    control.subscribe();
    control.connect("tcp://localhost:5561");

    Proxy proxy;
    proxy.setControlSocket(control);
    proxy.run(frontend, backend);

    return 0;
}
