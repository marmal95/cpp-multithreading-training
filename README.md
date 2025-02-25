# `std::atomic` vs `std::mutex` in C++

Both `std::atomic` and `std::mutex` are used for thread synchronization in C++, but they serve different purposes and have different performance characteristics.

## **Comparison Table**

| Feature            | `std::atomic` | `std::mutex` |
|-------------------|--------------|-------------|
| **Purpose** | Provides atomic operations on a single variable | Provides mutual exclusion for protecting critical sections |
| **Granularity** | Works at the level of individual variables | Protects multiple variables or entire code blocks |
| **Locking Mechanism** | Lock-free (where supported), non-blocking | Requires explicit locking (`lock()`, `unlock()`) |
| **Performance** | Faster (avoids kernel overhead) | Slower (involves OS-level locks) |
| **Use Case** | Simple atomic operations (counters, flags, pointers) | Complex operations involving multiple shared resources |
| **Thread Blocking** | Never blocks; always non-blocking | Can block waiting threads |
| **Memory Overhead** | Low overhead | Higher overhead due to system calls |

---


## **When to Use `std::atomic`**
Use `std::atomic` when:
- You need to protect **a single variable** (like a counter or a flag).
- Lock-free operations improve performance.
- You are working with **simple operations** like incrementing, decrementing, or exchanging values.

## **When to Use `std::mutex`**
Use `std::mutex` when:
- You need to protect **multiple variables** or **complex data structures** (e.g., modifying multiple members of a class).
- You require **atomicity across multiple operations**.
- The performance overhead of a mutex is acceptable.


## Deadlock avoidance
1. Ustal jednolitą kolejność blokowania mutexów - Zawsze blokuj mutexy w tej samej kolejności w różnych wątkach.
2. Użyj std::lock() do uniknięcia zakleszczenia - std::lock() blokuje wiele mutexów na raz, zapobiegając deadlockowi
3. Używaj std::lock_guard / std::scoped_lock - gwarantuje odblokowanie mutexa