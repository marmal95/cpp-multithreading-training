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