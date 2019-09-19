#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dm_suite.h"
#include "testconf.h"

static dm_client_handle_type h_dm = 0;
extern int g_verbose;


int dm_suite_init()
{
	int ret;
	ret = QL_MCM_DM_Client_Init(&h_dm);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_MCM_DM_Client_Init failed. ret=%d\n", ret);
		return -1;
	}
	return 0;
}


int dm_suite_clean()
{
	int ret;

	ret = QL_MCM_DM_Client_Deinit(h_dm);
	if(ret)
	{
		printErrMsg("QL_MCM_DM_Client_Deinit failed. ret=%d\n", ret);
		return -1;
	}
	return 0;
}

void dm_suite_SetUp()
{
	return;
}

void dm_suite_TearDown()
{
	return;
}

/********************************TEST CASE START******************************/

static void TEST_QL_MCM_DM_GetSerialNumbers(void)
{
	int ret, imei_len, meid_len;
	ql_dm_device_serial_numbers_t dm_device_serial_numbers;

	printFuncPrefix;
	
    memset(&dm_device_serial_numbers, 0, sizeof(dm_device_serial_numbers));
	ret = QL_MCM_DM_GetSerialNumbers(h_dm, &dm_device_serial_numbers);

	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_DM_GetSerialNumbers failed, ret=%d\n", ret);
	}
	else
	{
		imei_len = strlen(dm_device_serial_numbers.imei);
		CU_ASSERT_EQUAL(imei_len, TEST_IMEI_LENGTH);
		
		printFormatMsg("QL_MCM_DM_GetSerialNumbers->imei: %s[%d].\n", 
							dm_device_serial_numbers.imei, imei_len);

		meid_len = strlen(dm_device_serial_numbers.meid);
		CU_ASSERT_EQUAL(meid_len, TEST_MEID_LENGTH);

		printFormatMsg("QL_MCM_DM_GetSerialNumbers->meid: %s[%d].\n",
							dm_device_serial_numbers.meid, meid_len);
	}
	return ;
}
//QL_MCM_DM_GetFirmware
static void TEST_QL_MCM_DM_GetFirmware(void)
{
	int ret, id_len;
	ql_dm_device_rev_id_t dm_device_rev;

	printFuncPrefix;
	memset(&dm_device_rev, 0, sizeof(dm_device_rev));
    ret = QL_MCM_DM_GetFirmware(h_dm, &dm_device_rev);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("\tdevice_rev_id: %s\n", dm_device_rev.device_rev_id);
	}
	else
	{
		id_len = strlen(dm_device_rev.device_rev_id);
		CU_ASSERT(id_len > 0);

		printFormatMsg("device_rev_id: %s[%d]\n", dm_device_rev.device_rev_id, id_len);

	}
	return;
}

/********************************TEST CASE END********************************/


/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo dm_suite_case[] = {
	{"test QL_MCM_DM_GetSerialNumbers", TEST_QL_MCM_DM_GetSerialNumbers},
	{"test QL_MCM_DM_GetFirmware", TEST_QL_MCM_DM_GetFirmware},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo dm_suites[] = {
	{"dm suite", dm_suite_init, dm_suite_clean, dm_suite_SetUp, dm_suite_TearDown, dm_suite_case},
	CU_SUITE_INFO_NULL,
};


