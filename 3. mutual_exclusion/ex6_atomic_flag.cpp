#include "../util/print.hpp"
#include <mutex>

class mutex
{
  public:
    void lock() noexcept
    {
        while (flag.test_and_set())
            flag.wait(true);
        // W/w-o wait
        // Wait without true?
    }

    bool try_lock() noexcept { return !flag.test_and_set(); }

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