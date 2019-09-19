#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "gps_suite.h"
#include "testconf.h"


static loc_client_handle_type h_loc = 0;
static int g_gps_location_update = 0;
static double g_loc_latitude = 0;
static double g_loc_longitude = 0;

double latitude_std_min_hefei = 30.57;
double latitude_std_max_hefei = 32.32;
double longitude_std_min_hefei = 116.41;
double longitude_std_max_hefei = 117.58;

extern int g_verbose;
extern int g_interval;

int gps_suite_init()
{
	int ret;

	ret = QL_LOC_Client_Init(&h_loc);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_LOC_Client_Init failed.ret=%d\n", ret);
		return -1;
	}
	return 0;
}


int gps_suite_clean()
{
	int ret;
	ret = QL_LOC_Client_Deinit(h_loc);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_LOC_Client_Init failed.ret=%d\n", ret);
		return -1;
	}
	return 0;
}

void gps_suite_SetUp()
{
	return;
}

void gps_suite_TearDown()
{
	return;
}

static void ql_loc_rx_ind_msg_cb(loc_client_handle_type  h_loc,
                                 E_QL_LOC_NFY_MSG_ID_T   e_msg_id,
                                 void                    *pv_data,
                                 void                    *contextPtr)
{
	//printFuncPrefix;

	//printFormatMsg("msg_id: %d\n", e_msg_id);

	switch(e_msg_id)
	{
		case E_QL_LOC_NFY_MSG_ID_LOCATION_INFO:
		{
			if(pv_data)
			{
				g_gps_location_update = 1;
				QL_LOC_LOCATION_INFO_T *pt_location = (QL_LOC_LOCATION_INFO_T *)pv_data;
				
				g_loc_latitude = pt_location->latitude; 
				g_loc_longitude = pt_location->longitude;
			}

		}
		break;
		case E_QL_LOC_NFY_MSG_ID_NMEA_INFO:
		{
		}
		break;
		default:
			break;
	}
	return;
}


/********************************TEST CASE START******************************/
#if 1
//TEST_QL_LOC_AddRxIndMsgHandler
static void TEST_QL_LOC_AddRxIndMsgHandler(void)
{
	int ret;

	ret = QL_LOC_AddRxIndMsgHandler(ql_loc_rx_ind_msg_cb, (void*)h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_AddRxIndMsgHandler failed. ret=%d\n", ret);
	}
	return;
}

//TEST_QL_LOC_Set_Indications
static void TEST_QL_LOC_Set_Indications(void)
{
	int bitmask = 0;
	int ret;

	printFuncPrefix;
	
	bitmask |= LOC_IND_LOCATION_INFO_ON;
	bitmask |= LOC_IND_STATUS_INFO_ON;
	bitmask |= LOC_IND_SV_INFO_ON;
	bitmask |= LOC_IND_NMEA_INFO_ON;
	bitmask |= LOC_IND_CAP_INFO_ON;
	bitmask |= LOC_IND_UTC_TIME_REQ_ON;
	bitmask |= LOC_IND_XTRA_DATA_REQ_ON;
	bitmask |= LOC_IND_AGPS_DATA_CONN_CMD_REQ_ON;
	bitmask |= LOC_IND_NI_NFY_USER_RESP_REQ_ON;
	
	ret = QL_LOC_Set_Indications(h_loc, bitmask);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("TEST_QL_LOC_Set_Indications failed. ret=%d\n", ret);
	}
	return;
}

//TEST_QL_LOC_Set_Position_Mode
static void TEST_QL_LOC_Set_Position_Mode(void)
{
	int ret;
	QL_LOC_POS_MODE_INFO_T t_mode = {0};

	printFuncPrefix;
	
	t_mode.mode 				= E_QL_LOC_POS_MODE_STANDALONE;
	t_mode.recurrence			= E_QL_LOC_POS_RECURRENCE_PERIODIC;
	t_mode.min_interval 		= 1000;  //report nmea frequency 1Hz
	t_mode.preferred_accuracy	= 50;	 // <50m
	t_mode.preferred_time		= 90;	 // 90s
	
	ret = QL_LOC_Set_Position_Mode(h_loc, &t_mode);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Set_Position_Mode failed. ret=%d\n", ret);
	}
	return;
}

//QL_LOC_Start_Navigation
static void TEST_QL_LOC_Start_Navigation(void)
{
	int ret;

	printFuncPrefix;

	ret = QL_LOC_Start_Navigation(h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Start_Navigation failed. ret=%d\n", ret);
	}
	return;
}

