#include <iostream>
using namespace std;

#include <boost/timer/timer.hpp>
#define BOOST_TEST_MODULE My Test
#include <boost/test/included/unit_test.hpp>
using namespace boost;

BOOST_AUTO_TEST_CASE(first_test)
{
    int i = 1;
    BOOST_TEST(1);
    BOOST_TEST(i == 2);
}
