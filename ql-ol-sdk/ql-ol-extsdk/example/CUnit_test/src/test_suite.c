#include <stdio.h>
#include <stdlib.h>
#include "test_suite.h"
#include "testconf.h"


	


/*
	this function is be tested.
	it is always in your code. here is just an example.
*/
int add_func(int a, int b)
{
	return a + b;
}



int test_suite_init()
{
	return 0;
}


int test_suite_clean()
{
	return 0;
}

void test_suite_SetUp()
{
	return;
}

void test_suite_TearDown()
{
	return;
}


/********************************TEST CASE START******************************/


void test_func1()
{
	printFuncPrefix;
	CU_ASSERT_EQUAL(add_func(1,2), 3);
}
void test_func2()
{
	printFuncPrefix;
	CU_ASSERT_EQUAL(add_func(2,4), 6);
}


/********************************TEST CASE end********************************/



/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo tests_suite_case[] = {
  { "test_func1", test_func1},
  { "test_func2", test_func2},
  CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo test_suites[] = {
	{"test suite", test_suite_init, test_suite_clean, test_suite_SetUp, test_suite_TearDown, tests_suite_case},
	CU_SUITE_INFO_NULL,
};


