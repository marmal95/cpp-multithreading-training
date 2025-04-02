#include "../util/print.hpp"
#include <vector>

// What is the output of the below code?
// What are the problems with the below code?
// - Does this code have race condition?
// - Does this code have Undefined Behavior?

int main()
{
    constexpr auto numOfThreads = 100;
    std::string text{"Some text"};

    const auto threadFunc = [&text]() { print(text); };

    std::vector<std::jthread> threads;
    threads.reserve(numOfThreads);

    for (int threadId = 1; threadId <= numOfThreads; threadId++) threads.emplace_back(threadFunc);
}