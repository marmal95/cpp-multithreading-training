#include "../util/print.hpp"
#include <mutex>

using namespace std::chrono_literals;

int main()
{
    std::mutex m1;
    std::mutex m2;

    std::jthread t1([&m1, &m2] {
        print("1. Acquiring m1.");
        std::lock_guard lock1{m1};
        std::this_thread::sleep_for(10ms);
        print("1. Acquiring m2");
        std::lock_guard lock2{m2};
    });

    std::jthread t2([&m1, &m2] {
        print("2. Acquiring m2");
        std::lock_guard lock2{m2};
        std::this_thread::sleep_for(10ms);
        print("2. Acquiring m1");
        std::lock_guard lock1{m1};
    });
}