#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <ql_wwan_v2.h>
#include "wwanv2_suite.h"
#include "testconf.h"

extern int g_verbose;

static ql_data_call_s g_call = {
	.profile_idx = 1,
	.reconnect = true,
	.ip_family = QL_DATA_CALL_TYPE_IPV4,
};

static char interface_name[16];
static bool g_cb_recv = FALSE;
static void data_call_state_callback(ql_data_call_state_s *state);



int wwanv2_suite_init()
{
	int ret;
	memset(interface_name, 0, sizeof(interface_name));

	ret = ql_data_call_init(data_call_state_callback);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("ql_data_call_init failed.ret=%d\n", ret);
		return -1;
	}
	return 0;
}


int wwanv2_suite_clean()
{
	//ql_data_call_destroy();
	return 0;
}

void wwanv2_suite_SetUp()
{
	return;
}

void wwanv2_suite_TearDown()
{
	return;
}


static void data_call_state_callback(ql_data_call_state_s *state)
{
	//interface_name
	if(g_call.profile_idx == state->profile_idx)
	{
		if(state->state == QL_DATA_CALL_CONNECTED)
		{
			strncpy(interface_name, state->name, sizeof(interface_name));
			if(state->ip_family == QL_DATA_CALL_TYPE_IPV4)
			{
				printFormatMsg("\tIP address:          %s\n", inet_ntoa(state->v4.ip));
				printFormatMsg("\tGateway address:     %s\n", inet_ntoa(state->v4.gateway));
				printFormatMsg("\tPrimary DNS address: %s\n", inet_ntoa(state->v4.pri_dns));
				printFormatMsg("\tSecond DNS address:  %s\n", inet_ntoa(state->v4.sec_dns));
			}
			g_cb_recv = TRUE;
		}
	}
	return;
}

static int get_addr_by_ifname(const char *ifname, char *ipaddr_str, int ipaddr_len)
{
	int ret = -1;
	struct sockaddr_in *addr = NULL;
	struct ifreq ifr;

	if(ifname == NULL) return -1;

	memset(&ifr, 0, sizeof(struct ifreq));

	int fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
	if(fd == -1)
	{
		printErrMsg("get_addr_by_ifname socket error.\n");
		return -1;
	}

	ifr.ifr_addr.sa_family = AF_INET;
	strncpy(ifr.ifr_name, ifname, IFNAMSIZ - 1);
	if ((ret = ioctl(fd, SIOCGIFADDR, &ifr)) != 0)
	{
		goto OUT;
	}

	addr = (struct sockaddr_in *)&ifr.ifr_addr;
	strncpy(ipaddr_str, inet_ntoa(addr->sin_addr), ipaddr_len);
	
	ret = 0;
OUT:
	close(fd);
	return ret;
}

/********************************TEST CASE START******************************/

//QL_Data_Call_Init


//QL_Data_Call_Start
static void TEST_QL_Data_Call_Start(void)
{
	int ret, count = 10, flag = 0;
	ql_data_call_error_e err = QL_DATA_CALL_ERROR_NONE;

	printFuncPrefix;

	ret = ql_data_call_start(&g_call, &err);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("ql_data_call_start failed. ret=%d\n", ret);
		return;
	}

	while(count--)
	{
		sleep(1);
		if(g_cb_recv)
		{
			flag = 1;
			break;
		}
	}
	if(flag != 1)
	{
		CU_FAIL("ql_data_call_start callback return failed or timeout.");
	}
	return;
}

//QL_Data_Call_Info_Get
static void TEST_QL_Data_Call_Info_Get(void)
{
	int ret;
	ql_data_call_info_s info = {0};
	ql_data_call_error_e err = QL_DATA_CALL_ERROR_NONE;
	char addr[16];

	printFuncPrefix;

	ret = ql_data_call_info_get(g_call.profile_idx, g_call.ip_family, &info, &err);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);

	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("ql_data_call_info_get failed.ret=%d\n", ret);
		return;
	}
	//check info
	if(strlen(interface_name) > 0)
	{
		ret = get_addr_by_ifname(interface_name, addr, sizeof(addr));
		if(ret == 0)
		{
			CU_ASSERT_STRING_EQUAL(inet_ntoa(info.v4.addr.ip), addr);
			printFormatMsg("ifname `%s` addr `%s`\n", interface_name, addr);
		}
		else
		{
			printErrMsg("get_addr_by_ifname ret %d.\n", ret);
		}
	}
	else
	{
		printErrMsg("interface_name length is 0.\n");
	}
	return;
}

//QL_Data_Call_Stop
static void TEST_QL_Data_Call_Stop(void)
{
	int ret;
	char addr[16] = {0};
	ql_data_call_error_e err = QL_DATA_CALL_ERROR_NONE;

	printFuncPrefix;

	ret = ql_data_call_stop(g_call.profile_idx, g_call.ip_family, &err);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("ql_data_call_stop failed.ret=%d\n", ret);
		return;
	}

	sleep(3);

	if(strlen(interface_name) > 0)
	{
		ret = get_addr_by_ifname(interface_name, addr, sizeof(addr));
		if(ret == 0)
		{
			CU_FAIL("ql_data_call_stop failed, data call already connected");
		}
	}
	else
	{
		printErrMsg("interface_name length is 0.\n");
	}
	return;
}


/********************************TEST CASE END********************************/

/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo wwanv2_suite_case[] = {
	{"test QL_Data_Call_Start", TEST_QL_Data_Call_Start},
	{"test QL_Data_Call_Info_Get", TEST_QL_Data_Call_Info_Get},
	{"test QL_Data_Call_Stop", TEST_QL_Data_Call_Stop},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo wwanv2_suites[] = {
	{"wwanv2 suite", wwanv2_suite_init, wwanv2_suite_clean, wwanv2_suite_SetUp, wwanv2_suite_TearDown, wwanv2_suite_case},
	CU_SUITE_INFO_NULL,
};


