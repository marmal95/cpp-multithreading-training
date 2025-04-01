#include "../util/print.hpp"
#include <array>
#include <atomic>
#include <thread>

// Is the below code safe?

std::atomic<int> data{0};
std::array<int, 5> shared_data{};

void do_work(int thread_num)
{
    auto val = data.fetch_add(1);
    shared_data[thread_num] = val;
}

int main()
{
    {
        std::jthread th0{do_work, 0};
        std::jthread th1{do_work, 1};
        std::jthread th2{do_work, 2};
        std::jthread th3{do_work, 3};
        std::jthread th4{do_work, 4};
    }

    print(shared_data);
}
