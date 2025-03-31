# Execution Policies in C++17 (`std::execution`)

C++17 introduced **execution policies** in the `<execution>` header, allowing developers to specify how certain algorithms (e.g., `std::sort`, `std::for_each`) execute.

These policies control whether an algorithm runs **sequentially**, **in parallel**, or **with vectorization (SIMD)**.

---

## 📌 Execution Policy Comparison

| Execution Policy            | Description                                                   | Parallel? | Vectorized? |
| --------------------------- | ------------------------------------------------------------- | --------- | ----------- |
| `std::execution::seq`       | **Sequential execution**, executes in order.                  | ❌ No      | ❌ No        |
| `std::execution::par`       | **Parallel execution**, multi-threaded.                       | ✅ Yes     | ❌ No        |
| `std::execution::par_unseq` | **Parallel + vectorized execution**, multi-threaded and SIMD. | ✅ Yes     | ✅ Yes       |
| `std::execution::unseq`     | **Vectorized execution**, single-threaded but SIMD.           | ❌ No      | ✅ Yes       |

---

## 🔍 Explanation of Each Policy

### 1️⃣ `std::execution::seq` (Sequenced Policy)

- Runs **sequentially** on a single thread.
- **Order of execution is preserved**.
- **No parallelism or vectorization**.

✅ **Use case**: When order of execution matters.  
🚫 **Avoid**: If you want performance improvements via parallelism.

```cpp
std::for_each(std::execution::seq, vec.begin(), vec.end(), [](int& x) { x *= 2; });
```

---

### 2️⃣ `std::execution::par` (Parallel Policy)

- Runs **across multiple threads** but **not vectorized**.
- **No guarantee of execution order**.
- Uses **multi-core processing** (e.g., via `std::thread` or `TBB` in GCC/MSVC).

✅ **Use case**: When you need **multi-threaded performance** but **not SIMD**.  
🚫 **Avoid**: If data dependencies exist between elements.

```cpp
std::sort(std::execution::par, vec.begin(), vec.end());
```

---

### 3️⃣ `std::execution::par_unseq` (Parallel + Vectorized Policy)

- **Fully parallel and vectorized**:
  - Uses **multi-threading** (CPU cores).
  - Uses **vectorized instructions (SIMD)** (e.g., AVX, SSE).
- **No guarantee of execution order**.
- **Highest level of parallelism** available.

✅ **Use case**: **Compute-heavy tasks on large datasets**.  
 🚫 **Avoid**: If **order matters** or there are **data dependencies**.

```cpp
std::for_each(std::execution::par_unseq, vec.begin(), vec.end(), [](int& x) { x *= 2; });
```

---

### 4️⃣ `std::execution::unseq` (Unsequenced Policy)

- **Vectorized execution (SIMD), but single-threaded**.
- Uses **SIMD CPU instructions** for efficiency.
- **No multi-threading** (operates in a single thread but vectorizes operations).
- **No guarantee of execution order**.

✅ **Use case**: **Math-heavy operations** where **SIMD (vectorization) is beneficial**, but you don't need multi-threading.  
🚫 **Avoid**: If execution order is important.

```cpp
std::for_each(std::execution::unseq, vec.begin(), vec.end(), [](int& x) { x *= 2; });
```

---

## 💡 Which One Should You Use?

| **Scenario**                       | **Recommended Execution Policy** |
| ---------------------------------- | -------------------------------- |
| Strict order needed                | `std::execution::seq`            |
| Multi-threaded execution (no SIMD) | `std::execution::par`            |
| Best performance (parallel + SIMD) | `std::execution::par_unseq`      |
| Single-threaded but SIMD optimized | `std::execution::unseq`          |

---
