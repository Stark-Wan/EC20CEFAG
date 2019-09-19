#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "device_suite.h"
#include "testconf.h"


extern int g_verbose;


int device_suite_init()
{
	return 0;
}


int device_suite_clean()
{
	return 0;
}

void device_suite_SetUp()
{
	return;
}

void device_suite_TearDown()
{
	return;
}

/********************************TEST CASE START******************************/
#define TEST_DEVICE_MAX_LENGTH (128)
//QL_DEV_GetImei
static void TEST_Q_DEV_GetImei(void)
{
	int ret;
	char buff[TEST_DEVICE_MAX_LENGTH];

printFuncPrefix;

	memset(buff, 0, TEST_DEVICE_MAX_LENGTH);
	ret = QL_DEV_GetImei(buff, TEST_DEVICE_MAX_LENGTH);
	CU_ASSERT_EQUAL(ret, 0);
	if(ret)
	{
		printFormatMsg("QL_DEV_GetImei ret=%d\n", ret);
	}
	else
	{
		int len = strlen(buff);
		CU_ASSERT_EQUAL(len, TEST_IMEI_LENGTH);

		printFormatMsg("IMEI: %s[%d]\n", buff, len);

	}
	return;
}

//QL_DEV_GetFirmwareVersion
static void TEST_QL_DEV_GetFirmwareVersion(void)
{
	int ret;
	char buff[TEST_DEVICE_MAX_LENGTH];

	printFuncPrefix;

	memset(buff, 0, TEST_DEVICE_MAX_LENGTH);
	ret = QL_DEV_GetFirmwareVersion(buff, TEST_DEVICE_MAX_LENGTH);
	CU_ASSERT_EQUAL(ret, 0);
	if(ret)
	{
		printFormatMsg("QL_DEV_GetFirmwareVersion ret=%d\n", ret);
	}
	else
	{
		int len = strlen(buff);
		CU_ASSERT(len > 0);

		printFormatMsg("FirmwareVersion: %s[%d]\n", buff, len);
	}
	return;
}
//QL_DEV_GetDeviceModel
static void TEST_QL_DEV_GetDeviceModel(void)
{
	int ret;
	char buff[TEST_DEVICE_MAX_LENGTH];

	printFuncPrefix;

	memset(buff, 0, TEST_DEVICE_MAX_LENGTH);
	ret = QL_DEV_GetDeviceModel(buff, TEST_DEVICE_MAX_LENGTH);
	CU_ASSERT_EQUAL(ret, 0);
	if(ret)
	{
		printFormatMsg("QL_DEV_GetDeviceModel ret=%d\n", ret);
	}
	else
	{
		int len = strlen(buff);
		CU_ASSERT(len > 0);

		printFormatMsg("DeviceModel: %s[%d]\n", buff, len);

	}
	return;
}
//QL_DEV_GetMeid
static void TEST_QL_DEV_GetMeid(void)
{
	int ret;
	char buff[TEST_DEVICE_MAX_LENGTH];

printFuncPrefix;
	memset(buff, 0, TEST_DEVICE_MAX_LENGTH);
	ret = QL_DEV_GetMeid(buff, TEST_DEVICE_MAX_LENGTH);
	CU_ASSERT_EQUAL(ret, 0);
	if(ret)
	{
		printFormatMsg("QL_DEV_GetDeviceModel ret=%d\n", ret);
	}
	else
	{
		int len = strlen(buff);
		CU_ASSERT_EQUAL(len, TEST_MEID_LENGTH);

		printFormatMsg("Meid: %s[%d]\n", buff, len);
	}
	return;
}
//QL_DEV_GetEsn
static void TEST_QL_DEV_GetEsn(void)
{
	int ret;
	char buff[TEST_DEVICE_MAX_LENGTH];

printFuncPrefix;

	memset(buff, 0, TEST_DEVICE_MAX_LENGTH);
	ret = QL_DEV_GetEsn(buff, TEST_DEVICE_MAX_LENGTH);
	CU_ASSERT_EQUAL(ret, 0);
	if(ret)
	{
		printFormatMsg("QL_DEV_GetEsn ret=%d\n", ret);
	}
	else
	{
		int len = strlen(buff);
		CU_ASSERT_EQUAL(len, TEST_ESN_LENGTH);

		printFormatMsg("Esn: %s[%d]\n", buff, len);

	}
	return;
}

/********************************TEST CASE END********************************/


/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo device_suite_case[] = {
	{"test Q_DEV_GetImei", TEST_Q_DEV_GetImei},
	{"test QL_DEV_GetFirmwareVersion", TEST_QL_DEV_GetFirmwareVersion},
	{"test QL_DEV_GetDeviceModel", TEST_QL_DEV_GetDeviceModel},
	{"test QL_DEV_GetMeid", TEST_QL_DEV_GetMeid},
	{"test QL_DEV_GetEsn", TEST_QL_DEV_GetEsn},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo device_suites[] = {
	{"device suite",device_suite_init,device_suite_clean,device_suite_SetUp,device_suite_TearDown,device_suite_case},
	CU_SUITE_INFO_NULL,
};



