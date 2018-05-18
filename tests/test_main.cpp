#define BOOST_TEST_MODULE Ucenter  Test Suite
#define BOOST_TEST_DYN_LINK
#include "test_main.h"
#include <boost/filesystem.hpp>
#include <boost/test/unit_test.hpp>


BasicTestingSetup::BasicTestingSetup(const std::string& chainName)
{
}

BasicTestingSetup::~BasicTestingSetup()
{
}

TestingSetup::TestingSetup(const std::string& chainName) : BasicTestingSetup(chainName)
{
//    pathTemp =  strprintf("test_eos_%lu_", (unsigned long)GetTime());
 //   boost::filesystem::create_directories(pathTemp);
}

TestingSetup::~TestingSetup()
{
 //   boost::filesystem::remove_all(pathTemp);
}
 
/*
int BOOST_TEST_CALL_DECL
main( int argc, char* argv[] )
{
    //return ::boost::unit_test::unit_test_main( &init_unit_test, argc, argv );
}
*/
