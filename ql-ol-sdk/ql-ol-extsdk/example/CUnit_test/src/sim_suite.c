#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "sim_suite.h"
#include "testconf.h"

static sim_client_handle_type h_sim = 0;
extern int g_verbose;


int sim_suite_init()
{
	int ret;
	ret = QL_MCM_SIM_Client_Init(&h_sim);
	if(ret)
	{
		printErrMsg("Client Init failed.\n");
		return -1;
	}
	return 0;
}


int sim_suite_clean()
{
	int ret;
	
	ret = QL_MCM_SIM_Client_Deinit(h_sim);
	if(ret)
	{
		printErrMsg("Client Deinit failed.\n");
		return -1;
	}
	return 0;
}

void sim_suite_SetUp()
{
	return;
}

void sim_suite_TearDown()
{
	return;
}


/********************************TEST CASE START******************************/
//QL_MCM_SIM_GetIMSI
static void TEST_QL_MCM_SIM_GetIMSI(void)
{
	int ret, len;
	char buff[32];
	QL_SIM_APP_ID_INFO_T info;

	printFuncPrefix;
	memset(buff, 0, sizeof(buff));
    info.e_slot_id = E_QL_MCM_SIM_SLOT_ID_1;
    info.e_app = E_QL_MCM_SIM_APP_TYPE_3GPP;
    ret = QL_MCM_SIM_GetIMSI(h_sim, &info, buff, sizeof(buff));
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret !=  MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_SIM_GetIMSI failed. ret=%d\n", ret);
		return;
	}

	if(memcmp(buff, "460", 3) != 0)
	{
		CU_FAIL("QL_MCM_SIM_GetIMSI IMSI content error.");
	}

	len = strlen(buff);
	CU_ASSERT_EQUAL(len, TEST_IMSI_LENGTH);
	
	printFormatMsg("QL_MCM_SIM_GetIMSI IMSI: %s[%d]\n", buff, len);

	return;
}

//QL_MCM_SIM_GetICCID
static void TEST_QL_MCM_SIM_GetICCID(void)
{
	int ret, iccid_len;
	char buff[32];
	
	printFuncPrefix;
	memset(buff, 0, sizeof(buff));
	ret = QL_MCM_SIM_GetICCID(h_sim, E_QL_MCM_SIM_SLOT_ID_1, buff, sizeof(buff));
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_SIM_GetICCID failed.ret=%d\n", ret);
		return;
	}
	
	iccid_len = strlen(buff);
	CU_ASSERT_EQUAL(iccid_len, TEST_ICCID_LENGTH);

	if(memcmp(buff, "8986", 4) != 0)
	{
		CU_FAIL("QL_MCM_SIM_GetICCID->iccid content error.");
	}
	printFormatMsg("ICCID: %s, len: %d\n", buff, iccid_len);
	return;
}


/********************************TEST CASE END********************************/


/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo sim_suite_case[] = {
	{"test QL_MCM_SIM_GetIMSI", TEST_QL_MCM_SIM_GetIMSI},
	{"test QL_MCM_SIM_GetICCID", TEST_QL_MCM_SIM_GetICCID},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo sim_suites[] = {
	{"sim suite", sim_suite_init, sim_suite_clean, sim_suite_SetUp, sim_suite_TearDown, sim_suite_case},
	CU_SUITE_INFO_NULL,
};


