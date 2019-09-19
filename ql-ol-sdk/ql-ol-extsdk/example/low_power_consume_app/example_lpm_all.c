/*
 *@file: just a demo, for reference only. the demo in consist of ext_interrupt, sms, voice and data methods to wakeup 4G module, 
 *	 maybe user just need one or two methods in it; In addition it is necessary for user to call "Ql_SLP_WakeLock_Lock()" in
 *	 the beginning of ext_interrupt/sms/voice/data callback for keeping 4G module awake, and then deal with other things.
 *
*@date     2018-08-30
 *@author   gale
 *@brief    the function is suitable for this product: 
 *		 __________                 ________
 *	sms  -->| Quectel  |<--wakeupin----|Customer| 
 *	voice-->| 4G module|               |  MCU   |
 *	data -->|__________|---wakeupout-->|________|
 *@Default:
 *          EC20xx: wakeupin pin62(input), rising to wakeup 4G module; wakeupout pin5  (output), rising to wakeup mcu.
 *          AG35xx: wakeupin pin61(input), rising to wakeup 4G module; wakeupout pin147(output), rising to wakeup mcu.
*/

#include <ql_oe.h>
#include <ql_lpm.h>

int ret = 0;

static sms_client_handle_type      h_sms            = 0;

static voice_client_handle_type    h_voice          = 0;

static ql_data_call_s g_call = {
	.profile_idx = 1,
	.reconnect = true,
	.ip_family = QL_DATA_CALL_TYPE_IPV4,
};

static int g_ql_lpm_wakelock_flag = 0;
static int g_ql_lpm_wakelock_fd = -1;
static int g_ql_lpm_wakeupout_pin = 5;	/* wakeupout(EC20xx is pin 5), in general, user need to cntrol when module is waken by ext_interrupt, sms, voice, or data */


/******************************* ql data*************************************/
void data_rev_process(void *params)
{
    int     sockfd          = (int)params;
    int     len             = 0;
    char    ack_msg[64]     = {0};
    char    rcv_buf[128]    = {0};
    struct  timespec time = {0, 0};
   
    while(1)
    {
        len = recv(sockfd, rcv_buf, sizeof(rcv_buf), 0);
        if(g_ql_lpm_wakelock_flag == 0)
        {
            if (Ql_SLP_WakeLock_Lock(g_ql_lpm_wakelock_fd) != 0)
            {
                Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
                printf("Lock wakelock failed! \n");
                return;
            }
            //ret = QL_MCM_NW_SetLowPowerMode(h_nw, 0);//Turn on some qmi indication(eg. Radio change) after wakeup module.
            //printf("QL_MCM_NW_SetLowPowerMode ret = %d\n", ret);
            //changed by javen:update the interface
            ret = QL_NW_ForbidInd(0);
            printf("QL_NW_ForbidInd ret = %d\n", ret);
            /* Control the wakeup_out pin output high level to notify mcu that I`m awakened. */
            Ql_GPIO_SetLevel(g_ql_lpm_wakeupout_pin, PINLEVEL_HIGH);
            printf("wakeup_out pin output high level to notify mcu that I`m awakened.\n");
            g_ql_lpm_wakelock_flag = 1;
        }

        if(len > 0)
        {
            clock_gettime(CLOCK_REALTIME, &time);
            printf("###Msg from server: %s\n", rcv_buf);
            printf("####Client Got msg time: tick=%d.%d\n", (int)time.tv_sec, (int)time.tv_nsec);

            snprintf(ack_msg, sizeof(ack_msg), "%s", rcv_buf);

            len = send(sockfd, ack_msg, strlen(ack_msg), 0);
            if (len < 0)
            {
                printf("Message '%s' failed to send ! "
                        "The error code is %d, error message '%s'\n",
                        ack_msg, errno, strerror(errno));
            }
            else
            {
                printf("News: module >>> Ack to server!!!\n");
            }
        }

    }
}

