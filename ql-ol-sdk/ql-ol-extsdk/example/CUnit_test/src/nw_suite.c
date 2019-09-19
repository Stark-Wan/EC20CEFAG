#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "nw_suite.h"
#include "testconf.h"


nw_client_handle_type h_nw = 0;
extern int g_verbose;



/*
MCM client must initional first
so QL_MCM_NW_Client_Init() called in suite_init()
*/

int nw_suite_init()
{
	int ret;
	
	ret = QL_MCM_NW_Client_Init(&h_nw);

	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_MCM_NW_Client_Init failed. ret=%d\n", ret);
		return -1;
	}
	return 0;
}


int nw_suite_clean()
{
	int ret;

	ret = QL_MCM_NW_Client_Deinit(h_nw);
	if(ret != MCM_SUCCESS_V01)
	{
		printErrMsg("QL_MCM_NW_Client_Deinit failed. ret=%d\n", ret);
		return -1;
	}
	return 0;
}

void nw_suite_SetUp()
{
	return;
}

void nw_suite_TearDown()
{
	return;
}

//QL_MCM_NW_MODE_GSM      0x01 
//QL_MCM_NW_MODE_WCDMA    0x02
//QL_MCM_NW_MODE_CDMA     0x04
//QL_MCM_NW_MODE_EVDO     0x08
//QL_MCM_NW_MODE_LTE      0x10
//QL_MCM_NW_MODE_TDSCDMA  0x20
//QL_MCM_NW_MODE_PRL      0x10000

void nw_mode_spilt(uint64_t mode)
{
	if(mode > 0)
	{
		printFormatMsg("nw_mode: %lld, split as: ", mode);
		if(mode & QL_MCM_NW_MODE_GSM)
		{
			printFormatMsg("GSM ");
		}
		if(mode & QL_MCM_NW_MODE_WCDMA)
		{
			printFormatMsg("WCDMA ");
		}
		if(mode & QL_MCM_NW_MODE_CDMA)
		{
			printFormatMsg("CDMA ");
		}
		if(mode & QL_MCM_NW_MODE_EVDO)
		{
			printFormatMsg("EVDO ");
		}
		if(mode & QL_MCM_NW_MODE_LTE)
		{
			printFormatMsg("LTE ");
		}
		if(mode & QL_MCM_NW_MODE_TDSCDMA)
		{
			printFormatMsg("TDSCDMA ");
		}
		if(mode & QL_MCM_NW_MODE_PRL)
		{
			printFormatMsg("PRL ");
		}
		printFormatMsg("\n");
	}
}
/********************************TEST CASE START******************************/

//QL_MCM_NW_Config
static void TEST_QL_MCM_NW_GetConfig(void)
{
	int ret;
	
	QL_MCM_NW_CONFIG_INFO_T info = {0};

	printFuncPrefix;

	//getconfig
    ret = QL_MCM_NW_GetConfig(h_nw, &info);
	
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_NW_GetConfig failed.ret=%d\n", ret);
		return;
	}
	
	//preferred_nw_mode
	//network mode none,gsm,wcdma,cdma eveo lte tdscdma prl...
	CU_ASSERT(info.preferred_nw_mode != MCM_MODE_NONE_V01);
	
	CU_ASSERT(info.roaming_pref == E_QL_MCM_NW_ROAM_STATE_ON ||
				info.roaming_pref != E_QL_MCM_NW_ROAM_STATE_OFF);

	printFormatMsg("ret = %d, nw_mode: %lld, roaming: %d\n", ret, info.preferred_nw_mode, info.roaming_pref);
	if(g_verbose == 1)
	{
		nw_mode_spilt(info.preferred_nw_mode);
	}
	
	return;
}


