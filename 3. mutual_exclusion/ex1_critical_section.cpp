#include "../util/print.hpp"
#include <vector>

std::vector<int> v{};

// What's the output of this code?
// What's wrong with this code?
// How to fix this code?
// What happens after fix when push_back throws exception?

void addData(int value)
{
    // [...]
    v.push_back(value);
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

    for (int i = 0; i < 10; i++) threads.emplace_back(threadFunc);

    for (auto& thread : threads) thread.join();

    print("vector size(): ", v.size());
}