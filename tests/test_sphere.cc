#include <catch2/catch_test_macros.hpp>
#include "../src/sphere.h"
#include "../src/vec3.h"
#include "../src/Raytracer/ray.h"
#include "../src/color.h"



TEST_CASE("Intersection with rays is computed correctly", "[sphere]")
{}

TEST_CASE("Constructor and access functions", "[sphere]")
{
    vec3 v{3, 4, 5};
    Color c{64, 128, 255};
    Sphere S1(v, 2, c);
    Sphere S2({3, 4, 5}, 2, {64, 128, 255});
    REQUIRE(S1.get_center() == S2.get_center());
    REQUIRE(S2.get_radius() == S1.get_radius());
    REQUIRE(S1.getColor() == S2.getColor());
}
