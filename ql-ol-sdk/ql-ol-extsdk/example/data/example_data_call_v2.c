/**
 * @file example_data_call_v2.c
 * @brief Quectel Openlinux Data call examples.
 * 
 * @note 
 *
 * @copyright Copyright (c) 2009-2017 @ Quectel Wireless Solutions Co., Ltd.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <unistd.h>
#include "ql_wwan_v2.h"

static void data_call_state_callback(ql_data_call_state_s *state)
{
	printf("profile id %d ", state->profile_idx);
	printf("IP family %s ", QL_DATA_CALL_TYPE_IPV4 == state->ip_family ? "v4" : "v6");
	if(QL_DATA_CALL_CONNECTED == state->state) {
		printf("is Connected\n");
		printf("Interface Name: %s\n", state->name);
		if(QL_DATA_CALL_TYPE_IPV4 == state->ip_family) {
			printf("IP address:          %s\n", inet_ntoa(state->v4.ip));
			printf("Gateway address:     %s\n", inet_ntoa(state->v4.gateway));
			printf("Primary DNS address: %s\n", inet_ntoa(state->v4.pri_dns));
			printf("Second DNS address:  %s\n", inet_ntoa(state->v4.sec_dns));
		} else {
			char ipv6_buffer[INET6_ADDRSTRLEN];
			inet_ntop(AF_INET6, (void *)&state->v6.ip, ipv6_buffer, INET6_ADDRSTRLEN);
			printf("IP address:          %s\n", ipv6_buffer);
			inet_ntop(AF_INET6, (void *)&state->v6.gateway, ipv6_buffer, INET6_ADDRSTRLEN);
			printf("Gateway address:     %s\n", ipv6_buffer);
			inet_ntop(AF_INET6, (void *)&state->v6.pri_dns, ipv6_buffer, INET6_ADDRSTRLEN);
			printf("Primary DNS address: %s\n", ipv6_buffer);
			inet_ntop(AF_INET6, (void *)&state->v6.sec_dns, ipv6_buffer, INET6_ADDRSTRLEN);
			printf("Second DNS address:  %s\n", ipv6_buffer);
		}
		printf("\n");
	} else {
		printf("is disconnected, and reason code 0x%x\n", state->err);
	}
}

int main(int argc, char **argv)
{
    int retry = 10;
    int loop;
    ql_data_call_s data_call[3];
    ql_data_call_info_s data_call_info;
    ql_data_call_error_e err = QL_DATA_CALL_ERROR_NONE;

    memset(&data_call, 0, sizeof(data_call));

    /*
     * The dialup API relies on the Quectel Manager service. If the program is not initialized successfully, 
     * debugging these API interfaces will fail, so here is judged whether the service is started normally.
     */
    while(0 != QL_Data_Call_Init_Precondition() && 0 != retry) {
        printf("The Quectel manager service is not initialized, about 500ms try again.\n");
        usleep(500*1000);
        retry--;
    }

    if(0 == retry) {
        printf("Data call failure\n");
        exit(0);
    }

    if(QL_Data_Call_Init(data_call_state_callback)) {
        printf("Initialization data call failure\n");
        exit(0);
    }

    for(loop = 0; loop < sizeof(data_call)/sizeof(data_call[0]); loop++) {
        memset(&data_call_info, 0, sizeof(data_call_info));
        err = QL_DATA_CALL_ERROR_NONE;
        data_call[loop].profile_idx = loop+1;
        /*
         * If your data call program is coredump, the data call status will not disappear automatically. 
         * When your program is start again, you need to call the QL_Data_Call_Info_Get interface to get 
         * the data call status. Because it is already in the data call state, you call QL_Data_Call_Start 
         * again without callback function
         */
        if(QL_Data_Call_Info_Get(data_call[loop].profile_idx, QL_DATA_CALL_TYPE_IPV4, &data_call_info, &err)) {
            printf("get profile index %d information failure: errno 0x%x\n", data_call[loop].profile_idx, err);
            continue;
        }
        if(QL_DATA_CALL_CONNECTED == data_call_info.v4.state) {
            printf("the profile index %d is already connected, don't up\n", data_call[loop].profile_idx);
            continue;
        }
        data_call[loop].ip_family = QL_DATA_CALL_TYPE_IPV4;
        data_call[loop].reconnect = true;
        err = QL_DATA_CALL_ERROR_NONE;
        if(QL_Data_Call_Start(&data_call[loop], &err)) {
            printf("the profile index %d start data call failure: 0x%x\n", data_call[loop].profile_idx, err);
            
        }
        printf("the profile index %d start data call success\n", data_call[loop].profile_idx);
        usleep(500*1000);
    }
    sleep(3600);
    return 0;
}

