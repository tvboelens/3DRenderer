#define CONFIG_CATCH_MAIN

#include "../src/vec3.h"
#include <catch2/catch_test_macros.hpp>

TEST_CASE("vectors yield the right coordinates", "[vector]")
{
    vec3 v(1,2,3);
    
    REQUIRE(v.x() == 1);
    REQUIRE (v.y()==2);
    REQUIRE (v.z()==3);
}

TEST_CASE("vector equality", "[vector]")
{
    vec3 v(1, 2, 3);
    vec3 w(1, 2, 3);
    vec3 x(0.5, 1.5, 2.5);
    vec3 y(0.5, 1.5, 2.5);
    vec3 z(y);
    REQUIRE(v == w);
    REQUIRE(x == y);
    REQUIRE(x == z);
}

TEST_CASE("vector addition and scalar multiplication", "[vector]")
{
    vec3 u(0.5, 1, 1.5);
    vec3 v(1, 2, 3);
    vec3 w(1.5, 3, 4.5);
    double a = 0;
    double b = 0.5;
    REQUIRE(u + v == w);
    REQUIRE(a * u == u * a);
    REQUIRE(a * u == vec3(0, 0, 0));
    REQUIRE(b * v == u);
    REQUIRE(w - v == u);
}

TEST_CASE("vector length and dot product", "[vector]")
{
    vec3 u(0.5, 1, 1.5);
    vec3 v(1, 2, 3);
    vec3 w(1.5, 3, 4.5);
    REQUIRE(dot(v, u) == dot(u, v));
    REQUIRE(dot(w, v) == 3 * dot(v, u));
    REQUIRE(dot(1.5 * v, w) == 1.5 * dot(v, w));
    REQUIRE (dot(v, 1.5 * w) == 1.5 * dot(v, w));
    REQUIRE(dot(u, v) == 7);
    REQUIRE(w.length_squared() == dot(w, w));
    REQUIRE(w.length() == std::sqrt(w.length_squared()));
}
