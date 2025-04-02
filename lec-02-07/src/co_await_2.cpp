#include <iostream>

#ifdef EXPERIMENTAL_CORO
#include <experimental/coroutine>
namespace coro = std::experimental;
#else
#include <coroutine>
namespace coro = std;
#endif


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

template <class T>
struct AsyncTask {
    bool await_ready() const noexcept { return false; }
    void await_suspend(coro::coroutine_handle<>) {}
    T await_resume() { return std::move(value); }
    T value;
};

AsyncTask<int> async_task() {
    return { 10 };
}

task<int> do_work() {
    int res = co_await async_task();

//    auto&& awaiter = async_task();
//    if (!awaiter.await_ready()) {
//        awaiter.await_suspend(cur_coro_handle);
//        // suspend()
//    }
//    auto res = awaiter.await_resume();

    co_return res + 2;
}

int main() {
        auto task = do_work();
        // code
        std::cout << task.result();
}
