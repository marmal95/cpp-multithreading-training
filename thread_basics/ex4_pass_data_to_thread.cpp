#include "../util/print.hpp"

struct Noisy
{
    Noisy() { print("C-tor"); };
    Noisy(const Noisy &) { print("Noisy Copy..."); }
    Noisy(Noisy &&) { print("Noisy Move..."); }
    Noisy &operator=(const Noisy &)
    {
        print("Operator&");
        return *this;
    }
    Noisy &operator=(Noisy &&)
    {
        print("Operator&&");
        return *this;
    }
};

void threadFunction(const Noisy &param)
{
    print(&param);
}

int main()
{
    // The arguments to the thread function are moved or copied by value.
    Noisy noisy{};
    print(&noisy);
    std::jthread thread(threadFunction, noisy);
}