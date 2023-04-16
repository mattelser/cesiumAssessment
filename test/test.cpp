//
//

#include <catch2/catch_test_macros.hpp>

bool foo()
{
    return true;
}

TEST_CASE("test foo", "[foo]")
{
    REQUIRE(foo());
}