//QL_LOC_Stop_Navigation
static void TEST_QL_LOC_Stop_Navigation(void)
{
	int ret;

	printFuncPrefix;

	ret = QL_LOC_Stop_Navigation(h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Stop_Navigation failed. ret=%d\n", ret);
	}
	return;
}

//QL_LOC_Delete_Aiding_Data
static void TEST_QL_LOC_Delete_Aiding_Data(void)
{
	int ret, bitmask = 0;

	printFuncPrefix;

	bitmask |= MCM_LOC_DELETE_EPHEMERIS_V01;
	
	ret = QL_LOC_Delete_Aiding_Data(h_loc, bitmask);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Delete_Aiding_Data failed. ret=%d\n", ret);
	}
	return;
}

//QL_LOC_InjectTime

static void TEST_QL_LOC_InjectTime(void)
{
	int ret;
	QL_LOC_INJECT_TIME_INTO_T info;

	printFuncPrefix;
	memset(&info, 0, sizeof(QL_LOC_INJECT_TIME_INTO_T));

	info.time = time(NULL);
	info.time_reference = 100;
	info.uncertainty = 10;

	ret = QL_LOC_InjectTime(h_loc, &info);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_InjectTime failed. ret=%d\n", ret);
	}
	return;
}

//QL_LOC_InjectLocation

static void TEST_QL_LOC_InjectLocation(void)
{
	int ret;
	QL_LOC_INJECT_LOCATION_INTO_T info;

	printFuncPrefix;

	memset(&info, 0, sizeof(QL_LOC_INJECT_LOCATION_INTO_T));
	info.longitude = 117.282699;
    info.latitude  = 31.866942;
    info.accuracy  = 100.0;
    ret = QL_LOC_InjectLocation(h_loc, &info);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_InjectLocation failed. ret=%d\n", ret);
	}
	return;
}

#endif
static void TEST_QL_LOC_GetPositionByCB(void)
{
	//Init
	//AddRxIndMsgHandler
	//SetIndications
	//SetPositionMode
	//StartNavigation
	//cb
	//stopNavigation
	//Deinit
	int ret, bitmask = 0, interval = 0;
	QL_LOC_POS_MODE_INFO_T t_mode = {0};
	
printFuncPrefix;
	ret = QL_LOC_AddRxIndMsgHandler(ql_loc_rx_ind_msg_cb, (void*)h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_AddRxIndMsgHandler failed. ret=%d\n", ret);
		return;
	}

	bitmask |= LOC_IND_LOCATION_INFO_ON;
	bitmask |= LOC_IND_NMEA_INFO_ON;
	
	ret = QL_LOC_Set_Indications(h_loc, bitmask);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Set_Indications failed.ret=%d\n", ret);
		return;
	}

	t_mode.mode 				= E_QL_LOC_POS_MODE_STANDALONE;
	t_mode.recurrence			= E_QL_LOC_POS_RECURRENCE_PERIODIC;
	t_mode.min_interval 		= 1000;  //report nmea frequency 1Hz
	t_mode.preferred_accuracy	= 50;	 // <50m
	t_mode.preferred_time		= 90;	 // 90s
	
	ret = QL_LOC_Set_Position_Mode(h_loc, &t_mode);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Set_Position_Mode failed.ret=%d\n", ret);
		return;
	}

	ret = QL_LOC_Start_Navigation(h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Start_Navigation failed.ret=%d\n", ret);
		return;
	}
	printFormatMsg("Waiting for GPS location:               %02dS", interval);
	do
	{
		sleep(1);
		interval ++;
		printf("\b\b\b%02dS", interval);
		fflush(stdout);
		if(g_gps_location_update == 1)
		{
			printFormatMsg("\n");
			if(g_verbose == 1)
			{
				printFormatMsg("Get Location Info from cb: lat: %lf, lon: %lf\n", g_loc_latitude, g_loc_longitude);
			}
			if(g_loc_latitude >= latitude_std_min_hefei &&
				g_loc_latitude <= latitude_std_max_hefei &&
				 g_loc_longitude >= longitude_std_min_hefei &&
				  g_loc_longitude <= longitude_std_max_hefei)
			{
				printFormatMsg("TEST_QL_LOC_GetPositionByCB success.\n");
				CU_PASS("TEST_QL_LOC_GetPositionByCB success.");
				break;
			}
			else
			{
				printFormatMsg("TEST_QL_LOC_GetPositionByCB failed.\n");
				CU_FAIL("TEST_QL_LOC_GetPositionByCB failed.");
				break;
			}
		}
	}while(interval < g_interval);
	printFormatMsg("\n");
	
	ret = QL_LOC_Stop_Navigation(h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Stop_Navigation failed.ret=%d\n", ret);
	}
	return;
}

