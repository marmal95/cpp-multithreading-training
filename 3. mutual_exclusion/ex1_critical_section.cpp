#include "../util/print.hpp"
#include <vector>

std::vector<int> v{};

void addData(int value)
{
    // [...]
    v.push_back(value); // Deadlock when exception thrown
    // [...]
}

int main()
{
    const auto threadFunc = []() {
        for (int i = 0; i < 1'000; i++)
        {
            addData(i);
        }
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < 10; i++)
        threads.emplace_back(threadFunc);

    for (auto& thread : threads)
        thread.join();

    print("vector size(): ", v.size());
}