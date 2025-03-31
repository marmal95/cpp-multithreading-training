#include "../util/print.hpp"
#include <thread>

int main()
{
    // What is the output of the below code?
    // What are the problems with the below code?
    // - Does this code have race condition?
    // - Does this code have Undefined Behavior?
    // - Does this code may produce "Garbabe" values?

    constexpr auto numOfThreads = 100;
    int counter{};

    {
        std::vector<std::jthread> threads;
        threads.reserve(numOfThreads);

        for (int threadId = 1; threadId <= numOfThreads; threadId++)
        {
            threads.emplace_back([&counter, threadId]() { counter++; });
        }
    }

    print("Counter: ", counter);
}