//QL_MCM_NW_GetNitzTimeInfo
static void TEST_QL_MCM_NW_GetNitzTimeInfo(void)
{
	int ret;
	QL_MCM_NW_NITZ_TIME_INFO_T info;

	printFuncPrefix;
	memset(&info, 0, sizeof(QL_MCM_NW_NITZ_TIME_INFO_T));
	ret = QL_MCM_NW_GetNitzTimeInfo(h_nw, &info);
	
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_NW_GetNitzTimeInfo failed.ret=%d\n", ret);
		return;
	}

	CU_ASSERT(info.abs_time >= 0);
	CU_ASSERT(info.leap_sec >= 0);

	printFormatMsg("NitzTime: %s, abs_time: %lld, leap_sec: %d\n",
				info.nitz_time, info.abs_time, info.leap_sec);
	return;
}

//QL_MCM_NW_EventRegister
//how to check? i have no idea! skip

//QL_MCM_NW_GetOperatorName
static void TEST_QL_MCM_NW_GetOperatorName(void)
{
	int ret;
	QL_MCM_NW_OPERATOR_NAME_INFO_T info;

	printFuncPrefix;
	memset(&info, 0, sizeof(QL_MCM_NW_OPERATOR_NAME_INFO_T));
	//long_eons short_eons mcc mnc
	ret = QL_MCM_NW_GetOperatorName(h_nw, &info);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_NW_GetOperatorName failed.ret=%d\n", ret);
		return;
	}
	CU_ASSERT_STRING_EQUAL(info.mcc, "460");
	CU_ASSERT(strlen(info.mnc) == 2);

	printFormatMsg("long_eons:%s short_eons:%s mcc:%s mnc:%s \n",
							info.long_eons, info.short_eons, info.mcc, info.mnc);
	return;
}


/**
QL_MCM_NW_GetRegStatus
*/
static void TEST_QL_MCM_NW_GetRegStatus(void)
{
	int ret;
	QL_MCM_NW_REG_STATUS_INFO_T info = {0};
	const char *tech_domain[] = {"NONE", "3GPP", "3GPP2"};
	const char *radio_tech[] = {"TD_SCDMA","GSM","HSPAP","LTE",
								  "EHRPD", "EVDO_B", "HSPA","HSUPA",
								  "HSDPA","EVDO_A","EVDO_0", "1xRTT",
								  "IS95B","IS95A","UMTS","EDGE",
								  "GPRS","NONE"};
	const char *roaming[] = {"OFF","ON"};
	const char *registration_state[] = {"NONE","LIMITED","FULL"};
	printFuncPrefix;
	
	ret = QL_MCM_NW_GetRegStatus(h_nw, &info);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_NW_GetRegStatus failed.ret=%d\n", ret);
	}

	printFormatMsg("voice_registration\n\ttech_domain:%s, radio_tech:%s, roaming:%s, state:%s\n",
					tech_domain[info.voice_registration.tech_domain], 
					radio_tech[info.voice_registration.radio_tech],
					roaming[info.voice_registration.roaming],
					registration_state[info.voice_registration.registration_state]);
	printFormatMsg("data_registration\n\ttech_domain:%s, radio_tech:%s, roaming:%s, state:%s\n",
					tech_domain[info.data_registration.tech_domain],
					radio_tech[info.data_registration.radio_tech],
					roaming[info.data_registration.roaming],
					registration_state[info.data_registration.registration_state]);
	CU_ASSERT(info.voice_registration.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP || 
				info.voice_registration.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP2);
	
	CU_ASSERT(info.voice_registration.radio_tech >= E_QL_MCM_NW_RADIO_TECH_TD_SCDMA &&
				info.voice_registration.radio_tech < E_QL_MCM_NW_RADIO_TECH_NONE);
	
	CU_ASSERT(info.voice_registration.roaming == E_QL_MCM_NW_ROAM_STATE_ON || 
					info.voice_registration.roaming == E_QL_MCM_NW_ROAM_STATE_OFF);
	
	CU_ASSERT(info.voice_registration.registration_state == E_QL_MCM_NW_SERVICE_FULL);

	
	CU_ASSERT(info.data_registration.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP || 
				info.data_registration.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP2);
	
	CU_ASSERT(info.data_registration.radio_tech >= E_QL_MCM_NW_RADIO_TECH_TD_SCDMA &&
				info.data_registration.radio_tech < E_QL_MCM_NW_RADIO_TECH_NONE);
	
	CU_ASSERT(info.data_registration.roaming == E_QL_MCM_NW_ROAM_STATE_ON || 
			info.data_registration.roaming == E_QL_MCM_NW_ROAM_STATE_OFF);
	
	CU_ASSERT(info.data_registration.registration_state == E_QL_MCM_NW_SERVICE_FULL);

