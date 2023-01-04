#include <iostream>
#include <vector>
#include <variant>

// 请修复这个函数的定义：10 分
template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &a) {
    os << "{";
    for (size_t i = 0; i < a.size(); i++) {
        os << a[i];
        if (i != a.size() - 1)
            os << ", ";
    }
    os << "}";
    return os;
}

// 请修复这个函数的定义：10 分
template <class T1, class T2>
decltype(auto) operator+(std::vector<T1> const &a, std::vector<T2> const &b) {
    // 请实现列表的逐元素加法！10 分
    // 例如 {1, 2} + {3, 4} = {4, 6}
    std::vector<decltype(T1{}+T2{})> vec;
    vec.resize(std::min(a.size(),b.size()));
    for(int i = 0; i < vec.size(); ++i)
    {
        vec[i] = a[i] + b[i];    
    }

    return vec;
}

template <class T1, class T2>
std::variant<T1, T2> operator+(std::variant<T1, T2> const &a, std::variant<T1, T2> const &b) {
// 请实现自动匹配容器中具体类型的加法！10 分
    return
    std::visit([&](const auto& t1, const auto& t2) -> std::variant<T1,T2>{
        return t1 + t2;
    },a,b);

}

template <class T1, class T2, class T3>
std::variant<T1, T2> operator+(std::variant<T1, T2> const &a, T3 const &b) {
    static_assert(std::is_same_v<T1,T3> || std::is_same_v<T2,T3>);
    return std::visit([&](const auto& v)->std::variant<T1, T2>{
        return v + b;
    },a);

}

template <class T1, class T2>
std::ostream& operator<<(std::ostream &os, std::variant<T1, T2> const &a) {
    // 请实现自动匹配容器中具体类型的打印！10 分
    return 
    std::visit([&](const auto& t) -> std::ostream&{
        os << t;
        return os;
    },a);
}

int main() {
    std::vector<int> a = {1, 4, 2, 8, 5, 7};
    std::cout << a << std::endl;
    std::vector<double> b = {3.14, 2.718, 0.618};
    std::cout << b << std::endl;
    auto c = a + b;

    // 应该输出 1
    std::cout << std::is_same_v<decltype(c), std::vector<double>> << std::endl;

    // 应该输出 {4.14, 6.718, 2.618}
    std::cout << c << std::endl;

    std::variant<std::vector<int>, std::vector<double>> d = c;
    std::variant<std::vector<int>, std::vector<double>> e = a;
    d = d + c + e;
    //d = d + e;
    // 应该输出 {9.28, 17.436, 7.236}
    std::cout << d << std::endl;

    return 0;
}
