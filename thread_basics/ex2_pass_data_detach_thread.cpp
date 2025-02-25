#include "../util/print.hpp"
#include <string>

int main()
{
    {
        const std::string data = "some_data";
        std::thread t{[&]()
                      { print(data); }};
        t.detach();

        // Lambda captures by reference
        // Thread is detached from lifetime of its creator
        // Lifetime of "data" is bound to the lifetime of the invocation context
        // Result: Undefined Behavior - accessing possibly destroyed data
    }
}