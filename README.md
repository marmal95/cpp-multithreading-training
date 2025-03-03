## 📌 C++ Thread Synchronization Mechanisms

### **1️⃣ Mutual Exclusion (Protects Shared Resources)**
| Mechanism       | Description |
|----------------|------------|
| **`std::mutex`** | Ensures **only one thread** accesses a shared resource at a time. |
| **`std::recursive_mutex`** | Allows **the same thread** to lock multiple times (useful for recursive functions). |
| **`std::timed_mutex`** | Like `std::mutex`, but allows a **timeout** when trying to lock. |
| **`std::shared_mutex`** | Allows **multiple readers but only one writer** (reader-writer lock). |

📌 **Use Case**: Protecting **shared data structures** from concurrent modifications.

---

### **2️⃣ Thread Coordination (Synchronization Between Threads)**
| Mechanism       | Description |
|----------------|------------|
| **`std::condition_variable`** | Lets threads **wait** for an event and be **notified** when ready. |
| **`std::condition_variable_any`** | Like `condition_variable`, but works with **any lock type**. |
| **`std::barrier`** (C++20) | Synchronizes **multiple threads at specific points** (multi-stage processing). |
| **`std::latch`** (C++20) | Allows threads to **wait until a counter reaches zero** (one-time use). |
| **`std::semaphore`** (C++20) | Limits **how many threads** can access a resource concurrently. |

📌 **Use Case**: **Waiting for data availability**, **multi-stage processing**, **rate-limiting access**.

---

### **3️⃣ Atomic Operations**
| Mechanism       | Description |
|----------------|------------|
| **`std::atomic<T>`** | Provides **thread-safe** operations on variables **without locks**. |
| **`std::atomic_flag`** | A simple atomic boolean flag (set/reset). |

📌 **Use Case**: **Incrementing counters, lock-free data structures, low-latency operations**.

---

### **4️⃣ Smart Locking (Automatic Lock Management)**
| Mechanism       | Description |
|----------------|------------|
| **`std::lock_guard<std::mutex>`** | Auto-locks a mutex for a **single critical section** (RAII style). |
| **`std::unique_lock<std::mutex>`** | More flexible than `lock_guard` (supports deferred locking, unlocking, and moving). |
| **`std::scoped_lock`** (C++17) | Locks **multiple mutexes at once** (prevents deadlocks). |

📌 **Use Case**: **Automatic locking & unlocking** to prevent forgetting to unlock a `mutex`.

---

## **🚀 Which One to Use?**
| Scenario | Best Mechanism |
|----------|---------------|
| **Protect shared data** (only one thread at a time) | `std::mutex` ✅ |
| **Multiple readers, one writer** | `std::shared_mutex` ✅ |
| **Limit access to N threads** (e.g., thread pool, database connections) | `std::semaphore` ✅ |
| **Wait for an event before proceeding** | `std::condition_variable` ✅ |
| **Thread-safe counter** | `std::atomic<int>` ✅ |
| **Synchronize multiple threads at stages** | `std::barrier` ✅ |
| **Wait for N tasks to finish before proceeding** | `std::latch` ✅ |


## `std::atomic` vs `std::mutex` in C++

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
1. Avoid nested locks.
2. Establish a uniform order for blocking mutexes - Always block mutexes in the same order across all threads.
3. Use std::lock() to avoid deadlocks - std::lock() locks multiple mutexes at once, preventing deadlocks
4. Use std::lock_guard/std::scoped_lock to guarantee mutex unlock


# Locks comparison


| Feature              | `std::lock_guard` | `std::unique_lock` | `std::scoped_lock` |
|----------------------|------------------|--------------------|--------------------|
| **Introduced In**    | C++11            | C++11             | C++17             |
| **Purpose**         | Simple, automatic mutex locking | More flexible mutex handling | Locks multiple mutexes at once |
| **Locking Mechanism** | Locks immediately on construction | Can defer, move, or manually unlock | Locks immediately on construction |
| **Unlocking Support** | ❌ No manual unlock | ✅ Can unlock manually (`unlock()`) | ❌ No manual unlock |
| **Multiple Mutexes** | ❌ No | ❌ No | ✅ Yes (prevents deadlocks) |
| **Performance** | ⚡ Fast, minimal overhead | 🐢 Slight overhead due to flexibility | ⚡ Fast, optimized for multiple mutexes |
| **Best Use Case** | Simple, scoped locking | When flexibility is needed (e.g., deferred locking, moving ownership) | When locking multiple mutexes safely |


# Barrier
1. ✅ Parallel Processing Pipelines – Synchronize different stages of computation.
2. ✅ Multi-Threaded Algorithms – Ensure all threads complete a step before moving forward.
3. ✅ Data Processing in Batches – Process chunks of data in parallel and synchronize between batches.


## 📌 Comparison: `std::barrier` vs `std::latch`

| Feature            | `std::barrier`                        | `std::latch`                          |
|--------------------|--------------------------------------|--------------------------------------|
| **Type**          | Reusable Synchronization Mechanism   | One-Time Countdown Synchronization |
| **Resets Automatically?** | ✅ Yes (after all threads arrive) | ❌ No (one-time use) |
| **Callback Function?** | ✅ Yes (executed after all threads arrive) | ❌ No |
| **When to Use?**  | Synchronize threads **at multiple stages** (e.g., iterative parallel algorithms) | Synchronize threads **only once** (e.g., waiting for initialization) |
