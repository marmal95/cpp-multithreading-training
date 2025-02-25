#pragma once

#include <iostream>
#include <syncstream>
#include <thread>

template <typename... Args>
inline void print(Args &&...args)
{
    std::osyncstream out{std::cout};
    out << "[" << std::this_thread::get_id() << "]: ";
    (out << ... << args) << ' ';
    out << std::endl;
}