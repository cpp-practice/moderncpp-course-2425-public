
#include "task.h"

struct T {
    T() { std::cout << "T()" << std::endl; }
    ~T() { std::cout << "~T()" << std::endl; }
};

task<int> coroutine() {
    // <---
    T t;
    std::cout << "step1" << std::endl;
    int a = 1;
    co_await coro::suspend_always{};
    std::cout << "step2" << std::endl;
    int b = 2;
    co_await coro::suspend_always{};
    std::cout << "step3" << std::endl;
    co_return a + b;
}

int main() {
    [[maybe_unused]] auto task = coroutine();
    std::cout << "WATCHPOINT1" << std::endl; task.resume();
    std::cout << "WATCHPOINT2" << std::endl; task.resume();
    std::cout << "WATCHPOINT3" << std::endl; task.resume();
    std::cout << "WATCHPOINT4" << std::endl;
}