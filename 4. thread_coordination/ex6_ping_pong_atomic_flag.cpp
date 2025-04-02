#include "../util/print.hpp"
#include <atomic>
#include <thread>

std::atomic<int> counter{};
std::atomic_flag pingSent{};

constexpr int limit = 10;

void runPing()
{
    while (counter < limit)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        while (pingSent.test());

        counter++;
        print("Ping: ", counter);

        pingSent.test_and_set(); // Mark ping as sent
    }
}

void runPong()
{
    while (counter < limit)
    {
        while (!pingSent.test());

        print("Pong: ", counter);

        pingSent.clear(); // Mark ping as processed
    }
}

int main()
{
    std::jthread pingThread(runPing);
    std::jthread pongThread(runPong);
}
