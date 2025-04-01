#include "../util/print.hpp"

class mutex
{
  public:
    void lock() noexcept
    {
        // Why is .wait(true) needed here?
        // Otherwise thread will keep calling test_and_set in tight loop (spinlock/active wait)
        // Causes high CPU usage (wastes CPU)
        //
        // Wait - allows tread to sleep (block and wait) until notified -> efficient long waits
        // Reduces CPU consunption
        //
        //
        // Why is boolean (true) needed?
        // 1. Avoiding the "Lost Wakeup" Problem

        // Thread A calls lock():
        //   flag.test_and_set() succeeds (since flag was initially false).
        //   Thread A enters the critical section.

        // Thread B calls lock() while Thread A is in the critical section:
        //   flag.test_and_set() fails (flag is already true).
        //   Thread B calls flag.wait(), going to sleep.

        // Thread A calls unlock():
        //   flag.clear() sets flag = false.
        //   flag.notify_one() wakes one waiting thread.

        // Thread B missed the wakeup!
        //   There is a tiny window where Thread B might have not actually started waiting yet when Thread A called
        //   notify_one().
        //   Since Thread B was not in the waiting state when notify_one() was called, it never receives
        //   the wakeup signal. Thread B is now sleeping forever, thinking it is still waiting for flag to change.

        while (flag.test_and_set())
            flag.wait(true);
    }

    bool try_lock() noexcept
    {
        return !flag.test_and_set();
    }

    void unlock() noexcept
    {
        flag.clear();
        flag.notify_one();
    }

  private:
    std::atomic_flag flag{};
};

int main()
{
    int counter{};
    mutex m{};

    {
        std::vector<std::jthread> v;
        auto operation = [&counter, &m]() {
            for (int iter = 0; iter < 10'000; iter++)
            {
                m.lock();
                ++counter;
                m.unlock();
            }
        };
        for (int i = 0; i < 10; i++)
        {
            v.emplace_back(operation);
        }
    }

    print("Counter: ", counter);
}