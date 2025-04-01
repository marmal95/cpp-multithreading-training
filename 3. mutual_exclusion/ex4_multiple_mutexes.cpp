#include "../util/print.hpp"
#include <mutex>

struct BankAccount
{
    double balance;
    std::mutex mutex;
};

void transfer(BankAccount& source, BankAccount& target, const double amount)
{
    // DEADLOCK
    // std::lock_guard lock1{source.mutex};
    // std::lock_guard lock2{target.mutex};

    // std::lock(source.mutex, target.mutex);
    // std::unique_lock lock1{source.mutex, std::adopt_lock};
    // std::unique_lock lock2{target.mutex, std::adopt_lock};

    // std::unique_lock lock1{source.mutex, std::defer_lock};
    // std::unique_lock lock2{target.mutex, std::defer_lock};
    // std::lock(lock1, lock2);

    // std::scoped_lock lock{source.mutex, target.mutex};

    target.balance += amount;
    source.balance -= amount;
}

int main()
{
    BankAccount account1{2000};
    BankAccount account2{1000};

    {
        std::jthread thread1([&]() {
            for (int i = 0; i < 1000; i++)
            {
                transfer(account1, account2, 10);
            }
        });

        std::jthread thread2([&]() {
            for (int i = 0; i < 1000; i++)
            {
                transfer(account2, account1, 10);
            }
        });
    }

    print(account1.balance, " ", account2.balance);
}