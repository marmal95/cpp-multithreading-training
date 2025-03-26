#include "../util/print.hpp"

struct Noisy
{
    Noisy() { print("C-tor"); };
    Noisy(const Noisy&) { print("Noisy Copy..."); }
    Noisy(Noisy&&) { print("Noisy Move..."); }
    Noisy& operator=(const Noisy&)
    {
        print("Operator&");
        return *this;
    }
    Noisy& operator=(Noisy&&)
    {
        print("Operator&&");
        return *this;
    }
};

void threadFunction(const Noisy& param) {}

int main()
{
    // The arguments to the thread function are moved or copied by value.
    // If a reference argument needs to be passed to the thread function, it has to be wrapped with std::ref.
    Noisy noisy{};
    std::jthread thread(threadFunction, noisy);
}