static void data_call_state_callback(ql_data_call_state_s *state)
{
	char command[128];

	if(g_call.profile_idx == state->profile_idx) {
		printf("profile id %d ", g_call.profile_idx);
		printf("IP family %s ", QL_DATA_CALL_TYPE_IPV4 == state->ip_family ? "v4" : "v6");
		if(QL_DATA_CALL_CONNECTED == state->state) {
			printf("is Connected\n");
			printf("Interface Name: %s\n", state->name);
			if(QL_DATA_CALL_TYPE_IPV4 == state->ip_family) {
				printf("IP address:          %s\n", inet_ntoa(state->v4.ip));
				printf("Gateway address:     %s\n", inet_ntoa(state->v4.gateway));
				printf("Primary DNS address: %s\n", inet_ntoa(state->v4.pri_dns));
				printf("Second DNS address:  %s\n", inet_ntoa(state->v4.sec_dns));

				if(1 != g_call.profile_idx) {
					snprintf(command, sizeof(command), "route add default gw %s",
						inet_ntoa(state->v4.gateway));
					system(command);
					snprintf(command, sizeof(command), "echo 'nameserver %s' >> /etc/resolv.conf",
						inet_ntoa(state->v4.pri_dns));
					system(command);
					snprintf(command, sizeof(command), "echo 'nameserver %s' >> /etc/resolv.conf",
						inet_ntoa(state->v4.sec_dns));
					system(command);
				}
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

				if(1 != g_call.profile_idx) {
					inet_ntop(AF_INET6, (void *)&state->v6.gateway, ipv6_buffer, INET6_ADDRSTRLEN);
					snprintf(command, sizeof(command), "ip -6 route del default via %s dev %s",
						ipv6_buffer, state->name);
					system(command);
					
					inet_ntop(AF_INET6, (void *)&state->v6.pri_dns, ipv6_buffer, INET6_ADDRSTRLEN);
					snprintf(command, sizeof(command), "echo 'nameserver %s' >> /etc/resolv.conf",
						ipv6_buffer);
					system(command);
					
					inet_ntop(AF_INET6, (void *)&state->v6.sec_dns, ipv6_buffer, INET6_ADDRSTRLEN);
					snprintf(command, sizeof(command), "echo 'nameserver %s' >> /etc/resolv.conf",
						ipv6_buffer);
					system(command);
				}
			}
			printf("\n");
		} else {
			printf("is disconnected, and reason code %x\n", state->err);
		}
	}
}

static void data_call()
{	
	ql_data_call_error_e err = QL_DATA_CALL_ERROR_NONE;
	
	ql_data_call_init(data_call_state_callback);
	if(ql_data_call_start(&g_call, &err)) {
		printf("start data call failure: %x\n", err);
		ql_data_call_destroy();
		return;
	}
}

static void ql_data_init(char *ip, int dest_port)
{
    if(ip == NULL )
    {
        printf("#####  return  #####\n");
	return;
    }

    struct sockaddr_in dest;
    char ip_addr[32] = {0};
    int port = dest_port;
    pthread_t data_tid = -1;

    /* start data call */
    data_call();
    sleep(3);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
    {
        printf("Socket error\n");
	return;
    }
    
    strcpy(ip_addr, ip);
 
    if(inet_aton(ip_addr, (struct in_addr*)&dest.sin_addr.s_addr) == 0)
    {
        printf("ip %s is invalid\n", ip_addr);
	return;
    }

    dest.sin_family = AF_INET;
    dest.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr*)&dest, sizeof(dest)) != 0)
    {
        printf("Connect error\n");
	return;
    }
    printf("######## Connect server %s %d OK #########\n", ip_addr, port);
    
    ret = pthread_create(&data_tid, NULL, (void*)data_rev_process, (void*)sockfd);
    printf("create thread! ret: %d\n", ret);
}

