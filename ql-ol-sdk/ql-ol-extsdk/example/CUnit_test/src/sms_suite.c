#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include "sms_suite.h"
#include "testconf.h"


static sms_client_handle_type h_sms;

//#define TEST_SDK_DEST_PHONE_NUMBER  "18054099355"

static int sms_send_flag = 0;
#define SMS_REPLY_BUFF_LEN  (128)
static char sms_reply_buff[SMS_REPLY_BUFF_LEN] = {0};

extern char g_dest_phone_number[32];
extern int g_reply_sms_times;
extern int g_verbose;
extern int g_interval;


int sms_suite_init()
{
	int ret;
	ret = QL_SMS_Client_Init(&h_sms);
	if(ret)
	{
		printErrMsg("QL_SMS_Client_Init failed.\n");
		return -1;
	}
	return 0;
}


int sms_suite_clean()
{
	int ret;
	
	ret = QL_SMS_Client_Deinit(h_sms);
	if(ret)
	{
		printDebugFormatMsg("%s: Client Deinit failed.\n", __FUNCTION__);
		return -1;
	}
	return 0;
}

void sms_suite_SetUp()
{
	return;
}

void sms_suite_TearDown()
{
	return;
}


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
 
int UTF8ToUnicode (unsigned char *ch, int *unicode)  
{  
    unsigned char *p = NULL;  
    int e = 0, n = 0;  
    if((p = ch) && unicode)  
    {  
        if(*p >= 0xfc)  
        {
            e = (p[0] & 0x01) << 30;  
            e |= (p[1] & 0x3f) << 24;  
            e |= (p[2] & 0x3f) << 18;  
            e |= (p[3] & 0x3f) << 12;  
            e |= (p[4] & 0x3f) << 6;  
            e |= (p[5] & 0x3f);  
            n = 6;  
        }  
        else if(*p >= 0xf8)   
        {
            e = (p[0] & 0x03) << 24;  
            e |= (p[1] & 0x3f) << 18;  
            e |= (p[2] & 0x3f) << 12;  
            e |= (p[3] & 0x3f) << 6;  
            e |= (p[4] & 0x3f);  
            n = 5;  
        }  
        else if(*p >= 0xf0)  
        {
            e = (p[0] & 0x07) << 18;  
            e |= (p[1] & 0x3f) << 12;  
            e |= (p[2] & 0x3f) << 6;  
            e |= (p[3] & 0x3f);  
            n = 4;  
        }  
        else if(*p >= 0xe0)  
        {
            e = (p[0] & 0x0f) << 12;  
            e |= (p[1] & 0x3f) << 6;  
            e |= (p[2] & 0x3f);  
            n = 3;  
        }  
        else if(*p >= 0xc0)   
        {
            e = (p[0] & 0x1f) << 6;  
            e |= (p[1] & 0x3f);  
            n = 2;  
        }  
        else   
        {  
            e = p[0];  
            n = 1;  
        }  
        *unicode = e;  
    }  
     
    return n;  
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
 
int UTF8StrToUnicodeStr(unsigned char   *utf8_str,  
                        uint16_t        *unicode_str, 
                        int             unicode_str_size)  
{  
    int unicode = 0;  
    int n = 0;  
    int count = 0;  
    unsigned char *s = NULL;  
    uint16_t *e = NULL;  
      
    s = utf8_str;  
    e = unicode_str;  
      
    if ((utf8_str) && (unicode_str))  
    {  
        while (*s)  
        {  
            if ((n = UTF8ToUnicode (s, &unicode)) > 0)  
            {  
                if ((count + 1) >= unicode_str_size)  
                {  
                    return count;  
                }  
                else 
                {  
                #if 0//LE
                    *e = (unsigned short) unicode;  
                #else//BE
                    *e = ((unicode&0xFF)<<8) | ((unicode&0xFF00) >> 8);  
                #endif
                    e++;  
                    *e = 0;                     
                    s += n;  
                    count++;
                }  
            }  
            else 
            {
                return count;  
            }  
        }  
    }  
      
    return count;  
} 


static void ql_sms_cb_func(QL_SMS_MsgRef msgRef, void *contextPtr)
{
	char *p = NULL;
	//printDebugFormatMsg("%s: recv msg from %s, content: %s\n", __FUNCTION__, msgRef->src_addr, msgRef->sms_data);
	printFuncPrefix;
	
	if(memcmp(msgRef->src_addr, "+86", 3) == 0)
	{
		p = msgRef->src_addr + 3;
	}
	else
	{
		p = msgRef->src_addr;
	}
	if(strcmp(p, g_dest_phone_number) == 0)
	{
		sms_send_flag = 1;
		memset(sms_reply_buff, 0, SMS_REPLY_BUFF_LEN);
		//printFormatMsg("\trecv msg from %s, content: %s\n", msgRef->src_addr, msgRef->sms_data);
		if(msgRef->format == E_QL_SMS_FORMAT_UCS2)
		{
	        UnicodeStrToUTF8Str((unsigned short*)(msgRef->sms_data),  
	                              (unsigned char*)sms_reply_buff, 
	                              SMS_REPLY_BUFF_LEN) ;
		}
		else
		{
			strcpy(sms_reply_buff, msgRef->sms_data);
		}
	}
}

/**
* 1. set sms message recv callback function
* 2. set route list, specified sms restore type ..
* 2. client: send sms message ( eg. magic_number 0xdeaddead)
* 3. server: recv sms message, and reply it with magic_number + 1
* 4. client: recv reply message, check it.
*/

/********************************TEST CASE START******************************/

//QL_SMS_AddRxMsgHandler
static void TEST_QL_SMS_AddRxMsgHandler(void)
{
	int ret;

	printFuncPrefix;
	ret = QL_SMS_AddRxMsgHandler(ql_sms_cb_func, (void*)h_sms);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_SMS_AddRxMsgHandler failed. ret=%d\n", ret);
	}
	return;
}



