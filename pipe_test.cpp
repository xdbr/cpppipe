#include <iostream>
#include <vector>
#include <cassert>
#include <initializer_list>

#include "pipe.hpp"

#include <boost/test/minimal.hpp>


int plusone(int i) { return i+1; }
int addone(int i) { return i+1; }

void test1() {
    std::vector<int>        v{ 0, 2, 4 };
    ext::pipe<decltype(v)>  pipe{ v };
    std::vector<int>        expected{ 2, 4, 6 };

    std::vector<int> result = ext::pipe<decltype(v)>{v} | plusone | addone;
    
    BOOST_REQUIRE(expected == result);
}

void test2() {
    std::vector<int> v{ 0, 2, 4 };
    std::vector<int> V{ 2, 4, 6 };
    ext::pipe<decltype(v)> pipe{ v };
    ext::pipe<decltype(V)> expected{ V };
    
    auto result = pipe | plusone | addone; // auto q will be of type pipe<T>
    
    BOOST_REQUIRE(result == expected);
}

void test3() {
    std::vector<int> v{ 0, 2, 4 };
    std::vector<int> V{ 2, 4, 6 };
    ext::pipe<decltype(V)> expected{ V };

    auto result = ext::make_pipe(v) | plusone | addone;

    BOOST_REQUIRE(expected == result);
}

void test4() {
    std::vector<int> v{ 0, 2, 4 };
    std::vector<int> V{ 2, 4, 6 };
    ext::pipe<decltype(V)> expected{ V };

    auto result = ext::make_pipe(v) | [](int i){ return i+1; } | [](int i){ return i+1; };

    BOOST_REQUIRE(expected == result);
}

void test5() {
    std::vector<int> v{ 0, 2, 4 };
    std::vector<int> expected{ 2, 4, 6 };
    std::vector<int> result;

    (ext::make_pipe(v) | plusone | addone) > result;

    BOOST_REQUIRE(expected == result);
}

struct specification {
    typedef std::function<void()>       function_type;
    typedef std::vector<function_type>  value_type;

    value_type spec_;

    explicit specification(const std::initializer_list<function_type> & spec)
    : spec_{spec} {}

    void run() const {
        for (const auto & run : spec_)
            run();
    }
};

int test_main( int ac, char* av[] ) {
    specification{ test1, test2, test3, test4 }.run();
    return 0;
}