/************************** ql sms  ********************************/
#define MAX_CHARACTER_SIZE    8   
unsigned char* UnicodeToUTF8( int unicode, unsigned char *p)  
{  
    unsigned char *e = NULL;  
    if((e = p))  
    {  
        if(unicode < 0x80)  
        {  
            *e++ = unicode;  
        }  
        else if(unicode < 0x800)  
        {
            *e++ = ((unicode >> 6) & 0x1f)|0xc0;  
            *e++ = (unicode & 0x3f)|0x80;   
        }  
        else if(unicode < 0x10000)  
        {
            *e++ = ((unicode >> 12) & 0x0f)|0xe0;   
            *e++ = ((unicode >> 6) & 0x3f)|0x80;  
            *e++ = (unicode & 0x3f)|0x80;   
        }  
        else if(unicode < 0x200000)  
        {
            *e++ = ((unicode >> 18) & 0x07)|0xf0;   
            *e++ = ((unicode >> 12) & 0x3f)|0x80;  
            *e++ = ((unicode >> 6) & 0x3f)|0x80;  
            *e++ = (unicode & 0x3f)|0x80;   
        }  
        else if(unicode < 0x4000000)  
        {
            *e++ = ((unicode >> 24) & 0x03)|0xf8 ;   
            *e++ = ((unicode >> 18) & 0x3f)|0x80;  
            *e++ = ((unicode >> 12) & 0x3f)|0x80;  
            *e++ = ((unicode >> 6) & 0x3f)|0x80;  
            *e++ = (unicode & 0x3f)|0x80;   
        }  
        else 
        {
            *e++ = ((unicode >> 30) & 0x01)|0xfc;
            *e++ = ((unicode >> 24) & 0x3f)|0x80;
            *e++ = ((unicode >> 18) & 0x3f)|0x80;
            *e++ = ((unicode >> 12) & 0x3f)|0x80;
            *e++ = ((unicode >> 6) & 0x3f)|0x80;  
            *e++ = (unicode & 0x3f)|0x80;   
        }  
    }  
     
    return e;  
}

unsigned char* UnicodeStrToUTF8Str (unsigned short *unicode_str,  
                                    unsigned char   *utf8_str, 
                                    int             utf8_str_size)  
{  
    int unicode = 0;  
    unsigned char *e = NULL, *s = NULL;  
    unsigned char utf8_ch[MAX_CHARACTER_SIZE];   
    s = utf8_str;  
    if ((unicode_str) && (s))  
    {  
        while ((unicode = (int) (*unicode_str++)))  
        {  
            #if 1//LE
                unicode = ((unicode&0xFF)<<8) | ((unicode&0xFF00) >> 8);  //error
            #else//BE
                unicode = unicode;  
            #endif
            memset (utf8_ch, 0, sizeof (utf8_ch));  
              
            if ((e = UnicodeToUTF8 (unicode, utf8_ch)) > utf8_ch)  
            {  
                *e = '\0';
                 
                if ((s - utf8_str + strlen ((const char *) utf8_ch)) >= utf8_str_size)  
                {  
                    return s;  
                }  
                else 
                {  
                    memcpy (s, utf8_ch, strlen ((const char *) utf8_ch));  
                    s += strlen ((const char *) utf8_ch);  
                    *s = '\0';  
                }  
            }  
            else 
            {
                return s;  
            }  
        }  
    }  
      
    return s;  
}  
 
