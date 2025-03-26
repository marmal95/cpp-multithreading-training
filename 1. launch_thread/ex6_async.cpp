#include <future>
#include <iostream>
#include <vector>

// Function to compute sum of numbers in a range
auto sumRange(int start, int end)
{
    int sum = 0;
    for (int i = start; i <= end; ++i)
    {
        sum += i;
    }
    return sum;
}

int main()
{
    int n = 1'000;
    int numThreads = 4;
    int chunkSize = n / numThreads;

    std::vector<std::future<int>> futures;

    // Launch asynchronous tasks
    for (int i = 0; i < numThreads; ++i)
    {
        int start = i * chunkSize + 1;
        int end = (i + 1) * chunkSize;

        // Call `sumRange` asynchonously
        // std::launch::async - ensures that the function runs in a separate thread

        // Alternatively: std::launch::deferred - the task is executed on the calling thread the first time its result
        // is requested (lazy evaluation)

        // A std::future is an object that acts as a placeholder for the result of the asynchronous computation.
        // The result of sumRange(start, end) can be retrieved later using .get() on the std::future object.

        auto future = std::async(std::launch::async, sumRange, start, end);
        futures.push_back(std::move(future));
    }

    int totalSum = 0;
    for (auto& f : futures)
    {
        // Waits for the computation to finish and retrieves the value.
        totalSum += f.get();
    }

    std::cout << "Total sum: " << totalSum << std::endl;
}