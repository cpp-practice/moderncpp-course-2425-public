#include <iostream>

#ifdef EXPERIMENTAL_CORO
#include <experimental/coroutine>
namespace coro = std::experimental;
#else
#include <coroutine>
namespace coro = std;
#endif

using Awaitable = coro::suspend_always;

#include <optional>
template <class T>
struct task {
    struct promise_type;
private:
    using coro_handle = coro::coroutine_handle<promise_type>;
public:
    struct promise_type {
        auto initial_suspend() { return coro::suspend_always{}; }
        auto final_suspend() noexcept { return coro::suspend_always{}; }
        task get_return_object() { return task{coro_handle::from_promise(*this)}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() { }
    };

    void resume() {
        if (handle_) {
            handle_.resume();
        }
    }

    ~task() { handle_.destroy(); }

private:
    explicit task(coro_handle handle) : handle_(std::move(handle)) {}
    coro_handle handle_;
};

task<void> step_by_step() {
    std::cout << "step1\n";

    co_await Awaitable {};

    std::cout << "step2\n";
}

int main() {
    auto task = step_by_step();
    std::cout << "watch1\n";
    task.resume();
    std::cout << "watch2\n";
    // task.resume();
    std::cout << "watch3\n";
}
