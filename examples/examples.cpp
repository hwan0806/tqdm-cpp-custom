#include <algorithm>
#include <numeric>
#include <set>
#include <unistd.h>
#include <vector>

#include "tqdmcpp/tqdmcpp.hpp"

const int sleep_time = 200;

std::vector<int> get_vector(int size)
{
    std::vector<int> A(size);
    std::iota(A.begin(), A.end(), 1000);
    //     std::generate(A.begin(), A.end(), []() {return rand(); } );

    return A;
}

std::set<int> get_set(int size)
{
    std::vector<int> A(size);
    std::iota(A.begin(), A.end(), 1000);
    //     std::generate(A.begin(), A.end(), []() {return rand(); } );

    return std::set<int>(A.begin(), A.end());
}

void test_rvalue()
{
    auto T = tq::tqdm(get_vector(5000));
    T.set_prefix("tqdm from rvalue ");
    T.set_theme_basic();
    T.disable_colors();
    for (auto t : T)
    {
        usleep(sleep_time);
        T << t;
    }
}

void test_lvalue()
{
    auto A = get_vector(5000);
    auto T = tq::tqdm(A);
    T.set_theme_original();
    T.set_prefix("tqdm from lvalue ");
    T.disable_color_transition();
    for (auto&& t : T)
    {
        t *= 2;
        usleep(sleep_time);
        T << t;
    }
}

void test_lvalue_2()
{
    auto A = get_set(5000);
    auto T = tq::tqdm(A);
    T.set_theme_circle();
    T.set_prefix("tqdm from lvalue ");
    for (auto&& t : T)
    {
        t *= 2;
        usleep(sleep_time);
        T << t;
    }
}

void test_constlvalue()
{
    const std::vector<int> A = get_vector(5000);
    auto T = tq::tqdm(A);
    T.set_prefix("tqdm from const lvalue ");
    T.set_theme_circle();
    for (auto&& t : T)
    {
        usleep(sleep_time);
        T << t;
    }
}

void test_trange()
{
    auto T = tq::trange(100, 5000);
    T.set_prefix("tqdm range ");
    for (auto t : T)
    {
        usleep(sleep_time);
        T << t;
    }
}

void test_timer()
{
    tq::tqdm_timer timer(2.0);
    timer.set_prefix("tqdm timer ");
    for (auto a : timer) { usleep(50000); }
}

int main()
{
    test_timer();
    std::cout << '\n';
    test_lvalue();
    std::cout << '\n';
    test_lvalue_2();
    std::cout << '\n';
    test_constlvalue();
    std::cout << '\n';
    test_rvalue();
    std::cout << '\n';
    test_trange();
    std::cout << '\n';

    return 0;
}
