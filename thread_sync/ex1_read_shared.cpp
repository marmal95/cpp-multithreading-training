#include "../util/print.hpp"
#include <vector>

int main()
{
    std::string text{"Some text"};

    const auto threadFunc = [&text]()
    {
        print(text);
    };

    std::vector<std::jthread> threads;

    for (int i = 0; i < 12; i++)
        threads.emplace_back(threadFunc);
}