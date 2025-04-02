#include "../util/print.hpp"
#include <condition_variable>
#include <mutex>
#include <thread>

std::mutex mtx;
std::condition_variable cv;
int counter = 0;
bool pingSent = false;

constexpr int limit = 10;

void runPing()
{
    for (int i = 0; i < limit; ++i)
    {
        std::unique_lock<std::mutex> lock(mtx);
        counter++;
        print("Ping: ", counter);

        pingSent = true;
        cv.notify_one(); // Notify Pong

        cv.wait(lock, [] { return !pingSent; }); // Wait until Pong clears
    }
}

void runPong()
{
    for (int i = 0; i < limit; ++i)
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [] { return pingSent; }); // Wait for Ping

        print("Pong: ", counter);

        pingSent = false;
        cv.notify_one(); // Notify Ping
    }
}

int main()
{
    std::jthread pingThread(runPing);
    std::jthread pongThread(runPong);
}
