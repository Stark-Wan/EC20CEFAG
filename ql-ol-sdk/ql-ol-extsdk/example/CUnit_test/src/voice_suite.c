#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "voice_suite.h"
#include "testconf.h"

static voice_client_handle_type h_voice = 0;
static int voice_state_change_flag = 0;
static int voice_state_value = -1 ;
static int voice_call_id = -1;
//static int voice_waiting_interval = 60;

//#define VOICE_DEST_PHONE_NUMBER "18054099355"
extern char g_dest_phone_number[32];
extern int g_verbose ;
extern int g_interval;


int voice_suite_init()
{
	int ret;
	ret = QL_Voice_Call_Client_Init(&h_voice);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_Voice_Call_Client_Init failed.ret=%d\n", ret);
		return -1;
	}
	return 0;
}


int voice_suite_clean()
{
	int ret;
	ret = QL_Voice_Call_Client_Deinit(h_voice);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_Voice_Call_Client_Deinit failed.ret=%d\n", ret);
		return -1;
	}
	return 0;
}

void voice_suite_SetUp()
{
	return;
}

void voice_suite_TearDown()
{
	return;
}

static void ql_voice_call_cb_func(int                     call_id,
                                  char*                   phone_num,
                                  E_QL_VOICE_CALL_STATE_T state,
                                  void                    *contextPtr)
{
	//state
	//char *call_state[] = {"INCOMING", "DIALING", "ALERTING", "ACTIVE", "HOLDING", "END", "WAITING"};
	//printDebugFormatMsg("phonenumber: %s, state: %s\n", phone_num, call_state[state]);
	if(strcmp(phone_num, g_dest_phone_number) == 0)
	{
		voice_state_change_flag = 1;
		voice_call_id = call_id;
		voice_state_value = state;
	}
	
}


/********************************TEST CASE START******************************/
//
static void TEST_QL_Voice_Call_Start(void)
{
	int ret, interval = 0;
	int flag = 0;

	voice_state_change_flag = 0;
	voice_state_value = -1;
	voice_call_id = -1;

	printFuncPrefix;
	ret = QL_Voice_Call_Start(h_voice, E_QL_VCALL_EXTERNAL_SLOT_1, g_dest_phone_number, &voice_call_id);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_Voice_Call_Start error.ret=%d\n", ret);
		return ;
	}

	printFormatMsg("waiting %s hung up:               %2dS", g_dest_phone_number, interval);
	do
	{
		//if(interval % 10 == 0)
		//{
		//	printDebugFormatMsg("waiting %s hung up [%d].\n", g_dest_phone_number, interval);
		//}
		printf("\b\b\b%2dS", interval);
		fflush(stdout);
		if(voice_state_value == E_QL_MCM_VOICE_CALL_STATE_END)
		{
			flag = 1;
			CU_PASS("QL_Voice_Call_start success!");
			break;
		}
		sleep(1);
		interval++;
	}
	while (interval < g_interval);
	printFormatMsg("\n");
	if(flag == 0)
	{
		CU_FAIL("\tQL_Voice_Call_Start failed.");
	}
	voice_state_change_flag = -1;
}

static void TEST_QL_Voice_Call_End(void)
{
	int ret, interval1 = 0, interval2 = 0;
	int flag = 0;

	printFuncPrefix;
	printFormatMsg("waiting %s Call me:               %02dS", g_dest_phone_number, interval1);
	do
	{
		interval1++;
		//if(interval1 % 10 == 0)
		//{
		//	printDebugFormatMsg("waiting %s Call me [%d].\n", g_dest_phone_number, interval1);
		//}
		printf("\b\b\b%02dS", interval1);
		if(voice_state_value == E_QL_MCM_VOICE_CALL_STATE_INCOMING && 
			voice_state_change_flag == 1)
		{
			voice_state_change_flag = -1;
			
			ret = QL_Voice_Call_End(h_voice, voice_call_id);
			CU_ASSERT(ret == MCM_SUCCESS_V01);
			
			do
			{
				interval2++;
				if(voice_state_change_flag == 1)
				{
					CU_ASSERT(voice_state_value == E_QL_MCM_VOICE_CALL_STATE_END);
					break;
				}
				sleep(1);	
			}
			while (interval2 < g_interval);
			
			flag = 1;
			break;
		}
		sleep(1);
	}
	while (interval1 < g_interval);
	printFormatMsg("\n");
	if(flag == 0)
	{
		CU_FAIL("QL_Voice_Call_End failed.");
	}
	voice_state_change_flag = -1;
	
	return;

}


static void TEST_QL_Voice_Call_AddStateHandler(void)
{
	int ret;

	printFuncPrefix;
	ret = QL_Voice_Call_AddStateHandler(h_voice, ql_voice_call_cb_func, &voice_call_id);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_Voice_Call_AddStateHandler failed.ret=%d\n", ret);
	}
	return;
}
/********************************TEST CASE END********************************/

/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo voice_suite_case[] = {
	{"test QL_Voice_Call_AddStateHandler", TEST_QL_Voice_Call_AddStateHandler},
	{"test QL_Voice_Call_Start", TEST_QL_Voice_Call_Start},
	{"test QL_Voice_Call_End", TEST_QL_Voice_Call_End},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo voice_suites[] = {
	{"voice suite", voice_suite_init, voice_suite_clean, voice_suite_SetUp, voice_suite_TearDown, voice_suite_case},
	CU_SUITE_INFO_NULL,
};

