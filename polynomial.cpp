#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Polynomial {
 private:
    std::vector<T> data;

 public:
    explicit Polynomial(std::vector<T> coefs) {
        data = coefs;
        while (!data.empty() && data.back() == T(0)) {
            data.pop_back();
        }
    }

    Polynomial(T a = T()) {
        if (a != T(0)) {
            data = std::vector<T>(1, a);
        }
    }

    template <typename It>
    Polynomial(It first, It last) {
        while (first != last) {
            data.push_back(*first++);
        }
        while (!data.empty() && data.back() == T(0)) {
            data.pop_back();
        }
    }

    Polynomial& operator+= (const Polynomial& other) {
        data.resize(std::max(this->Degree() + 1, other.Degree() + 1));
        for (size_t i = 0; i < other.data.size(); ++i) {
            data[i] += other.data[i];
        }
        while (!data.empty() && data.back() == T(0)) {
            data.pop_back();
        }
        return (*this);
    }

    Polynomial& operator-= (const Polynomial& other) {
        data.resize(std::max(this->Degree() + 1, other.Degree() + 1));
        for (size_t i = 0; i < other.data.size(); ++i) {
            data[i] -= other.data[i];
        }
        while (!data.empty() && data.back() == T(0)) {
            data.pop_back();
        }
        return (*this);
    }

    Polynomial& operator*= (const Polynomial& other) {
        Polynomial t(data);
        data = std::vector<T>(this->Degree() + other.Degree() + 1);
        for (size_t i = 0; i < t.data.size(); ++i) {
            for (size_t j = 0; j < other.data.size(); ++j) {
                data[i + j] += t[i] * other[j];
            }
        }
        while (!data.empty() && data.back() == T(0)) {
            data.pop_back();
        }
        return (*this);
    }

    template <typename ET>
    ET operator() (ET val) const {
        ET t(1);
        ET res(0);
        for (int i = 0; i <= this->Degree(); ++i) {
            res += (data[i] * t);
            t *= val;
        }
        return res;
    }

    friend bool operator== (const Polynomial& a, const Polynomial& b) {
        return a.data == b.data;
    }

    friend bool operator!= (const Polynomial& a, const Polynomial& b) {
        return a.data != b.data;
    }

    friend Polynomial operator+ (const Polynomial& a, const Polynomial& b) {
        Polynomial t(a);
        t += b;
        return t;
    }

    friend Polynomial operator- (const Polynomial& a, const Polynomial& b) {
        Polynomial t(a);
        t -= b;
        return t;
    }

    friend Polynomial operator* (const Polynomial& a, const Polynomial& b) {
        Polynomial t(a);
        t *= b;
        return t;
    }

    friend Polynomial operator& (const Polynomial& a, const Polynomial& b) {
        return a(b);
    }

    friend std::ostream& operator<< (std::ostream& out, const Polynomial& p) {
        if (p.Degree() == -1) {
            out << 0;
        } else {
            for (int i = p.Degree(); i >= 0; --i) {
                T t = p[i];
                if (t == T(0)) {
                    continue;
                }
                if (t < T(0)) {
                    out << '-';
                    t = -t;
                } else if (i != p.Degree()) {
                    out << '+';
                }
                if ((t != T(1)) || (i == 0))  {
                    out << t;
                }
                if ((t != T(1)) && (i != 0)) {
                    out << '*';
                }
                if (i != 0) {
                    out << 'x';
                }
                if (i > 1) {
                    out << "^" << i;
                }
            }
        }
        return out;
    }

    const T operator[] (size_t i) const {
        if (i < data.size()) {
            return data[i];
        }
        return T(0);
    }

    auto begin() const {
        return data.cbegin();
    }

    auto end() const {
        return data.cend();
    }

    int Degree() const {
        return data.size() - 1;
    }
};
