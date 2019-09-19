/*
 *@file: just a demo, for reference only. the demo in consist of ext_interrupt(wakeup_in pin) to wakeup 4G module, 
 *	 it is necessary for user to call "Ql_SLP_WakeLock_Lock()" in the beginning of callback for keeping 4G module 
 * 	 awake, and then deal with other things.
 *
*@date     2018-08-30
 *@author   gale
 *@brief    the function is suitable for this product: 
 *		 __________                 ________
 *		| Quectel  |<--wakeupin----|Customer| 
 *		| 4G module|               |  MCU   |
 *		|__________|---wakeupout-->|________|
 *@Default:
 *          EC20xx: wakeupin pin62(input), rising to wakeup 4G module; wakeupout pin5  (output), rising to wakeup mcu.
 *          AG35xx: wakeupin pin61(input), rising to wakeup 4G module; wakeupout pin147(output), rising to wakeup mcu.
*/

#include <ql_oe.h>
#include <ql_lpm.h>

int g_ql_lpm_wakelock_flag = 0;
int g_ql_lpm_wakelock_fd = -1;
int g_ql_lpm_wakeupout_pin = 5;	/* wakeupout(Ec20xx is pin5), in general, user need to control when module is waken by ext_interrupt, sms, voice, or data */
int ret = 0;

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

static void ql_lpm_exception_handler(int signal, siginfo_t *info, void *ptr)
{
	switch(signal)
	{
	case SIGTERM:
	case SIGKILL:
	case SIGINT:
	case SIGSEGV:
		QL_Lpm_Deinit();
		Ql_GPIO_Uninit(g_ql_lpm_wakeupout_pin);
		Ql_Autosleep_Enable(0);
		Ql_SLP_WakeLock_Unlock(g_ql_lpm_wakelock_fd);
		exit(1);
		break;
	default:
		printf("unknow signal\n");
		break;
	}
}

/*************************** Main ***********************************/
int main(int argc, char **argv)
{
	struct sigaction sa = {0};
	sa.sa_sigaction = ql_lpm_exception_handler;    
	sa.sa_flags = SA_SIGINFO;
	sigaction (SIGTERM, &sa, NULL);    
	sigaction (SIGSEGV, &sa, NULL);
	sigaction (SIGKILL, &sa, NULL);
	sigaction (SIGINT, &sa, NULL);
	
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

	while(1){
		sleep(2);
	}

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
	return 0;
}