static void ql_sms_cb_func( QL_SMS_MsgRef   msgRef,  
                            void*               contextPtr)
{
    int i;

    if(g_ql_lpm_wakelock_flag == 0)
    {
        if (Ql_SLP_WakeLock_Lock(g_ql_lpm_wakelock_fd) != 0)
        {
            Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
            printf("Lock wakelock failed!\n");
            return;
        }
        g_ql_lpm_wakelock_flag = 1;
        ret = QL_NW_ForbidInd(0);
        printf("QL_NW_ForbidInd ret = %d\n", ret);
    }
    /* Control the wakeup_out pin output high level to notify mcu that I`m awakened. */
    Ql_GPIO_SetLevel(g_ql_lpm_wakeupout_pin, PINLEVEL_HIGH);
    printf("wakeup_out pin output high level to notify mcu that I`m awakened.\n");

    if(msgRef->e_storage != E_QL_SMS_STORAGE_TYPE_NONE)
    {
        char *msg_format[]  = {"CDMA",  "GW"};
        char *storage_type[]= {"UIM",   "NV"};
        printf("###You've got one new %s message, stored to %s index=%d\n", 
                    msg_format[msgRef->e_mode & 1],
                    storage_type[msgRef->e_storage & 1],
                    msgRef->storage_index);  
    }
    else if(msgRef->format == E_QL_SMS_FORMAT_UCS2)
    {
        unsigned char* smsbuf = NULL;

        smsbuf = (char*)malloc(sizeof(char)*QL_SMS_MAX_MT_MSG_LENGTH);
        if(smsbuf == NULL)
        {
            printf("Out of memory");
            return;
        }
        memset(smsbuf, 0, QL_SMS_MAX_MT_MSG_LENGTH);
        UnicodeStrToUTF8Str((unsigned short*)(&msgRef->sms_data[0]),  
                              smsbuf, 
                              QL_SMS_MAX_MT_MSG_LENGTH) ;
	if (msgRef->user_data_head_valid)
	{
//		printf("\n###You've got one new UCS2 msg from %s at %s, total_segments:%d, seg_number:%d, reference_number:%02x, len=%d, content=%s\n", 
		printf("\n###You've got one new UCS2 msg from %s at %s, total_segments:%d, seg_number:%d, len=%d, content=%s\n", 
					msgRef->src_addr,
					msgRef->timestamp,
					msgRef->user_data_head.total_segments,
					msgRef->user_data_head.seg_number,
//					msgRef->user_data_head.reference_number,
					msgRef->sms_data_len,
					smsbuf); 
	}
	else
	{
		printf("\n###You've got one new UCS2 msg from %s at %s, len=%d, content=%s\n", 
		                        msgRef->src_addr,
		                        msgRef->timestamp,
		                        msgRef->sms_data_len,
		                        smsbuf); 
    	}
        printf("Received UCS raw data:");
        for(i=0; i<msgRef->sms_data_len; i++)
        {
            printf("%.2X ", msgRef->sms_data[i]);
        }
        
        printf("\nAfter convert to UTF8, len=%d, data:", strlen(smsbuf));
        for(i=0; i<strlen(smsbuf); i++)
        {
            printf("%.2X ", smsbuf[i]);
        }
        printf("\n");
        free(smsbuf);
    }
    else if(msgRef->format == E_QL_SMS_FORMAT_BINARY_DATA)
    {
    	if (msgRef->user_data_head_valid)
    	{
        //	printf("###You've got one new BINARY msg from %s at %s , total_segments:%d, seg_number:%d, reference_number:%02x, len=%d, content=", 
        	printf("###You've got one new BINARY msg from %s at %s , total_segments:%d, seg_number:%d, len=%d, content=", 
							msgRef->src_addr,
							msgRef->timestamp,
							msgRef->user_data_head.total_segments,
							msgRef->user_data_head.seg_number,
	//						msgRef->user_data_head.reference_number,
							msgRef->sms_data_len); 
    	}
	else
	{
        	printf("###You've got one new BINARY msg from %s at %s , len=%d, content=", 
							msgRef->src_addr,
							msgRef->timestamp,
							msgRef->sms_data_len); 
	}
        for(i=0; i<msgRef->sms_data_len; i++)
        {
            printf("%.2X ", msgRef->sms_data[i]);
        }
        printf("\n");
    }
    else //default is GSM-7
    {
    	if (msgRef->user_data_head_valid)
    	{
        //	printf("###You've got one new GSM-7 msg from %s at %s, total_segments:%d, seg_number:%d, reference_number:%02x, content=%s\n", 
        	printf("###You've got one new GSM-7 msg from %s at %s, total_segments:%d, seg_number:%d, content=%s\n", 
		                    msgRef->src_addr,
		                    msgRef->timestamp,
				    msgRef->user_data_head.total_segments,
		                    msgRef->user_data_head.seg_number,
	//			    msgRef->user_data_head.reference_number,
		                    msgRef->sms_data);          
    	}
	else
	{
		printf("###You've got one new GSM-7 msg from %s at %s, content=%s\n", 
		                    msgRef->src_addr,
		                    msgRef->timestamp,
		                    msgRef->sms_data);   
	}
        for(i=0; i<msgRef->sms_data_len; i++)
        {
            printf("%.2X ", msgRef->sms_data[i]);
        }
        printf("\n\n");
    }
}

