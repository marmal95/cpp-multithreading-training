#include "../util/print.hpp"

int main()
{
    // std::thread -> will terminate 
    // std::jthread -> calls join() in its destructor
    std::jthread t{[]()
                  { print("Hello!"); }};

    // As a consequence, main() never finishes when std::jthread runs forever
    // std::jthread t2{[]() {
    //     while(true);
    // }};
}