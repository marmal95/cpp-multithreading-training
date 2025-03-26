#include "../util/print.hpp"

void function() { print("Hello from function!"); }

class FunctionObject
{
  public:
    void operator()() const { print("Hello from a function object!"); }
};

int main()
{
    // Creates new threads and starts its execution immediately
    // std::thread accepts any Callable: functions/lambdas/function objects.
    std::thread t1{function};
    std::thread t2{FunctionObject{}};
    std::thread t3{[]() { print("Hello from lambda!"); }};

    // Parent thread must take care of child threads by
    // - waiting until they execution completes by .join() - waits for the spawned thread before continuing
    // - detaching himself from the child by .detach() - allows to run it indepenently in the background
    t1.join();
    t2.join();
    t3.join();

    // When threads are still `joinable` in ~thread, std::terminate is called.
    // .joinable() - if object identifies an active thread of execution - "is in the state that represents some thread"
    //   default constructed       => not joinable
    //   when moved-from           => not joinable
    //   detach() / join() called  => not joinable
    // [!] thread that finished executing code is still considered as joinable!
}