//	  voice_registration_details_3gpp
//	  info.voice_registration_details_3gpp.mcc,
//    info.voice_registration_details_3gpp.mnc,
//    info.voice_registration_details_3gpp.roaming,
//Forbidden: 0 -- No, 1 -- Yes.
//    info.voice_registration_details_3gpp.forbidden, 
//Cell Identity 0-65535
//    info.voice_registration_details_3gpp.cid,
//Location Area Code
//    info.voice_registration_details_3gpp.lac,
//Primary scrambling code, just for WCDMA, 0 is none
//    info.voice_registration_details_3gpp.psc,
//Tracking area code information for LTE
//    info.voice_registration_details_3gpp.tac
	if(info.voice_registration_details_3gpp_valid)
	{

		CU_ASSERT(info.voice_registration_details_3gpp.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP || 
					info.voice_registration_details_3gpp.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP2);
		
		CU_ASSERT(info.voice_registration_details_3gpp.radio_tech >= E_QL_MCM_NW_RADIO_TECH_TD_SCDMA &&
					info.voice_registration_details_3gpp.radio_tech < E_QL_MCM_NW_RADIO_TECH_NONE);
		
		CU_ASSERT(strlen(info.voice_registration_details_3gpp.mcc) == 3);
		CU_ASSERT_STRING_EQUAL(info.voice_registration_details_3gpp.mcc, "460");
		CU_ASSERT(strlen(info.voice_registration_details_3gpp.mnc) == 2);
		CU_ASSERT(info.voice_registration_details_3gpp.roaming == E_QL_MCM_NW_ROAM_STATE_ON || 
				info.voice_registration_details_3gpp.roaming == E_QL_MCM_NW_ROAM_STATE_OFF);

		CU_ASSERT(info.voice_registration_details_3gpp.forbidden == 0 || 
					info.voice_registration_details_3gpp.forbidden == 1);

		CU_ASSERT(info.voice_registration_details_3gpp.cid >= 0 && info.voice_registration_details_3gpp.cid <= UINT32_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp.lac >= 0 && info.voice_registration_details_3gpp.lac <= UINT16_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp.psc >= 0 && info.voice_registration_details_3gpp.psc <= UINT16_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp.tac >= 0 && info.voice_registration_details_3gpp.tac <= UINT16_MAX);
	}

	//data_registration_details_3gpp
	if(info.data_registration_details_3gpp_valid)
	{
			CU_ASSERT(info.data_registration_details_3gpp.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP || 
					info.data_registration_details_3gpp.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP2);
		
			CU_ASSERT(info.data_registration_details_3gpp.radio_tech >= E_QL_MCM_NW_RADIO_TECH_TD_SCDMA &&
					info.data_registration_details_3gpp.radio_tech < E_QL_MCM_NW_RADIO_TECH_NONE);
			CU_ASSERT(strlen(info.data_registration_details_3gpp.mcc) == 3);
			CU_ASSERT_STRING_EQUAL(info.data_registration_details_3gpp.mcc, "460");
			CU_ASSERT(strlen(info.data_registration_details_3gpp.mnc) == 2);

			CU_ASSERT(info.data_registration_details_3gpp.roaming == E_QL_MCM_NW_ROAM_STATE_ON || 
					info.data_registration_details_3gpp.roaming == E_QL_MCM_NW_ROAM_STATE_OFF);
		
			CU_ASSERT(info.data_registration_details_3gpp.forbidden == 0 || 
						info.data_registration_details_3gpp.forbidden == 1);
		
			CU_ASSERT(info.data_registration_details_3gpp.cid >= 0 && info.data_registration_details_3gpp.cid <= UINT32_MAX);
			CU_ASSERT(info.data_registration_details_3gpp.lac >= 0 && info.data_registration_details_3gpp.lac <= UINT16_MAX);
			CU_ASSERT(info.data_registration_details_3gpp.psc >= 0 && info.data_registration_details_3gpp.psc <= UINT16_MAX);
			CU_ASSERT(info.data_registration_details_3gpp.tac >= 0 && info.data_registration_details_3gpp.tac <= UINT16_MAX);
	}
	//voice_registration_details_3gpp2
	//uint8_t inPRL : 0 -- Not in PRL, 1 -- In PRL
	//uint8_t css: Concurrent services supported: 0 -- No, 1 -- Yes
	//UINT16_t sid: CDMA system ID
	//UINT16_t nid: CDMA network ID
	//UINT16_t bsid: Base station ID
	if(info.voice_registration_details_3gpp2_valid)
	{
		CU_ASSERT(info.voice_registration_details_3gpp2.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP || 
				info.voice_registration_details_3gpp2.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP2);

		CU_ASSERT(info.voice_registration_details_3gpp2.radio_tech >= E_QL_MCM_NW_RADIO_TECH_TD_SCDMA &&
				info.voice_registration_details_3gpp2.radio_tech < E_QL_MCM_NW_RADIO_TECH_NONE);

		CU_ASSERT(strlen(info.voice_registration_details_3gpp2.mcc) == 3);
		CU_ASSERT_STRING_EQUAL(info.voice_registration_details_3gpp2.mcc, "460");
		CU_ASSERT(strlen(info.voice_registration_details_3gpp2.mnc) == 2);

		CU_ASSERT(info.voice_registration_details_3gpp2.roaming == E_QL_MCM_NW_ROAM_STATE_ON || 
				info.voice_registration_details_3gpp2.roaming == E_QL_MCM_NW_ROAM_STATE_OFF);

		CU_ASSERT(info.voice_registration_details_3gpp2.forbidden == 0 || 
					info.voice_registration_details_3gpp2.forbidden == 1);

		CU_ASSERT(info.voice_registration_details_3gpp2.inPRL >= 0 && info.voice_registration_details_3gpp2.inPRL <= UINT8_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp2.css >= 0 && info.voice_registration_details_3gpp2.css <= UINT8_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp2.sid >= 0 && info.voice_registration_details_3gpp2.sid <= UINT16_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp2.nid >= 0 && info.voice_registration_details_3gpp2.nid <= UINT16_MAX);
		CU_ASSERT(info.voice_registration_details_3gpp2.bsid >= 0 && info.voice_registration_details_3gpp2.bsid <= UINT16_MAX);
	}
		//data_registration_details_3gpp2
	if(info.data_registration_details_3gpp2_valid)
	{
		CU_ASSERT(info.data_registration_details_3gpp2.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP || 
				info.data_registration_details_3gpp2.tech_domain == E_QL_MCM_NW_TECH_DOMAIN_3GPP2);
	
		CU_ASSERT(info.data_registration_details_3gpp2.radio_tech >= E_QL_MCM_NW_RADIO_TECH_TD_SCDMA &&
				info.data_registration_details_3gpp2.radio_tech < E_QL_MCM_NW_RADIO_TECH_NONE);
		
		CU_ASSERT(strlen(info.data_registration_details_3gpp2.mcc) == 3);
		CU_ASSERT_STRING_EQUAL(info.data_registration_details_3gpp2.mcc, "460");
		CU_ASSERT(strlen(info.data_registration_details_3gpp2.mnc) == 2);

		CU_ASSERT(info.data_registration_details_3gpp2.roaming == E_QL_MCM_NW_ROAM_STATE_ON || 
				info.data_registration_details_3gpp2.roaming == E_QL_MCM_NW_ROAM_STATE_OFF);
	
		CU_ASSERT(info.data_registration_details_3gpp2.forbidden == 0 || 
					info.data_registration_details_3gpp2.forbidden == 1);
	
		CU_ASSERT(info.data_registration_details_3gpp2.inPRL >= 0 && info.data_registration_details_3gpp2.inPRL <= UINT8_MAX);
		CU_ASSERT(info.data_registration_details_3gpp2.css >= 0 && info.data_registration_details_3gpp2.css <= UINT8_MAX);
		CU_ASSERT(info.data_registration_details_3gpp2.sid >= 0 && info.data_registration_details_3gpp2.sid <= UINT16_MAX);
		CU_ASSERT(info.data_registration_details_3gpp2.nid >= 0 && info.data_registration_details_3gpp2.nid <= UINT16_MAX);
		CU_ASSERT(info.data_registration_details_3gpp2.bsid >= 0 && info.data_registration_details_3gpp2.bsid <= UINT16_MAX);
	}
	return;
	
}

