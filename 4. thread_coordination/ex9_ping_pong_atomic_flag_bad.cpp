#include "../util/print.hpp"
#include <atomic>
#include <thread>

std::atomic<int> counter{};
std::atomic_flag pingSent = ATOMIC_FLAG_INIT; // Initially clear

constexpr int limit = 10;

void runPing()
{
    for (int i = 0; i < limit; ++i)
    {
        counter++;
        print("Ping: ", counter);

        pingSent.test_and_set(); // Mark ping as sent
        pingSent.notify_one();   // Notify pong

        // Problematic window

        pingSent.wait(true); // Wait until pong clears the flag
    }
}

void runPong()
{
    for (int i = 0; i < limit; ++i)
    {
        pingSent.wait(false); // Wait until ping is sent

        print("Pong: ", counter);

        pingSent.clear();      // Mark ping as processed
        pingSent.notify_one(); // Notify ping
    }
}

int main()
{
    std::jthread pingThread(runPing);
    std::jthread pongThread(runPong);
}
