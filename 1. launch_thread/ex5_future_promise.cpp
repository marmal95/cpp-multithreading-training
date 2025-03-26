#include <future>
#include <iostream>
#include <thread>

// Function to compute sum in a range and store result in promise
void sumRange(int start, int end, std::promise<int> promise)
{
    int sum = 0;
    for (int i = start; i <= end; ++i)
    {
        sum += i;
    }

    // Store the result in promise
    promise.set_value(sum);
}

int main()
{
    int start = 1, end = 1'000;

    // Create a promise and future pair - allowing communication between threads
    // std::promise is a producer that stores a value or result,
    // std::future is a consumer that retrieves the value asynchronously, .
    std::promise<int> resultPromise;
    std::future<int> resultFuture = resultPromise.get_future();

    // Launch a thread
    std::jthread t(sumRange, start, end, std::move(resultPromise));

    // Get the result from future
    // Blocks until the thread sets the value
    int sum = resultFuture.get();

    std::cout << "Sum from " << start << " to " << end << " is: " << sum << std::endl;
}
