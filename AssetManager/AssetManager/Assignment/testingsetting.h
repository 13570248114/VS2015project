#ifndef TESTINGSETTING_H
#define TESTINGSETTING_H

/* Edit this file to enable and disable tests. */

// Set this to 1 to run the testing, 0 to run normal mode.
#define TESTING 1

// Set the below options to 1 to run the testing, 0 to skip.
#define TEST_TELEVISION 1
#define TEST_CUSTODIAN 1

// The below tests only run if the Custodian test is enabled.
#define TEST_COMPUTER 1
#define TEST_PHONE 1
#define TEST_HMD 1

#endif // TESTINGSETTING_H