static void TEST_QL_LOC_GetCurrentLocation()
{
	//Init
	//AddRxIndMsgHandler
	//SetIndications
	//SetPositionMode
	//GetCurrentLocation
	//Deinit
	int ret;
	QL_LOC_POS_MODE_INFO_T t_mode = {0};
	int timeout_sec = 60;
	QL_LOC_LOCATION_INFO_T  t_loc_info  = {0};
	
	printFuncPrefix;
	ret = QL_LOC_AddRxIndMsgHandler(ql_loc_rx_ind_msg_cb, (void*)h_loc);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_AddRxIndMsgHandler failed.ret=%d\n", ret);
		return;
	}

	t_mode.mode 				= E_QL_LOC_POS_MODE_STANDALONE;
	t_mode.recurrence			= E_QL_LOC_POS_RECURRENCE_SINGLE;
	t_mode.min_interval 		= 1000;  //report nmea frequency 1Hz
	t_mode.preferred_accuracy	= 50;	 // <50m
	t_mode.preferred_time		= 90;	 // 90s
	ret = QL_LOC_Set_Position_Mode(h_loc, &t_mode);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_LOC_Set_Position_Mode failed.ret=%d\n", ret);
		return;
	}

	ret = QL_LOC_Get_Current_Location(h_loc, &t_loc_info, timeout_sec);
	CU_ASSERT(ret > 0);
	if(ret < 0)
	{
		printFormatMsg("QL_LOC_Get_Current_Location failed.ret=%d\n", ret);
		return;
	}
    else
    {
		if(t_loc_info.latitude >= latitude_std_min_hefei && 
			t_loc_info.latitude <= latitude_std_max_hefei &&
			t_loc_info.longitude >= longitude_std_min_hefei &&
			t_loc_info.longitude <= longitude_std_max_hefei)
		{
			printFormatMsg("QL_LOC_Get_Current_Location compare success.\n");
			CU_PASS("QL_LOC_Get_Current_Location compare success.");
		}
		else
		{
			CU_FAIL("QL_LOC_Get_Current_Location compare failed.");
		}
        printFormatMsg("Latitude = %lf, Longitude=%lf, altitude=%lf, accuracy = %lf\n", 
                t_loc_info.latitude, t_loc_info.longitude, t_loc_info.altitude, t_loc_info.accuracy);
    }
	return;
}
/********************************TEST CASE END********************************/

/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo gps_suite_case[] = {
	{"test QL_LOC_AddRxIndMsgHandler", TEST_QL_LOC_AddRxIndMsgHandler},
	{"test QL_LOC_Set_Indications", TEST_QL_LOC_Set_Indications},
	{"test QL_LOC_Set_Position_Mode", TEST_QL_LOC_Set_Position_Mode},
	{"test QL_LOC_Start_Navigation", TEST_QL_LOC_Start_Navigation},
	{"test QL_LOC_Stop_Navigation", TEST_QL_LOC_Stop_Navigation},
	{"test QL_LOC_Delete_Aiding_Data", TEST_QL_LOC_Delete_Aiding_Data},
	{"test QL_LOC_InjectTime", TEST_QL_LOC_InjectTime},
	{"test QL_LOC_InjectLocation", TEST_QL_LOC_InjectLocation},
	CU_TEST_INFO_NULL,
};

static CU_TestInfo gps_2_suite_case[] = {
	{"test QL_LOC_GetPositionByCB", TEST_QL_LOC_GetPositionByCB},
	{"test QL_LOC_GetCurrentLocation", TEST_QL_LOC_GetCurrentLocation},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo gps_suites[] = {
	{"gps suite", gps_suite_init, gps_suite_clean, gps_suite_SetUp, gps_suite_TearDown, gps_suite_case},
	CU_SUITE_INFO_NULL,
};

CU_SuiteInfo gps2_suites[] = {
	{"gps_suite", gps_suite_init, gps_suite_clean, gps_suite_SetUp, gps_suite_TearDown, gps_2_suite_case},
	CU_SUITE_INFO_NULL,
};