//QL_MCM_NW_GetSignalStrength
static void TEST_QL_MCM_NW_GetSignalStrength(void)
{
	int ret;
	QL_MCM_NW_SIGNAL_STRENGTH_INFO_T info = {0};
	
	printFuncPrefix;
	
	ret = QL_MCM_NW_GetSignalStrength(h_nw, &info);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_NW_GetSignalStrength failed.ret=%d\n", ret);
		return;
	}
	if(info.gsm_sig_info_valid)
	{
		CU_ASSERT(info.gsm_sig_info.rssi >= INT8_MIN && info.gsm_sig_info.rssi <= INT8_MAX);

		printFormatMsg("gsm_sig_info  rssi: %d\n", info.gsm_sig_info.rssi);

	}
	if(info.wcdma_sig_info_valid)
	{
		CU_ASSERT(info.wcdma_sig_info.rssi >= INT8_MIN && info.wcdma_sig_info.rssi <= INT8_MAX);
		CU_ASSERT(info.wcdma_sig_info.ecio >= INT16_MIN && info.wcdma_sig_info.ecio <= INT16_MAX);

		printFormatMsg("wcdma_sig_info  rssi: %d, ecio: %d\n", 
							info.wcdma_sig_info.rssi, info.wcdma_sig_info.ecio);
	}
	if(info.tdscdma_sig_info_valid)
	{
		CU_ASSERT(info.tdscdma_sig_info.rssi >= INT8_MIN && info.tdscdma_sig_info.rssi <= INT8_MAX);
		CU_ASSERT(info.tdscdma_sig_info.rscp >= INT8_MIN && info.tdscdma_sig_info.rscp <= INT8_MAX);
		CU_ASSERT(info.tdscdma_sig_info.ecio >= INT16_MIN && info.tdscdma_sig_info.ecio <= INT16_MAX);
		CU_ASSERT(info.tdscdma_sig_info.sinr >= INT8_MIN && info.tdscdma_sig_info.sinr <= INT8_MAX);

		printFormatMsg("tdscdma_sig_info  rssi: %d, rscp: %d, ecio: %d sinr: %d\n",
											info.tdscdma_sig_info.rssi, info.tdscdma_sig_info.rscp,
											info.tdscdma_sig_info.ecio, info.tdscdma_sig_info.sinr);
	}
	if(info.lte_sig_info_valid)
	{
		CU_ASSERT(info.lte_sig_info.rssi >= INT8_MIN && info.lte_sig_info.rssi <= INT8_MAX);
		CU_ASSERT(info.lte_sig_info.rsrq >= INT8_MIN && info.lte_sig_info.rsrq <= INT8_MAX);
		CU_ASSERT(info.lte_sig_info.rsrp >= INT16_MIN && info.lte_sig_info.rsrp <= INT16_MAX);
		CU_ASSERT(info.lte_sig_info.snr >= INT16_MIN && info.lte_sig_info.snr <= INT16_MAX);
		printFormatMsg("lte_sig_info  rssi: %d, rsrq: %d, rsrp: %d, snr: %d\n",
											info.lte_sig_info.rssi, info.lte_sig_info.rsrq,
											info.lte_sig_info.rsrp, info.lte_sig_info.snr);
	}
	if(info.cdma_sig_info_valid)
	{
		CU_ASSERT(info.cdma_sig_info.rssi >= INT8_MIN && info.cdma_sig_info.rssi <= INT8_MAX);
		CU_ASSERT(info.cdma_sig_info.ecio >= INT16_MIN && info.cdma_sig_info.ecio <= INT16_MAX);
		printFormatMsg("cdma_sig_info  rssi: %d, ecio: %d\n", 
								info.cdma_sig_info.rssi, info.cdma_sig_info.ecio);
	}

	if(info.hdr_sig_info_valid)
	{
		CU_ASSERT(info.hdr_sig_info.rssi >= INT8_MIN && info.hdr_sig_info.rssi <= INT8_MAX);
		CU_ASSERT(info.hdr_sig_info.ecio >= INT16_MIN && info.hdr_sig_info.ecio <= INT16_MAX);
		CU_ASSERT(info.hdr_sig_info.sinr >= INT8_MIN && info.hdr_sig_info.sinr <= INT8_MAX);
		CU_ASSERT(info.hdr_sig_info.io >= INT32_MIN && info.hdr_sig_info.io <= INT32_MAX);
		printFormatMsg("hdr_sig_info  rssi: %d, ecio: %d, sinr: %d, io: %d\n",
											info.hdr_sig_info.rssi, info.hdr_sig_info.ecio,
											info.hdr_sig_info.sinr, info.hdr_sig_info.io);
	}
}

