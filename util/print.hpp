#pragma once

#include <array>
#include <iostream>
#include <syncstream>
#include <thread>
#include <vector>

template <typename T> inline std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    std::cout << "[ ";
    for (const auto& elem : vec)
        std::cout << elem << " ";
    std::cout << "]";
    return out;
}

template <typename T, std::size_t N> std::ostream& operator<<(std::ostream& out, const std::array<T, N>& arr)
{
    out << "[ ";
    for (const auto& elem : arr)
        out << elem << " ";
    out << "]";
    return out;
}

template <typename... Args> inline void print(Args&&... args)
{
    std::osyncstream out{std::cout};
    out << "[" << std::this_thread::get_id() << "]: ";
    (out << ... << args) << ' ';
    out << std::endl;
}