struct smsdata {
	char buff[128];
	char reply[128];
};

//buff:hello  reply:world
static struct smsdata send_sms_data[] = {
							{"please reply the following msg: qwert", "qwert"},
							{"please reply the following msg: asdfg", "asdfgh"},
							{"please reply the following msg: zxcvb", "zxcvb"},
							{"please reply the following msg: qazws", "qazws"},
							{"please reply the following msg: 12345", "12345"},
						};

//QL_SMS_Send_Sms
static void TEST_QL_SMS_Send_Sms(void)
{
	int ret, interval, len = 0, i;
	int reply_yet;
	E_QL_SMS_FORMAT_T format;
	ql_sms_info_t *pt_sms_info = NULL;

	printFuncPrefix;
	pt_sms_info = (ql_sms_info_t*)malloc(sizeof(ql_sms_info_t));
    if(pt_sms_info == NULL)
    {
        CU_FAIL("TEST_QL_SMS_Send_Sms malloc error.\n");
		return;
    }

	for(i = 0; i < g_reply_sms_times; i++)
	{
		format = i & 0x03;

		memset(pt_sms_info, 0, sizeof(ql_sms_info_t));

		sms_send_flag = 0;

		memset(sms_reply_buff, 0, sizeof(sms_reply_buff));
		pt_sms_info->format = format;
			
		strncpy(pt_sms_info->src_addr, g_dest_phone_number, sizeof(pt_sms_info->src_addr));

		len = strlen(send_sms_data[i].buff);
		
		if(format == E_QL_SMS_FORMAT_GSM_7BIT)
		{
			strcpy(pt_sms_info->sms_data, send_sms_data[i].buff);
			pt_sms_info->sms_data_len = len;
		}
		else if(format == E_QL_SMS_FORMAT_BINARY_DATA)
		{
			memcpy(pt_sms_info->sms_data, send_sms_data[i].buff, len + 1);
			pt_sms_info->sms_data_len = len + 1;
		}
		else
		{
			
			len = UTF8StrToUnicodeStr((unsigned char*)send_sms_data[i].buff, 
                                          (uint16_t*)pt_sms_info->sms_data, 
                                          len + 1);// Got BE data
            pt_sms_info->sms_data_len = (len + 1) * 2;//in bytes
		}
		
		ret = QL_SMS_Send_Sms(h_sms, pt_sms_info);
		CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
		if(ret != MCM_SUCCESS_V01)
		{
			printFormatMsg("QL_SMS_Send_Sms failed. ret=%d\n", ret);
			return;
		}

		interval = 0;
		reply_yet = 0;
		printFormatMsg("waiting reply message:               %2dS", interval);
		do
		{
			//if(interval % 10 == 0)
			//{
			//	printDebugFormatMsg("waiting reply sms[%d].\n", interval);
			//}
			printf("\b\b\b%02dS", interval);
			fflush(stdout);
			if(sms_send_flag == 1)
			{
				if(strcmp(sms_reply_buff, send_sms_data[i].reply) != 0)
				{
					CU_FAIL("recv message content error.");
				}
				reply_yet = 1;
				break;
			}
			interval++;
			sleep(1);
		}
		while (interval < g_interval);
		printFormatMsg("\n");
		if(reply_yet != 1)
		{
			CU_FAIL("\trecv reply message failed.\n");
		}
	}
	return;
}
//QL_SMS_DeleteFromStorage

