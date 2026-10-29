#include <iostream>
#include <string>
#include <utility>

class LabRecord {
    int number_;
    std::string owner_;
public:
    LabRecord(int number, std::string owner)
        : number_(number), owner_(std::move(owner)) {
        std::cout << "Constructor: record opened\n";
    }
    void print() const {
        std::cout << "Record number: " << number_ << "\nStudent: " << owner_ << '\n';
    }
    ~LabRecord() { std::cout << "Destructor: record closed\n"; }
};

int main() {
    std::cout << "Object lifetime demonstration\n";
    {
        const LabRecord record(20, "Aswath");
        record.print();
    }
    std::cout << "Scope finished\n";
}
