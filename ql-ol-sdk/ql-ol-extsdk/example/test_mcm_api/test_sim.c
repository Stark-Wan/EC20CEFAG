#include <ql_oe.h>
#include "test_base.h"

static int    h_sim   = 0;
extern func_api_test_t t_sim_test;
st_api_test_case at_sim_testlist[] = 
{
    {0,    "QL_MCM_SIM_Client_Init"},
    {1,    "QL_MCM_SIM_Client_Deinit"},
    {2,    "QL_MCM_SIM_GetIMSI"},
    {3,    "QL_MCM_SIM_GetICCID"},
    {4,    "QL_MCM_SIM_GetPhoneNumber"},
    {5,    "QL_MCM_SIM_GetOperatorPlmnList"},
    {6,    "QL_MCM_SIM_VerifyPIN"},
    {7,    "QL_MCM_SIM_ChangePin"},
    {8,    "QL_MCM_SIM_UnblockPIN"},
    {9,    "QL_MCM_SIM_EnablePIN"},
    {10,   "QL_MCM_SIM_DisablePIN"},
    {11,   "QL_MCM_SIM_GetCardStatus"},
    {12,   "QL_MCM_SIM_Depersonalization"},
    {13,   "QL_MCM_SIM_Personalization"},
    {14,   "QL_MCM_SIM_WriteFile"},
    {15,   "QL_MCM_SIM_ReadFile"},
    {16,   "QL_MCM_SIM_GetFileSize"},
    {17,   "QL_MCM_SIM_ReadPhoneBookRecord"},
    {18,   "QL_MCM_SIM_WritePhoneBookRecord\n"},
    
    
    {-1,   "Return to main menu"}
};

