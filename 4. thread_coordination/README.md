# 📌 Thread Coordination

| Mechanism       | Description |
|----------------|------------|
| **`std::condition_variable`** | Lets threads **wait** for an event and be **notified** when ready. |
| **`std::condition_variable_any`** | Like `condition_variable`, but works with **any lock type**. |
| **`std::barrier`** (C++20) | Synchronizes **multiple threads at specific points** (multi-stage processing). |
| **`std::latch`** (C++20) | Allows threads to **wait until a counter reaches zero** (one-time use). |
| **`std::semaphore`** (C++20) | Limits **how many threads** can access a resource concurrently. |

📌 **Use Case**: **Waiting for data availability**, **multi-stage processing**, **rate-limiting access**.

## Barrier
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

---

## Difference Between `std::binary_semaphore` and `std::mutex`

| Feature          | `std::binary_semaphore`            | `std::mutex`                 |
|-----------------|-----------------------------------|------------------------------|
| **Ownership**    | No ownership concept (any thread can release) | Only the thread that locks can unlock |
| **Count Behavior** | Has a count of 0 or 1 (wait/release) | Always locked or unlocked |
| **Signaling**    | Threads can `acquire()` and `release()` freely | Must `lock()` and `unlock()` correctly |
| **Use Case**     | Producer-consumer patterns, synchronization points | Protecting shared resources from concurrent access |

### **🔹 Key Takeaway**
- Use **`std::mutex`** when you need **exclusive ownership** over a resource.
- Use **`std::binary_semaphore`** when you need **synchronization between threads** without strict ownership constraints.

| Feature                           | `std::mutex`                                   | `std::counting_semaphore`                          |
|-----------------------------------|------------------------------------------------|----------------------------------------------------|
| **Purpose**                       | Provides **exclusive ownership** of a resource. | Allows **multiple threads** to access a resource concurrently, up to a specified limit. |
| **Thread Access Control**         | Only **one thread** can acquire the lock at a time. | **Multiple threads** can acquire the semaphore concurrently, up to the semaphore’s count. |
| **Locking Mechanism**             | `lock()` blocks other threads until the mutex is unlocked. | `acquire()` blocks if the semaphore's count is `0`, otherwise decrements the count and proceeds. |
| **Unlocking Mechanism**           | `unlock()` releases the lock for other threads. | `release()` increments the semaphore's count, potentially waking up a blocked thread. |
| **Use Cases**                     | Used for **exclusive access** to shared resources. | Used to limit the number of threads that can access a shared resource concurrently. |
| **Thread Blocking**               | Blocks threads if the mutex is already locked. | Blocks threads if the semaphore count is `0`. |
| **Concurrency**                   | **No concurrency** (only one thread can access at a time). | **Limited concurrency** (multiple threads can access simultaneously, up to the semaphore's count). |
| **Performance**                   | Generally lower overhead, but can block threads. | Potentially better concurrency with more overhead for managing the semaphore count. |
| **Ideal Scenario**                | Exclusive access to shared resource.            | Limiting concurrent access to a limited pool of resources. |
