#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string_view>

class Figure {
public:
    virtual ~Figure() = default;
    virtual double area() const = 0;
    virtual std::string_view label() const = 0;
};
class Disk final : public Figure {
    double radius_;
public:
    explicit Disk(double radius) : radius_(radius) {}
    double area() const override { return 3.141592653589793 * radius_ * radius_; }
    std::string_view label() const override { return "Circle"; }
};
class BoxFace final : public Figure {
    double width_, height_;
public:
    BoxFace(double width, double height) : width_(width), height_(height) {}
    double area() const override { return width_ * height_; }
    std::string_view label() const override { return "Rectangle"; }
};
class TriangularFace final : public Figure {
    double base_, altitude_;
public:
    TriangularFace(double base, double altitude) : base_(base), altitude_(altitude) {}
    double area() const override { return base_ * altitude_ / 2.0; }
    std::string_view label() const override { return "Triangle"; }
};
int main() {
    const std::array<std::unique_ptr<Figure>, 3> figures{
        std::make_unique<Disk>(3.0), std::make_unique<BoxFace>(7.0, 4.0),
        std::make_unique<TriangularFace>(6.0, 5.0)};
    std::cout << "Areas through a common virtual interface\n" << std::fixed << std::setprecision(2);
    for (const auto& figure : figures)
        std::cout << figure->label() << ": " << figure->area() << " square units\n";
}
