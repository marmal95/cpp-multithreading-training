# 📌 Mutual Exclusion

## **Mutual Exclusion (Protects Shared Resources)**
| Mechanism       | Description |
|----------------|------------|
| **`std::mutex`** | Ensures **only one thread** accesses a shared resource at a time. |
| **`std::recursive_mutex`** | Allows **the same thread** to lock multiple times (useful for recursive functions). |
| **`std::timed_mutex`** | Like `std::mutex`, but allows a **timeout** when trying to lock. |
| **`std::shared_mutex`** | Allows **multiple readers but only one writer** (reader-writer lock). |

📌 **Use Case**: Protecting **shared data structures** from concurrent modifications.

---

<br />

## **Smart Locking (Automatic Lock Management)**
| Mechanism       | Description |
|----------------|------------|
| **`std::lock_guard<std::mutex>`** | Auto-locks a mutex for a **single critical section** (RAII style). |
| **`std::unique_lock<std::mutex>`** | More flexible than `lock_guard` (supports deferred locking, unlocking, and moving). |
| **`std::scoped_lock`** (C++17) | Locks **multiple mutexes at once** (prevents deadlocks). |

📌 **Use Case**: **Automatic locking & unlocking** to prevent forgetting to unlock a `mutex`.


### Locks comparison

| Feature              | `std::lock_guard` | `std::unique_lock` | `std::scoped_lock` |
|----------------------|------------------|--------------------|--------------------|
| **Introduced In**    | C++11            | C++11             | C++17             |
| **Purpose**         | Simple, automatic mutex locking | More flexible mutex handling | Locks multiple mutexes at once |
| **Locking Mechanism** | Locks immediately on construction | Can defer, move, or manually unlock | Locks immediately on construction |
| **Unlocking Support** | ❌ No manual unlock | ✅ Can unlock manually (`unlock()`) | ❌ No manual unlock |
| **Multiple Mutexes** | ❌ No | ❌ No | ✅ Yes (prevents deadlocks) |
| **Performance** | ⚡ Fast, minimal overhead | 🐢 Slight overhead due to flexibility | ⚡ Fast, optimized for multiple mutexes |
| **Best Use Case** | Simple, scoped locking | When flexibility is needed (e.g., deferred locking, moving ownership) | When locking multiple mutexes safely |

## `std::atomic` vs `std::mutex` in C++

Both `std::atomic` and `std::mutex` are used for thread synchronization in C++, but they serve different purposes and have different performance characteristics.

### **Comparison Table**

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

### **When to Use `std::atomic`**
Use `std::atomic` when:
- You need to protect **a single variable** (like a counter or a flag).
- Lock-free operations improve performance.
- You are working with **simple operations** like incrementing, decrementing, or exchanging values.

### **When to Use `std::mutex`**
Use `std::mutex` when:
- You need to protect **multiple variables** or **complex data structures** (e.g., modifying multiple members of a class).
- You require **atomicity across multiple operations**.
- The performance overhead of a mutex is acceptable.


## Deadlock avoidance
1. Avoid nested locks.
2. Establish a uniform order for blocking mutexes - Always block mutexes in the same order across all threads.
3. Use std::lock() to avoid deadlocks - std::lock() locks multiple mutexes at once, preventing deadlocks
4. Use std::lock_guard/std::scoped_lock to guarantee mutex unlock