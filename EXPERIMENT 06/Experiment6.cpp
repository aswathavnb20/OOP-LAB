#include <iostream>
#include <memory>
#include <utility>

class Session {
    int id_;
public:
    explicit Session(int id) : id_(id) { std::cout << "Acquire session " << id_ << '\n'; }
    void work() const { std::cout << "Use session " << id_ << '\n'; }
    ~Session() { std::cout << "Release session " << id_ << '\n'; }
};
template<typename T> class ScopedOwner {
    T* resource_;
public:
    explicit ScopedOwner(T* resource) noexcept : resource_(resource) {}
    ~ScopedOwner() { delete resource_; }
    ScopedOwner(const ScopedOwner&) = delete;
    ScopedOwner& operator=(const ScopedOwner&) = delete;
    ScopedOwner(ScopedOwner&& other) noexcept : resource_(std::exchange(other.resource_, nullptr)) {}
    ScopedOwner& operator=(ScopedOwner&& other) noexcept {
        if (this != &other) { delete resource_; resource_ = std::exchange(other.resource_, nullptr); }
        return *this;
    }
    T* operator->() const noexcept { return resource_; }
};
int main() {
    std::cout << "Custom RAII owner\n";
    { ScopedOwner<Session> first(new Session(1)); auto second = std::move(first); second->work(); }
    std::cout << "Unique ownership transfer\n";
    { auto first = std::make_unique<Session>(2); auto second = std::move(first);
      std::cout << "Original owner empty: " << std::boolalpha << !first << '\n'; second->work(); }
    std::cout << "Shared ownership and weak observation\n";
    std::weak_ptr<Session> observer;
    { auto first = std::make_shared<Session>(3); observer = first;
      { auto second = first; std::cout << "Owners: " << first.use_count() << '\n'; second->work(); }
      std::cout << "Owners after inner scope: " << first.use_count() << '\n'; }
    std::cout << "Observer expired: " << observer.expired() << '\n';
}
