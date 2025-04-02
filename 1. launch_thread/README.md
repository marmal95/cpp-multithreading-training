# 📌 Launching threads

## Joining and Detaching Threads
### Joining a Thread
Joining ensures the main thread waits for the spawned thread to complete.
```cpp
std::thread t(worker);
t.join(); // Blocks until worker() finishes
```

### Detaching a Thread
Detaching allows a thread to run independently in the background.
```cpp
std::thread t(worker);
t.detach(); // The thread runs independently
```
⚠️ **Warning:** A detached thread cannot be joined later, and accessing shared resources without synchronization may cause undefined behavior.

## Summary
- Use `std::jthread` when possible for safer automatic thread management.
- `std::thread` requires explicit `join()` or `detach()`, which can lead to resource leaks or crashes.
- Prefer `join()` over `detach()` unless the thread must run independently.

---

## `std::promise` and `std::future`

C++ provides `std::promise`, `std::future` for handling asynchronous operations and thread communication.

---

### What are `std::promise` and `std::future`?
- `std::promise` is used to set a value or an exception from one thread.
- `std::future` is used to retrieve the value or exception from another thread.

✅ `std::promise` sets the result, and `std::future` retrieves it.

---
## `std::packaged_task`

### What is `std::packaged_task`?
- Wraps a callable (function, lambda, or functor) and returns a `std::future`.
- Useful for deferred execution of tasks in a thread.

✅ `std::packaged_task` wraps a function and allows asynchronous execution.

---


## `std::async` in C++

`std::async` is a high-level mechanism in C++ for launching asynchronous tasks without managing threads manually. It returns a `std::future`, which allows retrieving the result when ready.

---

### `std::launch` Policies
`std::async` accepts an optional `std::launch` policy:
- `std::launch::async` → Ensures the task runs in a separate thread.
- `std::launch::deferred` → Runs the task only when `get()` is called.
- Default (unspecified) → Implementation chooses `async` or `deferred`.
