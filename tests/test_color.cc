#include "../src/color.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Colors yield the right coordinates", "[color]")
{
    Color c(300,-1,3);
    
    REQUIRE(c.r() == 255);
    REQUIRE (c.g()==0);
    REQUIRE (c.b()==3);
}

TEST_CASE("vector equality", "[color]")
{
    Color v(1, 2, 3);
    Color w(1, 2, 3);
    Color x(0.5, 1.5, 2.5);
    Color y(0.5, 1.5, 2.5);
    Color z(y);
    REQUIRE(v == w);
    REQUIRE(x == y);
    REQUIRE(x == z);
}

TEST_CASE("Color addition and scalar multiplication", "[color]")
{
    Color u(128, 64, 0);
    Color v(0,128, 255);
    Color w(128, 192, 255);
    Color t(128, 0, 0);
    double a = -3;
    double b = 3;
    REQUIRE(u + v == w);
    REQUIRE(b * u == u * b);
    REQUIRE(a * u == Color(0, 0, 0));
    REQUIRE(b * v == Color(0, 255, 255));
    REQUIRE(u - v == t);
    u /= a;
    REQUIRE(u == Color(0, 0, 0));
}

