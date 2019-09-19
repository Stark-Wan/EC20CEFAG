#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/Automated.h>
#include <CUnit/Console.h>


#include "testconf.h"
#include "nw_suite.h"
#include "wwanv2_suite.h"
#include "sim_suite.h"
#include "dm_suite.h"
#include "sms_suite.h"
#include "voice_suite.h"
#include "gps_suite.h"
#include "device_suite.h"


static int nw_suite_validate		= 1;
static int wwanv2_suite_validate	= 1;
static int sim_suite_validate 		= 1;
static int dm_suite_validate 		= 1;
static int sms_suite_validate 		= 1;
static int voice_suite_validate		= 1;
static int gps_suite_validate 		= 1;
static int device_suite_validate 	= 1;

static int gps_2_suite_validate 	= 0;

/************************************************/
//global variable
char g_dest_phone_number[32] = {0};
int  g_interval = 60;
int  g_verbose = 0;
int  g_reply_sms_times = 1;



/***********************************************/




void AddTest()
{
	int count = 0;
	assert(NULL != CU_get_registry());
	assert(!CU_is_test_running());


	if(nw_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(nw_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [NETWORK] suites...\n");
	}
	if(wwanv2_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(wwanv2_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [WWANv2] suites...\n");
	}
	if(sim_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(sim_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [SIM] suites...\n");
	}
	if(dm_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(dm_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [DM] suites...\n");
	}
	if(sms_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(sms_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [SMS] suites...\n");
	}
	if(voice_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(voice_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [VOICE] suites...\n");
	}
	if(gps_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(gps_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [GPS] suites...\n");
	}
	if(gps_2_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(gps2_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [GPS2] suites...\n");
	}
	if(device_suite_validate == 1)
	{
		if(CUE_SUCCESS != CU_register_suites(device_suites))
		{
			fprintf(stderr, "suite registration failed - %s\n", CU_get_error_msg());
			exit(EXIT_FAILURE);
		}
		count++;
		printf("Load [DEVICE] suites...\n");
	}
	printf("load [%d] suites total.\n", count);
}

void usage()
{
	printf("usage:\ntest_case [options]\n"
					"\t-v --verbose, print verbose info\n"
					"\t-p --phone, set dest phone number to send sms messages or send a voice call\n"
					"\t-i --interval, set times to wait sms reply or call[default 60]\n"
					"\t-r --reply, send sms reply times, less than 5 times [default 1]\n"
					"\t-g --gps, test gps with real location [default off]\n"
					"\teg. test_case --verbose --phone=180XXXXXXXX --interval=60 --reply=3\n");
}



int main(int argc, char *argv[])
{
	int opt, opt_index;
	CU_BasicRunMode mode = CU_BRM_VERBOSE;
	CU_ErrorAction error_action = CUEA_IGNORE;
	static struct option long_option[] = {
		{"verbose", no_argument, &g_verbose, 1},
		{"phone", required_argument, NULL, 'p'},
		{"interval", required_argument, NULL, 'i'},
		{"gps", no_argument, &gps_2_suite_validate, 1},
		{"reply", required_argument, NULL, 'r'},
		{"help", no_argument, NULL, 'h'},
		{0, 0, 0, 0},
	};
	while((opt = getopt_long(argc, argv, "p:i:r:", long_option, &opt_index)) != -1)
	{
		switch(opt)
		{
			case 0:
				break;
			case 'h':
				usage();
				exit(0);
			case 'p':
				//printDebugFormatMsg("phone number has been set.[%s]\n", optarg);
				if(optarg != NULL)
				{
					strncpy(g_dest_phone_number, optarg, sizeof(g_dest_phone_number));
				}
				else
				{
					printf("please input phone number.\n");
					usage();
					exit(1);
				}
				break;
			case 'i':
				//printDebugFormatMsg("reply sms and recall interval has been set, [%s]\n", optarg);
				if(optarg != NULL)
				{
					g_interval = strtoul(optarg, NULL, 0);
				}
				else
				{
					printf("please input interval.\n");
					usage();
					exit(1);
				}
				break;
			case 'r':
				//printDebugFormatMsg("reply sms and recall interval has been set, [%s]\n", optarg);
				g_reply_sms_times = strtoul(optarg, NULL, 0);
				if(g_reply_sms_times > 5)
				{
					printf("sms reply times must less than 5.\n");
					exit(1);
				}
				break;
			case '?':
			default:
				usage();
				exit(1);
		}
	}

	if(optind != argc) {
		fprintf(stderr, "Expected argument after options\n"); 
		usage();
		exit(1);
	}
	if(sms_suite_validate == 1 || voice_suite_validate == 1)
	{
		if(strlen(g_dest_phone_number) <= 0)
		{
			fprintf(stderr, "dest phone number must be set.\n");
			usage();
			exit(1);
		}
		if(g_reply_sms_times <= 0)
		{
			fprintf(stderr, "dest phone number must be set.\n");
			usage();
			exit(1);
		}
	}
	
	if (CU_initialize_registry())
	{
    	printf("\nInitialization of Test Registry failed.");
 	}
	else
	{
		AddTest();
		CU_basic_set_mode(mode);
		CU_set_error_action(error_action);
   	 	printf("\nTests completed with return value %d.\n", CU_basic_run_tests());
    	CU_cleanup_registry();
	}
	
	return 0;
}