//QL_SMS_SetRouteList

//QL_SMS_Send_SmsPdu

//QL_SMS_GetSmsCenterAddress
static void TEST_QL_SMS_GetSmsCenterAddress(void)
{
	int ret, len;
	ql_sms_service_center_cfg_t sca_cfg;

	printFuncPrefix;
	memset(&sca_cfg, 0, sizeof(ql_sms_service_center_cfg_t));
	ret = QL_SMS_GetSmsCenterAddress(h_sms, &sca_cfg);
	CU_ASSERT_EQUAL(ret, MCM_SUCCESS_V01);
	if(ret != MCM_SUCCESS_V01)
	{
		printFormatMsg("QL_SMS_GetSmsCenterAddress failed.ret=%d\n", ret);
		return;
	}

	//CU_ASSERT(strlen(sca_cfg.service_center_addr) > 0);
	len = strlen(sca_cfg.service_center_addr);
	if(len <= 0)
	{
		CU_FAIL("service_center_addr len error.\n");
	}

	printFormatMsg("service_center_addr: %s, len: %d\n", 
					sca_cfg.service_center_addr, len);
	
	if(sca_cfg.service_center_addr_type_valid)
	{
		//CU_ASSERT(strlen(sca_cfg.service_center_addr_type) > 0);
		if(strlen(sca_cfg.service_center_addr_type) <= 0)
		{
			CU_FAIL("service_center_addr_type error.\n");
		}
		
		printFormatMsg("service_center_addr_type: %s\n", sca_cfg.service_center_addr_type);
	}
	return;
}
//QL_SMS_SetSmsCenterAddress



/********************************TEST CASE END********************************/


/*
	Test case array - must be NULL terminated
*/
static CU_TestInfo sms_suite_case[] = {
	{"test QL_SMS_AddRxMsgHandler", TEST_QL_SMS_AddRxMsgHandler},
	{"test QL_SMS_Send_Sms", TEST_QL_SMS_Send_Sms},
	{"test QL_SMS_GetSmsCenterAddress", TEST_QL_SMS_GetSmsCenterAddress},
	CU_TEST_INFO_NULL,
};


/**
structure:
suite name, init func, cleanup func, SetUp func, TearDown func, testfunc
*/
CU_SuiteInfo sms_suites[] = {
	{"sms suite", sms_suite_init, sms_suite_clean, sms_suite_SetUp, sms_suite_TearDown, sms_suite_case},
	CU_SUITE_INFO_NULL,
};