static void ql_sms_init()
{
            ret = QL_SMS_Client_Init(&h_sms);
            printf("QL_SMS_Client_Init ret=%d with h_sms=0x%x\n", ret, h_sms);

            ret = QL_SMS_AddRxMsgHandler(ql_sms_cb_func, (void*)h_sms);
            printf("QL_SMS_AddRxMsgHandler ret=%d \n", ret);
}

/*************************** ql voice ***************************************/
static void ql_voice_call_cb_func(int                     call_id,
                                  char*                   phone_num,
                                  E_QL_VOICE_CALL_STATE_T state,
                                  void                    *contextPtr)
{
	switch(state)
	{
	case E_QL_MCM_VOICE_CALL_STATE_INCOMING:
		if(g_ql_lpm_wakelock_flag == 0)
		{
			if (Ql_SLP_WakeLock_Lock(g_ql_lpm_wakelock_fd) != 0)
			{
				Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
				printf("Lock wakelock failed!\n");
				return;
			}
	    		g_ql_lpm_wakelock_flag = 1;
                        ret = QL_NW_ForbidInd(0);
                        printf("QL_NW_ForbidInd ret = %d\n", ret);
                }
		/* Control the wakeup_out pin output high level to notify mcu that I`m awakened. */
		Ql_GPIO_SetLevel(g_ql_lpm_wakeupout_pin, PINLEVEL_HIGH);
		printf("wakeup_out pin output high level to notify mcu that I`m awakened.\n");
		break;
	default:
		break;
	}
 
    char *call_state[] = {"INCOMING", "DIALING", "ALERTING", "ACTIVE", "HOLDING", "END", "WAITING"};

    printf("######### Call id=%d, PhoneNum:%s, event=%s!  ######\n", call_id, phone_num, call_state[state]);
}

static void ql_voice_init()
{
	ret = QL_Voice_Call_Client_Init(&h_voice);
        printf("QL_Voice_Call_Client_Init ret = %d, with h_voice=%d\n", ret, h_voice);

	ret = QL_Voice_Call_AddStateHandler(h_voice, ql_voice_call_cb_func, NULL);
	printf("QL_Voice_Call_AddStateHandler ret = %d\n", ret);

}

/************************************* ql lpm ******************************************************/
static void ql_lpm_handler(ql_lpm_edge_t edge_state)
{
	switch(edge_state)
	{
	//wakeup
	case E_QL_LPM_RISING:
		if(g_ql_lpm_wakelock_flag == 0)
		{
			if (Ql_SLP_WakeLock_Lock(g_ql_lpm_wakelock_fd) != 0)
			{
				Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
				printf("Lock wakelock failed!\n");
				return;
			}
	    		g_ql_lpm_wakelock_flag = 1;
                        ret = QL_NW_ForbidInd(0);
                        printf("QL_NW_ForbidInd ret = %d\n", ret);
                }
		/* Control the wakeup_out pin output high level to notify mcu that I`m awakened. */
		Ql_GPIO_SetLevel(g_ql_lpm_wakeupout_pin, PINLEVEL_HIGH);
		printf("wakeup_out pin output high level to notify mcu that I`m awakened.\n");
		break;
	//suspend
	case E_QL_LPM_FALLING:
		printf("do something before enter sleep mode\n");
		printf("module will enter sleep mode\n");
		
		if(g_ql_lpm_wakelock_flag == 1)
		{
	    		g_ql_lpm_wakelock_flag = 0;
                        ret = QL_NW_ForbidInd(1);
                        printf("QL_NW_ForbidInd ret = %d\n", ret);
                        if (Ql_SLP_WakeLock_Unlock(g_ql_lpm_wakelock_fd) != 0) 
			{
				Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
	   			printf("Unlock wakelock failed!\n");
		   		return;
		   	}
		}
		break;
	default:
		break;
	}
}

