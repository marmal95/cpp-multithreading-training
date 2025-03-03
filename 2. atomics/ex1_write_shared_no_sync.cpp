#include "../util/print.hpp"

int main()
{
    int counter{};
    {
        auto t1 = std::jthread{[&counter]() { counter = 1; }};
        auto t2 = std::jthread{[&counter]() { counter = 2; }};
        auto t3 = std::jthread{[&counter]() { counter = 3; }};
    }
    print("Counter: ", counter);
}
