//
// Created by Egor Basharin on 13.04.2021.
//

#ifndef LEC09_S02_LEC09_COROUTINES_01_SECTION_GENERATOR_H_
#define LEC09_S02_LEC09_COROUTINES_01_SECTION_GENERATOR_H_

#include <exception>

#ifdef EXPERIMENTAL_CORO
#include <experimental/coroutine>
namespace coro = std::experimental;
#else
#include <coroutine>
namespace coro = std;
#endif

template <class T>
class generator {
public:
    struct promise_type;
private:
    using coro_handle = coro::coroutine_handle<promise_type>;
public:
    struct promise_type {
        auto initial_suspend() { return coro::suspend_always{}; }
        auto final_suspend() noexcept { return coro::suspend_always{}; }
        generator get_return_object() { return generator{coro_handle::from_promise(*this)}; }
        void unhandled_exception() { std::terminate(); }
        void return_void() { }
        auto yield_value(const T& value) { this->value = &value; return coro::suspend_always{}; }

        const T* value;
    };

    struct end_iterator {};

    struct iterator {
        explicit iterator(coro_handle handle) : handle_(handle) {
            handle_.resume();
        }

        const T& operator*() const {
            return *handle_.promise().value;
        }

        iterator& operator++() {
            handle_.resume();
            return *this;
        }

        coro_handle handle_;

        bool operator==(end_iterator) const {
            return handle_.done();
        }
    };

    iterator begin() const { return iterator{handle_}; }
    end_iterator end() const { return {}; }

    ~generator() {
        if (handle_) handle_.destroy();
    }

private:
    explicit generator(coro_handle handle) : handle_(std::move(handle)) {}

    coro_handle handle_;
};

#endif //LEC09_S02_LEC09_COROUTINES_01_SECTION_GENERATOR_H_