//
//QL_MCM_NW_GetCellAccessState
static void TEST_QL_MCM_NW_GetCellAccessState(void)
{
	int ret;
	E_QL_MCM_NW_CELL_ACCESS_STATE_TYPE_T e_state;

	printFuncPrefix;

	ret = QL_MCM_NW_GetCellAccessState(h_nw, &e_state);

	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_MCM_NW_GetCellAccessState failed.ret=%d\n", ret);
		return;
	}

	CU_ASSERT_EQUAL(e_state, E_QL_MCM_NW_CELL_ACCESS_ALL_CALLS);

	printFormatMsg("CellAccessState: %d\n", e_state);

	return;
}


/********************************TEST CASE end********************************/

/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo nw_suite_case[] = {
  {"test QL_MCM_NW_GetConfig", TEST_QL_MCM_NW_GetConfig},
  {"test QL_MCM_NW_GetNitzTimeInfo", TEST_QL_MCM_NW_GetNitzTimeInfo},
  {"test QL_MCM_NW_GetOperatorName", TEST_QL_MCM_NW_GetOperatorName},
  {"test QL_MCM_NW_GetRegStatus", TEST_QL_MCM_NW_GetRegStatus},
  {"test QL_MCM_NW_GetSignalStrength", TEST_QL_MCM_NW_GetSignalStrength},
  {"test QL_MCM_NW_GetCellAccessState", TEST_QL_MCM_NW_GetCellAccessState},
  CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo nw_suites[] = {
	{"nw suite", nw_suite_init, nw_suite_clean, nw_suite_SetUp, nw_suite_TearDown, nw_suite_case},
	CU_SUITE_INFO_NULL,
};