static char* errorcode[] = 
{
    "MCM_SUCCESS",                              //  0, /**<  Success. */
    "MCM_SUCCESS_CONDITIONAL_SUCCESS",          //  1, /**<  Conditional success. */
    "MCM_ERROR_MCM_SERVICES_NOT_AVAILABLE",     //  2, /**<  "MCM services not available. */
    "MCM_ERROR_GENERIC",                        //  3, /**<  Generic error. */
    "MCM_ERROR_BADPARM",                        //  4, /**<  Bad parameter. */
    "MCM_ERROR_MEMORY",                         //  5, /**<  Memory error. */
    "MCM_ERROR_INVALID_STATE",                  //  6, /**<  Invalid state. */
    "MCM_ERROR_MALFORMED_MSG",                  //  7, /**<  Malformed message. */
    "MCM_ERROR_NO_MEMORY",                      //  8, /**<  No memory. */
    "MCM_ERROR_INTERNAL",                       //  9, /**<  Internal error. */
    "MCM_ERROR_ABORTED",                        //  10, /**<  Action was aborted. */
    "MCM_ERROR_CLIENT_IDS_EXHAUSTED",           //  11, /**<  Client IDs have been exhausted. */
    "MCM_ERROR_UNABORTABLE_TRANSACTION",        //  12, /**<  Unabortable transaction. */
    "MCM_ERROR_INVALID_CLIENT_ID",              //  13, /**<  Invalid client ID. */
    "MCM_ERROR_NO_THRESHOLDS",                  //  14, /**<  No thresholds. */
    "MCM_ERROR_INVALID_HANDLE",                 //  15, /**<  Invalid handle. */
    "MCM_ERROR_INVALID_PROFILE",                //  16, /**<  Invalid profile. */
    "MCM_ERROR_INVALID_PINID",                  //  17, /**<  Invalid PIN ID. */
    "MCM_ERROR_INCORRECT_PIN",                  //  18, /**<  Incorrect PIN. */
    "MCM_ERROR_NO_NETWORK_FOUND",               //  19, /**<  No network found. */
    "MCM_ERROR_CALL_FAILED",                    //  20, /**<  Call failed. */
    "MCM_ERROR_OUT_OF_CALL",                    //  21, /**<  Out of call. */
    "MCM_ERROR_NOT_PROVISIONED",                //  22, /**<  Not provisioned. */
    "MCM_ERROR_MISSING_ARG",                    //  23, /**<  Missing argument. */
    "MCM_ERROR_ARG_TOO_LONG",                   //  24, /**<  Argument is too long. */
    "MCM_ERROR_INVALID_TX_ID",                  //  25, /**<  Invalid Tx ID. */
    "MCM_ERROR_DEVICE_IN_USE",                  //  26, /**<  Device is in use. */
    "MCM_ERROR_OP_NETWORK_UNSUPPORTED",         //  27, /**<  OP network is not supported. */
    "MCM_ERROR_OP_DEVICE_UNSUPPORTED",          //  28, /**<  OP device is not supported. */
    "MCM_ERROR_NO_EFFECT",                      //  29, /**<  No effect. */
    "MCM_ERROR_NO_FREE_PROFILE",                //  30, /**<  No free profile. */
    "MCM_ERROR_INVALID_PDP_TYPE",               //  31, /**<  Invalid PDP type. */
    "MCM_ERROR_INVALID_TECH_PREF",              //  32, /**<  Invalid technical preference. */
    "MCM_ERROR_INVALID_PROFILE_TYPE",           //  33, /**<  Invalid profile type. */
    "MCM_ERROR_INVALID_SERVICE_TYPE",           //  34, /**<  Invalid service type. */
    "MCM_ERROR_INVALID_REGISTER_ACTION",        //  35, /**<  Invalid register action. */
    "MCM_ERROR_INVALID_PS_ATTACH_ACTION",       //  36, /**<  Invalid PS attach action. */
    "MCM_ERROR_AUTHENTICATION_FAILED",          //  37, /**<  Authentication failed. */
    "MCM_ERROR_PIN_BLOCKED",                    //  38, /**<  PIN is blocked. */
    "MCM_ERROR_PIN_PERM_BLOCKED",               //  39, /**<  PIN is permanently blocked. */
    "MCM_ERROR_SIM_NOT_INITIALIZED",            //  40, /**<  SIM is not initialized. */
    "MCM_ERROR_MAX_QOS_REQUESTS_IN_USE",        //  41, /**<  Maximum QoS requests are in use. */
    "MCM_ERROR_INCORRECT_FLOW_FILTER",          //  42, /**<  Incorrect flow filter. */
    "MCM_ERROR_NETWORK_QOS_UNAWARE",            //  43, /**<  Network QoS is unaware. */
    "MCM_ERROR_INVALID_ID",                     //  44, /**<  Invalid ID. */
    "MCM_ERROR_INVALID_QOS_ID",                 //  45, /**<  Invalid QoS ID. */
    "MCM_ERROR_REQUESTED_NUM_UNSUPPORTED",      //  46, /**<  Requested number is not supported. */
    "MCM_ERROR_INTERFACE_NOT_FOUND",            //  47, /**<  Interface was not found. */
    "MCM_ERROR_FLOW_SUSPENDED",                 //  48, /**<  Flow is suspended. */
    "MCM_ERROR_INVALID_DATA_FORMAT",            //  49, /**<  Invalid data format. */
    "MCM_ERROR_GENERAL",                        //  50, /**<  General error. */
    "MCM_ERROR_UNKNOWN",                        //  51, /**<  Unknown error. */
    "MCM_ERROR_INVALID_ARG",                    //  52, /**<  Invalid argument. */
    "MCM_ERROR_INVALID_INDEX",                  //  53, /**<  Invalid index. */
    "MCM_ERROR_NO_ENTRY",                       //  54, /**<  No entry. */
    "MCM_ERROR_DEVICE_STORAGE_FULL",            //  55, /**<  Device storage is full. */
    "MCM_ERROR_DEVICE_NOT_READY",               //  56, /**<  Device is not ready. */
    "MCM_ERROR_NETWORK_NOT_READY",              //  57, /**<  Network is not ready. */
    "MCM_ERROR_CAUSE_CODE",                     //  58, /**<  Cause code error. */
    "MCM_ERROR_MESSAGE_NOT_SENT",               //  59, /**<  Message was not sent. */
    "MCM_ERROR_MESSAGE_DELIVERY_FAILURE",       //  60, /**<  Message delivery failure. */
    "MCM_ERROR_INVALID_MESSAGE_ID",             //  61, /**<  Invalid message ID. */
    "MCM_ERROR_ENCODING",                       //  62, /**<  Encoding error. */
    "MCM_ERROR_AUTHENTICATION_LOCK",            //  63, /**<  Authentication lock error. */
    "MCM_ERROR_INVALID_TRANSITION",             //  64, /**<  Invalid transition. */
    "MCM_ERROR_NOT_A_MCAST_IFACE",              //  65, /**<  Not an MCast interface. */
    "MCM_ERROR_MAX_MCAST_REQUESTS_IN_USE",      //  66, /**<  Maximum MCast requests are in use. */
    "MCM_ERROR_INVALID_MCAST_HANDLE",           //  67, /**<  Invalid MCast handle. */
    "MCM_ERROR_INVALID_IP_FAMILY_PREF",         //  68, /**<  Invalid IP family preference. */
    "MCM_ERROR_SESSION_INACTIVE",               //  69, /**<  Session is inactive. */
    "MCM_ERROR_SESSION_INVALID",                //  70, /**<  Session is invalid. */
    "MCM_ERROR_SESSION_OWNERSHIP",              //  71, /**<  Session ownership error. */
    "MCM_ERROR_INSUFFICIENT_RESOURCES",         //  72, /**<  Insufficient resources. */
    "MCM_ERROR_DISABLED",                       //  73, /**<  Disabled. */
    "MCM_ERROR_INVALID_OPERATION",              //  74, /**<  Invalid operation. */
    "MCM_ERROR_INVALID_CMD",                    //  75, /**<  Invalid command. */
    "MCM_ERROR_TPDU_TYPE",                      //  76, /**<  Transfer Protocol data unit type error. */
    "MCM_ERROR_SMSC_ADDR",                      //  77, /**<  Short message service center address error. */
    "MCM_ERROR_INFO_UNAVAILABLE",               //  78, /**<  Information is not available. */
    "MCM_ERROR_SEGMENT_TOO_LONG",               //  79, /**<  Segment is too long. */
    "MCM_ERROR_SEGMENT_ORDER",                  //  80, /**<  Segment order error. */
    "MCM_ERROR_BUNDLING_NOT_SUPPORTED",         //  81, /**<  Bundling is not supported. */
    "MCM_ERROR_OP_PARTIAL_FAILURE",             //  82, /**<  OP partial failure. */
    "MCM_ERROR_POLICY_MISMATCH",                //  83, /**<  Policy mismatch. */
    "MCM_ERROR_SIM_FILE_NOT_FOUND",             //  84, /**<  SIM file was not found. */
    "MCM_ERROR_EXTENDED_INTERNAL",              //  85, /**<  Extended internal error. */
    "MCM_ERROR_ACCESS_DENIED",                  //  86, /**<  Access is denied. */
    "MCM_ERROR_HARDWARE_RESTRICTED",            //  87, /**<  Hardware is restricted. */
    "MCM_ERROR_ACK_NOT_SENT",                   //  88, /**<  Acknowledgement was not sent. */
    "MCM_ERROR_INJECT_TIMEOUT",                 //  89, /**<  Inject timeout error. */
    "MCM_ERROR_INCOMPATIBLE_STATE",             //  90, /**<  Incompatible state. */
    "MCM_ERROR_FDN_RESTRICT",                   //  91, /**<  Fixed dialing number restrict error. */
    "MCM_ERROR_SUPS_FAILURE_CAUSE",             //  92, /**<  SUPS failure cause. */
    "MCM_ERROR_NO_RADIO",                       //  93, /**<  No radio. */
    "MCM_ERROR_NOT_SUPPORTED",                  //  94, /**<  Not supported. */
    "MCM_ERROR_NO_SUBSCRIPTION",                //  95, /**<  No subscription. */
    "MCM_ERROR_CARD_CALL_CONTROL_FAILED",       //  96, /**<  Card call control failed. */
    "MCM_ERROR_NETWORK_ABORTED",                //  97, /**<  Network was aborted. */
    "MCM_ERROR_MSG_BLOCKED",                    //  98, /**<  Message was blocked. */
    "MCM_ERROR_INVALID_SESSION_TYPE",           //  99, /**<  Invalid session type. */
    "MCM_ERROR_INVALID_PB_TYPE",                //  100, /**<  Invalid phonebook type. */
    "MCM_ERROR_NO_SIM",                         //  101, /**<  No SIM was found. */
    "MCM_ERROR_PB_NOT_READY",                   //  102, /**<  Phonebook not ready. */
    "MCM_ERROR_PIN_RESTRICTION",                //  103, /**<  PIN restriction. */
    "MCM_ERROR_PIN2_RESTRICTION",               //  104, /**<  PIN2 restriction. */
    "MCM_ERROR_PUK_RESTRICTION",                //  105, /**<  PIN unlocking key restriction. */
    "MCM_ERROR_PUK2_RESTRICTION",               //  106, /**<  PIN unlocking key2 restriction. */
    "MCM_ERROR_PB_ACCESS_RESTRICTED",           //  107, /**<  Phonebook access is restricted. */
    "MCM_ERROR_PB_DELETE_IN_PROG",              //  108, /**<  Phonebook delete is in progress. */
    "MCM_ERROR_PB_TEXT_TOO_LONG",               //  109, /**<  Phonebook text is too long. */
    "MCM_ERROR_PB_NUMBER_TOO_LONG",             //  110, /**<  Phonebook number is too long. */
    "MCM_ERROR_PB_HIDDEN_KEY_RESTRICTION",      //  111, /**<  Phonebook hidden key restriction. */
    "MCM_ERROR_PB_NOT_AVAILABLE",               //  112, /**<  Phonebook is not available. */
    "MCM_ERROR_DEVICE_MEMORY_ERROR",            //  113, /**<  Device memory error. */
    "MCM_ERROR_SIM_PIN_BLOCKED",                //  114, /**<  SIM PIN is blocked. */
    "MCM_ERROR_SIM_PIN_NOT_INITIALIZED",        //  115, /**<  SIM PIN is not initialized. */
    "MCM_ERROR_SIM_INVALID_PIN",                //  116, /**<  SIM PIN is invalid. */
    "MCM_ERROR_SIM_INVALID_PERSO_CK",           //  117, /**<  SIM invalid personalization CK. */
    "MCM_ERROR_SIM_PERSO_BLOCKED",              //  118, /**<  SIM personalization blocked. */
    "MCM_ERROR_SIM_PERSO_INVALID_DATA",         //  119, /**<  SIM personalization contains invalid data. */
    "MCM_ERROR_SIM_ACCESS_DENIED",              //  120, /**<  SIM access is denied. */
    "MCM_ERROR_SIM_INVALID_FILE_PATH",          //  121, /**<  SIM file path is invalid. */
    "MCM_ERROR_SIM_SERVICE_NOT_SUPPORTED",      //  122, /**<  SIM service is not supported. */
    "MCM_ERROR_SIM_AUTH_FAIL",                  //  123, /**<  SIM authorization failure. */
    "MCM_ERROR_SIM_PIN_PERM_BLOCKED"            //  124, /**<  SIM PIN is permanently blocked. */
};


