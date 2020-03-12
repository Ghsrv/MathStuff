#include <iostream>
#include <utility>
#include <vector>


template < typename T >
class Matrix {
 private:
    size_t a, b;
    std::vector<T> matrix;
    const T& operator() (size_t x, size_t y) const {
        return matrix[x * b + y];
    }
    T& operator() (size_t x, size_t y) {
        return matrix[x * b + y];
    }
    Matrix(size_t a, size_t b): a(a), b(b) {
        (this->matrix).resize(a * b);
    }

 public:
    explicit Matrix(const std::vector <std::vector<T>>& matrix) {
        a = matrix.size();
        if (a != 0) {
            b = matrix[0].size();
        } else {
            b = 0;
        }
        (this->matrix).reserve(a * b);
        for (const auto& i : matrix) {
            for (const auto& j : i) {
                (this->matrix).push_back(j);
            }
        }
    }

    Matrix operator+ (const Matrix<T>& other) const {
        Matrix res = *this;
        for (size_t i = 0; i < matrix.size(); ++i) {
            res.matrix[i] += other.matrix[i];
        }
        return res;
    }

    Matrix& operator+= (const Matrix<T>& other) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            matrix[i] += other.matrix[i];
        }
        return *this;
    }

    template <typename t>
    Matrix& operator*= (const t& num) {
        for (size_t i = 0; i < matrix.size(); ++i) {
            matrix[i] *= num;
        }
        return *this;
    }

    template <typename t>
    Matrix operator* (const t& num) const {
        Matrix res = *this;
        for (size_t i = 0; i < matrix.size(); ++i) {
            res.matrix[i] *= num;
        }
        return res;
    }

    Matrix operator* (const Matrix& other) const {
        Matrix res(a, other.b);
        for (size_t i = 0; i < a; ++i) {
            for (size_t j = 0; j < other.b; ++j) {
                for (size_t k = 0; k < b; ++k) {
                    res(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return res;
    }

    Matrix& operator*= (const Matrix& other) {
        *this = *this * other;
        return *this;
    }

    Matrix transposed() const {
        Matrix t(b, a);
        for (size_t i = 0; i < a; ++i) {
            for (size_t j = 0; j < b; ++j) {
                t(j, i) = (*this)(i, j);
            }
        }
        return t;
    }

    Matrix& transpose() {
        *this = this->transposed();
        return *this;
    }

    auto begin() {
        return matrix.begin();
    }

    auto end() {
        return matrix.end();
    }

    auto begin() const {
        return matrix.cbegin();
    }

    auto end() const {
        return matrix.cend();
    }

    std::pair<size_t, size_t> size() const {
        return {a, b};
    }

    friend std::ostream& operator<< (std::ostream& os, const Matrix<T>& a) {
        for (size_t i = 0; i < a.a; ++i) {
            for (size_t j = 0; j < a.b; ++j) {
                os << a(i, j);
                if (j != a.b - 1) os << '\t';
            }
            if (i != a.a - 1) os << '\n';
        }
        return os;
    }
};
