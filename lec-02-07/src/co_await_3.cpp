#include <iostream>

#ifdef EXPERIMENTAL_CORO
#include <experimental/coroutine>
namespace coro = std::experimental;
#else
#include <coroutine>
namespace coro = std;
#endif


#include <optional>
#include <chrono>
#include <thread>

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
        void return_value(T t) { value = std::move(t); }
        T value;
    };

    void resume() {
        if (handle_) {
            handle_.resume();
        }
    }

    T result() {
        while (!handle_.done())
            handle_.resume();
        return handle_.promise().value;
    }

    ~task() { handle_.destroy(); }

private:
    explicit task(coro_handle handle) : handle_(std::move(handle)) {}
    coro_handle handle_;
};

struct Sleep {
    bool await_ready() noexcept { return false; }
    void await_suspend(coro::coroutine_handle<>) noexcept {
        std::this_thread::sleep_for(duration);
    }
    void await_resume() noexcept {}
    std::chrono::seconds duration;
};

task<int> do_work() {
    co_await Sleep { std::chrono::seconds {5} };
    co_return 20;
}

int main() {
    auto task = do_work();
    std::cout << task.result();
}
