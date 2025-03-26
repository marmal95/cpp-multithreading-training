#include <future>
#include <iostream>
#include <thread>

// Function to be wrapped
int computeSquare(int x) { return x * x; }

int main()
{
    // Wrap the function in a packaged_task
    std::packaged_task<int(int)> task(computeSquare);

    // Get future to retrieve result
    std::future<int> result = task.get_future();

    // Run the task in a separate thread
    std::jthread t(std::move(task), 5);

    // Get result (waits if necessary)
    std::cout << "Square: " << result.get() << std::endl;
}

// std::packaged_task is used when you need to wrap a callable (like a function, lambda, or functor) so that its
// result can be retrieved asynchronously via std::future.

// Key Use Cases:
// Deferred execution – Storing packaged tasks in a queue and executing them in worker threads
//                      (The task is created but executed later, typically in a different thread).
// (e.g. thread pools)
//
// Lazy Execution – A task can be created and started when needed.
// Task Scheduling – Assigning tasks dynamically in a concurrent system.