static uint16_t get_data_array(uint8_t *buf, uint16_t buflen)
{
    int len = 0;
    int i;

    printf("Please enter data array length(<64): ");
    while(scanf("%d", &len) != 1)
    {
        char c;
        while(((c=getchar()) != '\n') && (c != EOF))
        {
            ;
        }
    }

    if(len > buflen)
    {
        len = buflen;
    }

    for(i=0; i<len; i++)
    {
        printf("data[%d]: ", i);
        while(scanf("%x", &buf[i]) != 1)
        {
            char c;
            while(((c=getchar()) != '\n') && (c != EOF))
            {
                ;
            }
        }
    }
    return len;
} 

static E_QL_MCM_SIM_APP_TYPE_T get_app_type(void)
{
    int type = 0;

    printf("Please input app_type(1:3GPP, 2:3GPP2, 3:ISIM): ");
    scanf("%d", &type);

    if(type == 2)
    {
        return E_QL_MCM_SIM_APP_TYPE_3GPP2;
    }
    else if(type == 3)
    {
        return E_QL_MCM_SIM_APP_TYPE_ISIM;
    }
    else
    {
        return E_QL_MCM_SIM_APP_TYPE_3GPP;
    }
} 

#define BUF_SIZE 32
static int test_sim(void)
{
    int    cmdIdx  = 0;
    int    ret     = E_QL_OK;
    char    buf[BUF_SIZE] = {0};
        
    show_group_help(&t_sim_test);

    while(1)
    {
        printf("please input cmd index(-1 exit): ");
        scanf("%d", &cmdIdx);
        if(cmdIdx == -1)
        {
            break;
        }
        switch(cmdIdx)
        {
        
        case 0://"QL_MCM_SIM_Client_Init"
        {
            ret = QL_MCM_SIM_Client_Init(&h_sim);
            printf("QL_MCM_SIM_Client_Init ret = %d with h_sim=%d\n", ret, h_sim);
            break;
        }
        case 1://"QL_MCM_SIM_Client_Deinit"
        {
            ret = QL_MCM_SIM_Client_Deinit(h_sim);
            printf("QL_MCM_SIM_Client_Deinit ret = %d\n", ret);
            break;
        }
        case 2://"QL_MCM_SIM_GetIMSI"
        {
            QL_SIM_APP_ID_INFO_T    t_info;

            memset(buf, 0, BUF_SIZE);
            t_info.e_slot_id    = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.e_app        = get_app_type();
            ret = QL_MCM_SIM_GetIMSI(h_sim, &t_info, buf, BUF_SIZE);
            printf("QL_MCM_SIM_GetIMSI ret = %s, IMSI: %s\n", errorcode[ret], buf);
            break;
        }
        case 3://"QL_MCM_SIM_GetICCID"
        {
            memset(buf, 0, BUF_SIZE);
            ret = QL_MCM_SIM_GetICCID(h_sim, E_QL_MCM_SIM_SLOT_ID_1, buf, BUF_SIZE);
            printf("QL_MCM_SIM_GetICCID ret = %s, ICCID: %s\n", errorcode[ret], buf);
            break;
        }
        case 4://"QL_MCM_SIM_GetPhoneNumber"
        {
            QL_SIM_APP_ID_INFO_T    t_info;

            t_info.e_slot_id    = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.e_app        = get_app_type();
            ret = QL_MCM_SIM_GetPhoneNumber(h_sim, &t_info, buf, BUF_SIZE);
            printf("QL_MCM_SIM_GetPhoneNumber ret = %s, phoneNum: %s\n", errorcode[ret], buf);
            break;
        }
        case 5://"QL_MCM_SIM_GetOperatorPlmnList"
        {
            QL_SIM_PREFERRED_OPERATOR_LIST_T    t_info = {0};

            t_info.preferred_operator_list_len = 1;
            t_info.preferred_operator_list[0].mcc[0] = '4';
            t_info.preferred_operator_list[0].mcc[1] = '6';
            t_info.preferred_operator_list[0].mcc[2] = '0';            
            t_info.preferred_operator_list[0].mnc_len= 2;
            t_info.preferred_operator_list[0].mnc[0] = '1';
            t_info.preferred_operator_list[0].mnc[1] = '1';
            t_info.preferred_operator_list[0].mnc[2] = 0xFF;
            ret = QL_MCM_SIM_GetOperatorPlmnList(h_sim, E_QL_MCM_SIM_SLOT_ID_1, &t_info);
            printf("QL_MCM_SIM_GetOperatorPlmnList ret = %s\n", errorcode[ret]);
            break;
        }
        case 6://"QL_MCM_SIM_VerifyPIN"
        {
            QL_SIM_VERIFY_PIN_INFO_T    t_info = {0};

            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            t_info.pin_id               = E_QL_MCM_SIM_PIN_ID_1;
            
            printf("please input pin: \n");
            scanf("%9s", t_info.pin_value);
            t_info.pin_value_len = strlen(t_info.pin_value);
            
            ret = QL_MCM_SIM_VerifyPIN(h_sim, &t_info);
            printf("QL_MCM_SIM_VerifyPIN ret = %s\n", errorcode[ret]);
            break;
        }
        case 7://"QL_MCM_SIM_ChangePin"
        {
            QL_SIM_CHANGE_PIN_INFO_T    t_info = {0};

            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            t_info.pin_id               = E_QL_MCM_SIM_PIN_ID_1;
            
            printf("please input OLD pin: \n");
            scanf("%9s", t_info.old_pin_value);
            t_info.old_pin_value_len = strlen(t_info.old_pin_value);
            
            printf("please input NEW pin: \n");
            scanf("%9s", t_info.new_pin_value);
            t_info.new_pin_value_len = strlen(t_info.new_pin_value);
            
            ret = QL_MCM_SIM_ChangePin(h_sim, &t_info);
            printf("QL_MCM_SIM_ChangePin ret = %s\n", errorcode[ret]);
            break;
        }
        case 8://"QL_MCM_SIM_UnblockPIN"
        {
            QL_SIM_UNBLOCK_PIN_INFO_T    t_info = {0};

            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            t_info.pin_id               = E_QL_MCM_SIM_PIN_ID_1;
            
            printf("please input PUK pin: \n");
            scanf("%9s", t_info.puk_value);
            t_info.puk_value_len = strlen(t_info.puk_value);
            
            printf("please input NEW pin: \n");
            scanf("%9s", t_info.new_pin_value);
            t_info.new_pin_value_len = strlen(t_info.new_pin_value);
            
            ret = QL_MCM_SIM_UnblockPIN(h_sim, &t_info);
            printf("QL_MCM_SIM_UnblockPIN ret = %s\n", errorcode[ret]);
            break;
        }
        case 9://"QL_MCM_SIM_EnablePIN"
        {
            QL_SIM_ENABLE_PIN_INFO_T    t_info = {0};

            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            t_info.pin_id               = E_QL_MCM_SIM_PIN_ID_1;
            
            printf("please input pin: \n");
            scanf("%9s", t_info.pin_value);
            t_info.pin_value_len = strlen(t_info.pin_value);
            
            ret = QL_MCM_SIM_EnablePIN(h_sim, &t_info);
            printf("QL_MCM_SIM_EnablePIN ret = %s\n", errorcode[ret]);
            break;
        }
        case 10://"QL_MCM_SIM_DisablePIN"
        {
            QL_SIM_DISABLE_PIN_INFO_T    t_info = {0};

            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            t_info.pin_id               = E_QL_MCM_SIM_PIN_ID_1;
            
            printf("please input pin: \n");
            scanf("%9s", t_info.pin_value);
            t_info.pin_value_len = strlen(t_info.pin_value);
            
            ret = QL_MCM_SIM_DisablePIN(h_sim, &t_info);
            printf("QL_MCM_SIM_DisablePIN ret = %s\n", errorcode[ret]);
            break;
        }
        case 11://"QL_MCM_SIM_GetCardStatus"
        {
            QL_MCM_SIM_CARD_STATUS_INFO_T   t_info = {0};

            char *card_state[] = {  "UNKNOWN", 
                                    "ABSENT", 
                                    "PRESENT", 
                                    "ERROR_UNKNOWN", 
                                    "ERROR_POWER_DOWN", 
                                    "ERROR_POLL_ERROR", 
                                    "ERROR_NO_ATR_RECEIVED", 
                                    "ERROR_VOLT_MISMATCH", 
                                    "ERROR_PARITY_ERROR", 
                                    "ERROR_SIM_TECHNICAL_PROBLEMS"};            
            char *card_type[]  = {  "UNKNOWN", "ICC", "UICC"};
            char *app_state[]  = {  "UNKNOWN", 
                                    "DETECTED",
                                    "PIN1_REQ",
                                    "PUK1_REQ",
                                    "INITALIZATING",
                                    "PERSO_CK_REQ",
                                    "PERSO_PUK_REQ",
                                    "PERSO_PERMANENTLY_BLOCKED",
                                    "PIN1_PERM_BLOCKED",
                                    "ILLEGAL",
                                    "READY"};            
            ret = QL_MCM_SIM_GetCardStatus(h_sim, E_QL_MCM_SIM_SLOT_ID_1, &t_info);
            printf("QL_MCM_SIM_GetCardStatus ret = %s, card_state=%s, card_type=%s, app_state=%s, pin1_retries=%d\n", 
                    errorcode[ret], 
                    card_state[t_info.e_card_state - 0xB01],
                    card_type[t_info.e_card_type - 0xB00],
                    app_state[t_info.card_app_info.app_3gpp.app_state - 0xB00],
                    t_info.card_app_info.app_3gpp.pin1_num_retries);
            break;
        }
        case 12://"QL_MCM_SIM_Depersonalization"
        {
            QL_MCM_SIM_DEPERSONALIZE_INFO_T     t_info = {0};

            t_info.e_feature_type   = E_QL_MCM_SIM_PERSO_FEATURE_TYPE_3GPP_NETWORK;
            t_info.e_operation      = E_QL_MCM_SIM_PERSO_OPERATION_DEACTIVATE;
            memcpy(t_info.ctrl_key_value, "testonly", strlen("testonly"));
            t_info.ctrl_key_value_len = strlen(t_info.ctrl_key_value);
            
            ret = QL_MCM_SIM_Depersonalization(h_sim, &t_info);
            printf("QL_MCM_SIM_Depersonalization ret = %s\n", errorcode[ret]);
            break;
        }
        case 13://"QL_MCM_SIM_Personalization"
        {
            QL_MCM_SIM_PERSONALIZE_FEATURE_INFO_T   t_info = {0};

            t_info.e_feature_type   = E_QL_MCM_SIM_PERSO_FEATURE_TYPE_3GPP_NETWORK;
            t_info.feature_data_len = 1;
            t_info.t_feature_data.feature_gw_network_perso[0].mcc[0] = '4';
            t_info.t_feature_data.feature_gw_network_perso[0].mcc[1] = '6';
            t_info.t_feature_data.feature_gw_network_perso[0].mcc[2] = '0';
            t_info.t_feature_data.feature_gw_network_perso[0].mnc_len= 2;
            t_info.t_feature_data.feature_gw_network_perso[0].mnc[0] = '1';
            t_info.t_feature_data.feature_gw_network_perso[0].mnc[1] = '1';
            t_info.t_feature_data.feature_gw_network_perso[0].mnc[2] = 0xFF;
            
            memcpy(t_info.ctrl_key_value, "testonly", strlen("testonly"));
            t_info.ctrl_key_value_len = strlen(t_info.ctrl_key_value);
            
            ret = QL_MCM_SIM_Personalization(h_sim, &t_info);
            printf("QL_MCM_SIM_Personalization ret = %s\n", errorcode[ret]);
            break;
        }
        case 14://"QL_MCM_SIM_WriteFile"
        {
            QL_MCM_SIM_CARD_WRITE_FILE_INFO_T   *pt_info = NULL;

            pt_info = (QL_MCM_SIM_CARD_WRITE_FILE_INFO_T *)malloc(sizeof(QL_MCM_SIM_CARD_WRITE_FILE_INFO_T));
            
            pt_info->app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            pt_info->app_info.e_app       = get_app_type();
            pt_info->file_access.offset   = 0;
            
            printf("please input file path: \n");
            scanf("%13s", pt_info->file_access.path);
            pt_info->file_access.path_len = strlen(pt_info->file_access.path);
            
            printf("please input record num(0: transparent mode, other:directly access): \n");
            scanf("%d", &pt_info->file_access.record_num);

            pt_info->data_len = get_data_array(pt_info->data, QL_MCM_SIM_DATA_LEN_MAX);
                        
            ret = QL_MCM_SIM_WriteFile(h_sim, pt_info);
            printf("QL_MCM_SIM_WriteFile ret = %d\n", ret);

            free(pt_info);
            break;
        }
        case 15://"QL_MCM_SIM_ReadFile"
        {
            int i;
            QL_MCM_SIM_CARD_FILE_INFO_TO_READ_T     t_info  = {0};
            QL_MCM_SIM_CARD_FILE_DATA_T             t_out   = {0};
            
            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            t_info.file_access.offset   = 0;

            printf("please input file path: \n");
            scanf("%13s", t_info.file_access.path);
            t_info.file_access.path_len = strlen(t_info.file_access.path);
                
            printf("please input record num(0: transparent mode, other:directly access): \n");
            scanf("%d", &i);
            t_info.file_access.record_num = i;
            
            ret = QL_MCM_SIM_ReadFile(h_sim, &t_info, &t_out);
            printf("QL_MCM_SIM_ReadFile ret = %d, Content[%d]:\n", ret, t_out.data_len);
            for(i=0; i<t_out.data_len; i++)
            {
                printf("%X ", t_out.data[i]);
            }
            printf("\n\n");
            break;
        }
        case 16://"QL_MCM_SIM_GetFileSize"
        {    
            QL_MCM_SIM_CARD_GET_FILE_SIZE_INPUT_INFO_T  t_info  = {0};
            QL_MCM_SIM_FILE_SIZE_INFO_T                 t_out   = {0};
            char    *filetype[] = {"UNKNOWN", "TRANSPARENT", "CYCLIC", "LINEAR_FIXED"};
            
            t_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.app_info.e_app       = get_app_type();
            
            printf("please input file path: \n");
            scanf("%13s", t_info.path);
            t_info.path_len = strlen(t_info.path);

            ret = QL_MCM_SIM_GetFileSize(h_sim, &t_info, &t_out);
            printf("QL_MCM_SIM_GetFileSize ret = %d, e_file_type=%s, filesize=%d, record_size=%d, record_count=%d\n", 
                    ret, 
                    filetype[t_out.e_file_type - 0xB00],
                    t_out.file_size,
                    t_out.record_size,
                    t_out.record_count);
            break;
        }
        case 17://"QL_MCM_SIM_ReadPhoneBookRecord"
        {
            int record_idx = 0;
            QL_MCM_SIM_PHONE_BOOK_RECORD_INFO_T  t_info  = {0};
            
            t_info.file_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.file_info.app_info.e_app       = get_app_type();
            
            printf("please input store file path(Use SIM phonebook '3F007F106F3A' only): \n");            
            printf( "\tSM: SIM phonebook ==> ONLY support this now \n"
                    "\tDC: ME dialed calls list(may not applicable) \n"
                    "\tFD: SIM fix dialing phonebook(need the authority of PIN2) \n"
                    "\tLD: SIM last-dialing phonebook(may not applicable) \n"
                    "\tMC: ME missed(unanswered) calls list(may not applicable) \n"
                    "\tME: Mobile equipment phonebook \n"
                    "\tRC: ME received calls list(may not applicable) \n"
                    "\tEN: SIM or ME emergency number(may not applicable) \n"
                    "\tON: SIM own numbers(MSISDNs) list \n");
            
            scanf("%13s", t_info.file_info.file_access.path);
            t_info.file_info.file_access.path_len = strlen(t_info.file_info.file_access.path);

            printf("input file path:%s, len=%d \n", 
                t_info.file_info.file_access.path, 
                t_info.file_info.file_access.path_len);
            
            printf("please input phone book record index: \n");
            scanf("%d", &record_idx);
            t_info.file_info.file_access.record_num = record_idx;

            ret = QL_MCM_SIM_ReadPhoneBookRecord(h_sim, &t_info);
            printf("QL_MCM_SIM_ReadPhoneBookRecord ret = %d, username=%s, phonenumber=%s\n", 
                    ret, 
                    t_info.t_record.username,
                    t_info.t_record.phonenum);
            break;
        }
        case 18://"QL_MCM_SIM_WritePhoneBookRecord"
        {    
            int record_idx = 0;
            QL_MCM_SIM_PHONE_BOOK_RECORD_INFO_T  t_info  = {0};
            
            t_info.file_info.app_info.e_slot_id   = E_QL_MCM_SIM_SLOT_ID_1;
            t_info.file_info.app_info.e_app       = get_app_type();
            
            printf("please input user name('d' means delete): \n");
            scanf("%14s", t_info.t_record.username);

            if(strcmp(t_info.t_record.username, "d") == 0)
            {
                memset(t_info.t_record.username, 0, 14);//username & phonebum empty means to delete this record specified by record_num
                memset(t_info.t_record.phonenum, 0, 24);
            }
            else
            {
                printf("please input phone number: \n");
                scanf("%24s",  t_info.t_record.phonenum);
            }
            
            printf("please input store file path(Use SIM phonebook '3F007F106F3A' only): \n");            
            printf( "\tSM: SIM phonebook ==> ONLY support this now \n"
                    "\tDC: ME dialed calls list(may not applicable) \n"
                    "\tFD: SIM fix dialing phonebook(need the authority of PIN2) \n"
                    "\tLD: SIM last-dialing phonebook(may not applicable) \n"
                    "\tMC: ME missed(unanswered) calls list(may not applicable) \n"
                    "\tME: Mobile equipment phonebook \n"
                    "\tRC: ME received calls list(may not applicable) \n"
                    "\tEN: SIM or ME emergency number(may not applicable) \n"
                    "\tON: SIM own numbers(MSISDNs) list \n");
            
            scanf("%13s", t_info.file_info.file_access.path);
            t_info.file_info.file_access.path_len = strlen(t_info.file_info.file_access.path);
                        
            printf("please input store index: \n");
            scanf("%d", &record_idx);
            t_info.file_info.file_access.record_num = record_idx;

            ret = QL_MCM_SIM_WritePhoneBookRecord(h_sim, &t_info);
            printf("QL_MCM_SIM_WritePhoneBookRecord ret = %d, username=%s, phonenumber=%s\n", 
                    ret, 
                    t_info.t_record.username,
                    t_info.t_record.phonenum);
            break;
        }

        default:
            show_group_help(&t_sim_test);
        }
    }
    return 0;
}


func_api_test_t t_sim_test = {"mcm_sim", at_sim_testlist, test_sim};


