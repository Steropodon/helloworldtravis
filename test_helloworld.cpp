#define BOOST_TEST_MODULE hw_test
#include "hw.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(hw_test)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(hwversion() > 0);
}

BOOST_AUTO_TEST_SUITE_END()