static void ql_lpm_init()
{	
	QL_Lpm_Cfg_T *ql_lpm_cfg = NULL;

/* Donot recommend to modify default pin and trigger methods. */
#if 0
	ql_lpm_cfg = (QL_Lpm_Cfg_T *)malloc(sizeof(QL_Lpm_Cfg_T));

	ql_lpm_cfg->wakeupin.wakeupin_pin = 61;
	ql_lpm_cfg->wakeupin.wakeupin_edge = E_QL_LPM_RISING;
	ql_lpm_cfg->wakeupout.wakeupout_pin = g_ql_lpm_wakeupout_pin;
	ql_lpm_cfg->wakeupout.wakeupout_edge = E_QL_LPM_RISING;
#endif


	ret = QL_Lpm_Init(ql_lpm_handler, ql_lpm_cfg);
	printf("QL Lpm Init, ret: %d\n", ret);

	Ql_GPIO_Init(g_ql_lpm_wakeupout_pin, PINDIRECTION_OUT, PINLEVEL_HIGH, PINPULLSEL_DISABLE);
	
	g_ql_lpm_wakelock_fd = Ql_SLP_WakeLock_Create("ql_lpm", sizeof("ql_lpm"));
	if (Ql_SLP_WakeLock_Lock(g_ql_lpm_wakelock_fd) != 0)
	{
		Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
		printf("Lock wakelock failed!\n");
		return;
	}
	g_ql_lpm_wakelock_flag = 1;

	Ql_Autosleep_Enable(1);

#if 0
	Ql_GPIO_Uninit(g_ql_lpm_wakeupout_pin);
	
	QL_Lpm_Deinit();

	Ql_Autosleep_Enable(0);
	
	if(Ql_SLP_WakeLock_Unlock(g_ql_lpm_wakelock_fd) != 0)
	{
		Ql_SLP_WakeLock_Destroy(g_ql_lpm_wakelock_fd);
		printf("Lock wakelock failed!\n");
		return;
	}
	g_ql_lpm_wakelock_flag = 0;
#endif
}

/*************************** app exception sinal deal ********************/
static void ql_exception_handler(int signal, siginfo_t *info, void *ptr)
{
	switch(signal)
	{
	case SIGTERM:
	case SIGKILL:
	case SIGINT:
	case SIGSEGV:
		ret = QL_SMS_Client_Deinit(h_sms);
		printf("QL_SMS_Client_Deinit ret=%d \n", ret);

		ret = QL_Voice_Call_Client_Deinit(h_voice);
		printf("QL_Voice_Call_Client_Deinit ret = %d\n", ret);
		
		ret = QL_Lpm_Deinit();
		printf("QL_Lpm_Deinit ret = %d\n", ret);
		ret = Ql_GPIO_Uninit(g_ql_lpm_wakeupout_pin);
		printf("QL_GPIO_Uninit ret = %d\n", ret);
		ret = Ql_Autosleep_Enable(0);
		printf("QL_Autosleep ret = %d\n", ret);
		ret = Ql_SLP_WakeLock_Unlock(g_ql_lpm_wakelock_fd);
		printf("Ql_SLP_WakeLock_Unlock ret = %d\n", ret);

		exit(1);
		break;
	default:
		printf("unknow signal\n");
		break;
	}
}

static void ql_exception_init()
{
	struct sigaction sa = {0};
	sa.sa_sigaction = ql_exception_handler;    
	sa.sa_flags = SA_SIGINFO;
	sigaction (SIGTERM, &sa, NULL);    
	sigaction (SIGSEGV, &sa, NULL);
	sigaction (SIGKILL, &sa, NULL);
	sigaction (SIGINT, &sa, NULL);
}

/*************************** Main ***********************************/
int main(int argc, char **argv)
{
	if(argc != 3 )
	{
		printf("#####usage: ./example_lpm_all server_ip port #####\n");
		printf("#####  return  #####\n");
		return -1;
	}

	ql_exception_init();

	ql_sms_init();

	ql_voice_init();

	ql_data_init(argv[1], atoi(argv[2]));

	ql_lpm_init();

	while(1){
		sleep(2);
	}
	return 0;
}
