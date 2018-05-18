#ifndef TEST_MAIN_TEST__H
#define  TEST_MAIN_TEST__H
/** Basic testing setup.
 * This just configures logging and chain parameters.
 */

#include <string>

struct BasicTestingSetup {

    BasicTestingSetup(const std::string& chainName = "main");
    ~BasicTestingSetup();
};

/** Testing setup that configures a complete environment.
 * Included are data directory, coins database, script check threads
 * and wallet (if enabled) setup.
 */
struct TestingSetup: public BasicTestingSetup {

    TestingSetup(const std::string& chainName = "main");
    ~TestingSetup();
//   std::string pathTemp;
};

#endif
