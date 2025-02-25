#include "../util/print.hpp"
#include <vector>

int main()
{
    int iterations{};

    const auto threadFunc = [&iterations]()
    {
        for (int i = 0; i < 10'000; i++)
            ++iterations;
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < 4; i++)
        threads.emplace_back(threadFunc);

    for (auto &thread : threads)
        thread.join();

    print("Iterations: ", iterations);
}