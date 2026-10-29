#include <array>
#include <cassert>
#include <cstddef>
#include <iostream>

class SquareMatrix {
    using Row = std::array<int, 2>;
    std::array<Row, 2> cells_{};
public:
    SquareMatrix() = default;
    SquareMatrix(int a, int b, int c, int d) : cells_{{Row{a,b}, Row{c,d}}} {}
    Row& operator[](std::size_t row) { return cells_.at(row); }
    const Row& operator[](std::size_t row) const { return cells_.at(row); }
    SquareMatrix operator+(const SquareMatrix& rhs) const {
        SquareMatrix answer;
        for (std::size_t row = 0; row < 2; ++row)
            for (std::size_t col = 0; col < 2; ++col)
                answer[row][col] = cells_[row][col] + rhs[row][col];
        return answer;
    }
    SquareMatrix operator*(const SquareMatrix& rhs) const {
        SquareMatrix answer;
        for (std::size_t row = 0; row < 2; ++row)
            for (std::size_t col = 0; col < 2; ++col)
                for (std::size_t k = 0; k < 2; ++k)
                    answer[row][col] += cells_[row][k] * rhs[k][col];
        return answer;
    }
    friend std::ostream& operator<<(std::ostream& out, const SquareMatrix& matrix) {
        for (const auto& row : matrix.cells_) out << row[0] << ' ' << row[1] << '\n';
        return out;
    }
};
int main() {
    const SquareMatrix left(2, 0, 1, 3), right(4, 1, 2, 5);
    const auto sum = left + right;
    const auto product = left * right;
    assert(sum[0][0] == 6 && sum[0][1] == 1 && sum[1][0] == 3 && sum[1][1] == 8);
    assert(product[0][0] == 8 && product[0][1] == 2 && product[1][0] == 10 && product[1][1] == 16);
    std::cout << "Left matrix\n" << left << "Right matrix\n" << right
              << "Sum\n" << sum << "Product\n" << product << "Matrix checks passed\n";
}
