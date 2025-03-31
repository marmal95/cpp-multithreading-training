# 📌 Atomic Operations

## 🔹 What is `std::atomic<T>`?
`std::atomic<T>` is a **thread-safe** wrapper for a variable of type `T` that ensures operations on it are **atomic** (indivisible). This prevents **race conditions** in multithreaded programs.

### 🛠 What Does It Do?
- Ensures **safe concurrent access** to a shared variable.  
- Guarantees that **reads/writes/updates** are performed **atomically** (without interference from other threads).  
- Prevents **data races** without requiring a `std::mutex`.  

### ✅ When is `std::atomic` Needed?
Use `std::atomic<T>` when:
- ✔️ Multiple threads **read & modify** the same variable.
- ✔️ You need **safe updates** (e.g., counters, flags, shared states).
- ✔️ Performance is critical, and **mutexes are too slow**.

### ⚠️ What Happens Without `std::atomic`?
🚨 If multiple threads **modify a shared variable without synchronization**, you get **race conditions** leading to:
- ❌ **Unpredictable results** (some updates may be lost).
- ❌ **Corrupt memory** (if partial writes occur on non-atomic types).
- ❌ **Undefined behavior (UB)** - the program might crash, hang, or produce incorrect results.

## ⚠️ When Can You NOT Use `std::atomic`?
While `std::atomic<T>` is useful, there are cases where it is **not applicable**:
- ❌ **Complex Data Structures**: If an object involves multiple fields that must be updated atomically, `std::atomic` won’t work (use `std::mutex` or `std::shared_mutex`).
- ❌ **Operations Requiring Strong Consistency**: If you need **transactions** or multiple operations to be atomic together, `std::atomic` is insufficient.
- ❌ **Non-Trivial Objects**: `std::atomic<T>` only works with **trivially copyable types**. If `T` has a constructor, destructor, or virtual functions, it cannot be used atomically.

<br />

## 🔹 What is `std::atomic_flag`?
`std::atomic_flag` is the simplest atomic type in C++, used as a **low-level** lock-free boolean flag.

### 🛠 What Does It Do?
- Represents a **binary flag** that can be **set** (`true`) or **cleared** (`false`).
- Provides **atomic test-and-set operations**, useful for **simple spinlocks**.
- Always **lock-free**, making it ideal for performance-critical applications.

### ✅ When to Use `std::atomic_flag`?
- **Spinlocks**: When you need a lightweight, **lock-free** synchronization mechanism.
- **Fast signaling** between threads when a simple flag is sufficient.
- **Avoiding full `std::atomic<bool>`**, since `std::atomic_flag` is guaranteed to be **lock-free**.

<br />

## `std::atomic<bool>` vs `std::atomic_flag` in C++

Both `std::atomic<bool>` and `std::atomic_flag` provide **atomic** operations for thread synchronization, but they have key differences in terms of features and performance.


| Feature               | `std::atomic<bool>` | `std::atomic_flag` |
|----------------------|------------------|------------------|
| **Type**            | Atomic Boolean (`true/false`) | Atomic flag (simplest atomic variable) |
| **Initialization**  | Can be initialized to `true` or `false` | Always **false** after default construction (`std::atomic_flag flag = ATOMIC_FLAG_INIT;`) |
| **Operations**      | Supports all atomic operations like `load()`, `store()`, `exchange()`, `compare_exchange_strong()` | Only supports `test_and_set()` and `clear()` |
| **Resetting Value** | Can be set to `true` or `false` freely | Must be explicitly cleared using `clear()` before reuse |
| **Lock-Free Guarantee** | **Not always lock-free** on all platforms | **Always lock-free** |
| **Performance** | Slightly slower due to full atomic operations | Faster due to minimal operations |
| **Use Case** | General atomic boolean flag, shared state management | Simple spinlock or low-level synchronization primitive |

---