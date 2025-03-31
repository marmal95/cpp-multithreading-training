#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <vector>

template <typename ExecutionPolicy>
void benchmark(const std::string& name, ExecutionPolicy policy, std::vector<int>& vec)
{
    auto start = std::chrono::high_resolution_clock::now();
    std::for_each(policy, vec.begin(), vec.end(), [](int& x) { x *= 2; });
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << name << " took " << std::chrono::duration<double>(end - start).count() << " seconds\n";
}

int main()
{
    std::vector<int> vec(10'000'000, 1);

    benchmark("Sequential", std::execution::seq, vec);
    benchmark("Parallel", std::execution::par, vec);
    benchmark("Parallel + Vectorized", std::execution::par_unseq, vec);
    benchmark("Vectorized Only", std::execution::unseq, vec);

    return 0;
}
