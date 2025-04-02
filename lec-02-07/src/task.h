//
// Created by Egor Basharin on 13.04.2021.
//

#ifndef LEC09_S02_LEC09_COROUTINES_01_SECTION_TASK_H_
#define LEC09_S02_LEC09_COROUTINES_01_SECTION_TASK_H_

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
private:
    using coro_handle = coro::coroutine_handle<promise_type>;
public:
    struct promise_type {
        auto initial_suspend() { return coro::suspend_always{}; }
        auto final_suspend() noexcept { return coro::suspend_never{}; }
        task get_return_object() { return task{coro_handle::from_promise(*this)}; }
        void unhandled_exception() { std::terminate(); }
        void return_value(const T& value) { value_ = value; }
        void return_value(T&& value) { value_ = std::move(value); }

        std::optional<T> value_;

        ~promise_type() { }
    };

    void resume() {
        if (handle_) {
            handle_.resume();
        }
    }

    T result() { return {}; }

private:
    explicit task(coro_handle handle) : handle_(std::move(handle)) {}
    coro_handle handle_;
};

#endif //LEC09_S02_LEC09_COROUTINES_01_SECTION_TASK_H_
