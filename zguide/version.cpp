// Report 0MQ version

#include <CpperoMQ/All.hpp>

#include <iostream>

int main()
{
    using namespace CpperoMQ;

    Version version;

    int major = 0, minor = 0, patch = 0;
    std::tie(major, minor, patch) = version.getTuple();
    // Can alternatively use indivdual getter methods instead of getTuple.

    std::cout << "Current 0MQ version is "
              << major << "."
              << minor << "."
              << patch << "."
              << std::endl;

    return 0;
}
