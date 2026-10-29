#include <chrono>
#include <deque>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>
#include <vector>

template<typename T> class LabStack {
    std::vector<T> values_;
public:
    void push(T value) { values_.push_back(value); }
    T pop() {
        if (values_.empty()) throw std::underflow_error("Stack is empty");
        T value = values_.back(); values_.pop_back(); return value;
    }
};
template<typename T> class LabQueue {
    std::deque<T> values_;
public:
    void enqueue(T value) { values_.push_back(value); }
    T dequeue() {
        if (values_.empty()) throw std::underflow_error("Queue is empty");
        T value = values_.front(); values_.pop_front(); return value;
    }
};
template<typename Operation> void measure(const char* name, Operation operation) {
    const auto start = std::chrono::steady_clock::now();
    const long long checksum = operation();
    const auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::steady_clock::now() - start).count();
    if (checksum != 49995000) throw std::runtime_error("Incorrect checksum");
    std::cout << name << ": " << elapsed << " us; checksum=" << checksum << '\n';
}
int main() {
    LabStack<int> stack; LabQueue<int> queue;
    for (int value : {10, 20, 30}) { stack.push(value); queue.enqueue(value); }
    std::cout << "Stack removal:";
    for (int i = 0; i < 3; ++i) std::cout << ' ' << stack.pop();
    std::cout << "\nQueue removal:";
    for (int i = 0; i < 3; ++i) std::cout << ' ' << queue.dequeue();
    std::cout << "\nUnderflow checks: ";
    int caught = 0;
    try { stack.pop(); } catch (const std::underflow_error&) { ++caught; }
    try { queue.dequeue(); } catch (const std::underflow_error&) { ++caught; }
    if (caught != 2) throw std::runtime_error("Underflow check failed");
    std::cout << "passed\n10000 insertions and removals per container\n";
    measure("Template stack", [] { LabStack<int> s; long long total=0;
        for(int i=0;i<10000;++i) s.push(i);
        for(int i=0;i<10000;++i) { total+=s.pop(); }
        return total; });
    measure("STL stack", [] { std::stack<int> s; long long total=0;
        for(int i=0;i<10000;++i) s.push(i);
        for(int i=0;i<10000;++i) { total+=s.top(); s.pop(); } return total; });
    measure("Template queue", [] { LabQueue<int> q; long long total=0;
        for(int i=0;i<10000;++i) q.enqueue(i);
        for(int i=0;i<10000;++i) { total+=q.dequeue(); }
        return total; });
    measure("STL queue", [] { std::queue<int> q; long long total=0;
        for(int i=0;i<10000;++i) q.push(i);
        for(int i=0;i<10000;++i) { total+=q.front(); q.pop(); } return total; });
}
