
#ifdef EXPERIMENTAL_CORO
#include <experimental/coroutine>
namespace coro = std::experimental;
#else
#include <coroutine>
namespace coro = std;
#endif

#include <iostream>
#include <optional>

template <class T>
struct task {

    struct promise_type;
    using coro_handle = coro::coroutine_handle<promise_type>;

    struct promise_type {
        promise_type() { std::cout << __FUNCTION__ << std::endl; }

        virtual ~promise_type() {
            std::cout << __FUNCTION__ << std::endl;
        }

        task get_return_object() {  return { coro_handle::from_promise(*this) }; };
        auto initial_suspend() { return coro::suspend_always{}; }
        auto final_suspend() noexcept { return coro::suspend_always{}; }
        void return_value(T t) { value = std::move(t); }
        void unhandled_exception() { std::terminate(); }

        std::optional<T> value;
    };

    coro_handle handle;
    int result() {
        while (!handle.done()) {
            handle.resume();
        }
        return handle.promise().value.value();
    }

    ~task() {
        if (handle) {
            handle.destroy();
        }
    }
};

task<int> answer() {
    // under the hood
//    struct frame {
//        // local, args, state
//        using promise_type = task<int>::promise_type;
//        promise_type promise;
//    }* f = new frame{};
//    auto& p = f->promise;
//    new (addr_of_task) task<int>{p.get_return_object()};
//
//    try {
//        co_await p.initial_suspend();
//        // body
//        int a = 0b101010;
//        p.return_value(a);
//    } catch(...) {
//        p.unhandled_exception();
//    }
//
//    co_await p.final_suspend();

    //
    int a = 0b101010;
    co_return a;
}

int main() {
    std::cout << "Starting...\n";
    auto task = answer();

    std::cout << "Got task\n";
    int result = task.result();
    std::cout << "Got result: " << result;
}
