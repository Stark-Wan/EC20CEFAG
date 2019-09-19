#ifndef MCM_VOICE_SERVICE_01_H
#define MCM_VOICE_SERVICE_01_H
/**
  @file mcm_voice_v01.h

  @brief This is the public header file which defines the mcm_voice service Data structures.

  This header file defines the types and structures that were defined in
  mcm_voice. It contains the constant values defined, enums, structures,
  messages, and service message IDs (in that order) Structures that were
  defined in the IDL as messages contain mandatory elements, optional
  elements, a combination of mandatory and optional elements (mandatory
  always come before optionals in the structure), or nothing (null message)

  An optional element in a message is preceded by a uint8_t value that must be
  set to true if the element is going to be included. When decoding a received
  message, the uint8_t values will be set to true or false by the decode
  routine, and should be checked before accessing the values that they
  correspond to.

  Variable sized arrays are defined as static sized arrays with an unsigned
  integer (32 bit) preceding it that must be set to the number of elements
  in the array that are valid. For Example:

  uint32_t test_opaque_len;
  uint8_t test_opaque[16];

  If only 4 elements are added to test_opaque[] then test_opaque_len must be
  set to 4 before sending the message.  When decoding, the _len value is set
  by the decode routine and should be checked so that the correct number of
  elements in the array will be accessed.

*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
  

  
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/
/*====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*
 *THIS IS AN AUTO GENERATED FILE. DO NOT ALTER IN ANY WAY
 *====*====*====*====*====*====*====*====*====*====*====*====*====*====*====*/

/* This file was generated with Tool version 6.14.7 
   It was generated on: Thu Jul 12 2018 (Spin 0)
   From IDL File: mcm_voice_v01.idl */

/** @defgroup mcm_voice_qmi_consts Constant values defined in the IDL */
/** @defgroup mcm_voice_qmi_msg_ids Constant values for QMI message IDs */
/** @defgroup mcm_voice_qmi_enums Enumerated types used in QMI messages */
/** @defgroup mcm_voice_qmi_messages Structures sent as QMI messages */
/** @defgroup mcm_voice_qmi_aggregates Aggregate types used in QMI messages */
/** @defgroup mcm_voice_qmi_accessor Accessor for QMI service object */
/** @defgroup mcm_voice_qmi_version Constant values for versioning information */

#include <stdint.h>
#include "mcm_common_v01.h"


#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup mcm_voice_qmi_version
    @{
  */
/** Major Version Number of the IDL used to generate this file */
#define MCM_VOICE_V01_IDL_MAJOR_VERS 0x01
/** Revision Number of the IDL used to generate this file */
#define MCM_VOICE_V01_IDL_MINOR_VERS 0x02
/** Major Version Number of the qmi_idl_compiler used to generate this file */
#define MCM_VOICE_V01_IDL_TOOL_VERS 0x06

/**
    @}
  */


/** @addtogroup mcm_voice_qmi_consts
    @{
  */

/**  GSM provides up to 8 calls; 3GPP2 provides 2. */
#define MCM_MAX_VOICE_CALLS_V01 8
#define MCM_MAX_PHONE_NUMBER_V01 82

/**  Maximum user-to-user data. */
#define MCM_MAX_UUS_DATA_V01 20

/**  Maximum DTMF length. */
#define MCM_MAX_DTMF_LENGTH_V01 20

/**  Maximum USSD length. */
#define MCM_MAX_USSD_LENGTH_V01 128

/**  Maximum password length. */
#define MCM_MAX_PASSWORD_LENGTH_V01 4

/**  Maximum call forwarding information. */
#define MCM_MAX_CALL_FORWARDING_INFO_V01 13

/**  Maximum size of the MSD sent to the network with an eCall */
#define MCM_MAX_ECALL_MSD_V01 140

/**  Maximum size of the ecall urc event */
#define MCM_MAX_ECALL_URC_EVENT_LENGTH_V01 128
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_STATE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_STATE_INCOMING_V01 = 0x0000, /**< MT incoming; CC setup. */
  MCM_VOICE_CALL_STATE_DIALING_V01 = 0x0001, /**< Dialing state. */
  MCM_VOICE_CALL_STATE_ALERTING_V01 = 0x0002, /**< MT call waiting; MO alterting. */
  MCM_VOICE_CALL_STATE_ACTIVE_V01 = 0x0003, /**< Call is active. */
  MCM_VOICE_CALL_STATE_HOLDING_V01 = 0x0004, /**< Call is on hold. */
  MCM_VOICE_CALL_STATE_END_V01 = 0x0005, /**< Call is disconnected. */
  MCM_VOICE_CALL_STATE_WAITING_V01 = 0x0006, /**< Call is waiting. */
  MCM_VOICE_CALL_STATE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_state_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_TYPE_NOT_SPECIFIED_V01 = 0x0000, /**< Placeholder for a zero value. */
  MCM_VOICE_CALL_TYPE_VOICE_V01 = 0x0001, /**<  Voice call. */
  MCM_VOICE_CALL_TYPE_EMERGENCY_V01 = 0x0002, /**<  Emergency call. */
  MCM_VOICE_CALL_TYPE_ECALL_AUTO_V01 = 0x0003, /**<  Automatically triggered eCall */
  MCM_VOICE_CALL_TYPE_ECALL_MANUAL_V01 = 0x0004, /**<  Manually triggered eCall */
  MCM_VOICE_CALL_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_DIRECTION_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_MOBILE_ORIGINATED_V01 = 0x0000, /**<  Mobile-originated. */
  MCM_VOICE_CALL_MOBILE_TERMINATED_V01 = 0x0001, /**<  Mobile-terminated. */
  MCM_VOICE_CALL_DIRECTION_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_direction_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_NUMBER_PRESENTATION_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_NUMBER_UNKNOWN_V01 = 0x0000, 
  MCM_VOICE_CALL_NUMBER_ALLOWED_V01 = 0x0001, /**<  Number allowed. */
  MCM_VOICE_CALL_NUMBER_RESTRICTED_V01 = 0x0002, /**<  Number restricted. */
  MCM_VOICE_CALL_NUMBER_PAYPHONE_V01 = 0x0003, /**<  Payhone number. */
  MCM_VOICE_CALL_NUMBER_PRESENTATION_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_number_presentation_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_REASON_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_REASON_NONE_V01 = 1, /**< Placeholder for a zero value. */
  MCM_VOICE_REASON_NORMAL_V01 = 2, /**<  Call ended normally. */
  MCM_VOICE_REASON_BUSY_V01 = 3, /**<  Call was rejected (busy). */
  MCM_VOICE_REASON_CONGESTION_V01 = 4, /**<  Network congestion. */
  MCM_VOICE_REASON_CALL_BARRED_V01 = 5, /**<  Incoming calls barred. */
  MCM_VOICE_REASON_FDN_BLOCKED_V01 = 6, /**<  Blocked by fixed dialing. */
  MCM_VOICE_REASON_DIAL_MODIFIED_TO_USSD_V01 = 7, /**<  Converted to a USSD message. */
  MCM_VOICE_REASON_DIAL_MODIFIED_TO_SS_V01 = 8, /**<  Converted to a SUP. */
  MCM_VOICE_REASON_DIAL_MODIFIED_TO_DIAL_V01 = 9, /**<  Converted to another call type. */
  MCM_VOICE_REASON_ACM_LIMIT_EXCEEDED_V01 = 10, /**<  No funds. */
  MCM_VOICE_REASON_NETWORK_GENERIC_ERROR_V01 = 11, 
  MCM_VOICE_REASON_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_reason_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_OPERATION_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_ANSWER_V01 = 0, /**< Answer the call. */
  MCM_VOICE_CALL_END_V01 = 1, /**< Deprecated. Do not use. */
  MCM_VOICE_CALL_HOLD_V01 = 2, /**< Hold the call. */
  MCM_VOICE_CALL_UNHOLD_V01 = 3, /**< Release the call from hold. */
  MCM_VOICE_CALL_CONFERENCE_V01 = 4, /**< Conference call. */
  MCM_VOICE_CALL_GO_PRIVATE_V01 = 5, /**< Private call. */
  MCM_VOICE_CALL_END_ALL_V01 = 6, /**< End all calls. */
  MCM_VOICE_CALL_OPERATION_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_operation_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_UUS_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_UUS_TYPE1_IMPLICIT_V01 = 0, /**<  Type 1 implicit. */
  MCM_VOICE_UUS_TYPE1_REQUIRED_V01 = 1, /**<  Type 1 required. */
  MCM_VOICE_UUS_TYPE1_NOT_REQUIRED_V01 = 2, /**<  Type 1 not required. */
  MCM_VOICE_UUS_TYPE2_REQUIRED_V01 = 3, /**<  Type 2 required. */
  MCM_VOICE_UUS_TYPE2_NOT_REQUIRED_V01 = 4, /**<  Type 2 not required. */
  MCM_VOICE_UUS_TYPE3_REQUIRED_V01 = 5, /**<  Type 3 required. */
  MCM_VOICE_UUS_TYPE3_NOT_REQUIRED_V01 = 6, /**<  Type 3 not required. */
  MCM_VOICE_UUS_TYPE_DATA_V01 = 7, /**<  Data. */
  MCM_VOICE_UUS_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_uus_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_UUS_DCS_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_UUS_DCS_IA5_V01 = 0, /**<  IA5. */
  MCM_VOICE_UUS_DCS_OHLP_V01 = 1, /**<  OHLP. */
  MCM_VOICE_UUS_DCS_USP_V01 = 2, /**<  USP. */
  MCM_VOICE_UUS_DCS_X244_V01 = 3, /**<  x244. */
  MCM_VOICE_UUS_DCS_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_uus_dcs_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_TECH_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_TECH_NONE_V01 = 0, /**<  None. */
  MCM_VOICE_TECH_3GPP_V01 = 1, /**<  3GPP. */
  MCM_VOICE_TECH_3GPP2_V01 = 2, /**<  3GPP2. */
  MCM_VOICE_TECH_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_tech_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_FORWARDING_STATUS_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_FORWARDING_DISABLED_V01 = 0, /**<  Disabled. */
  MCM_VOICE_CALL_FORWARDING_ENABLED_V01 = 1, /**<  Enabled. */
  MCM_VOICE_CALL_FORWARDING_STATUS_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_forwarding_status_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_FORWARDING_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_FORWARDING_TYPE_VOICE_V01 = 0, /**<  Voice. */
  MCM_VOICE_CALL_FORWARDING_TYPE_DATA_V01 = 1, /**<  Data. */
  MCM_VOICE_CALL_FORWARDING_TYPE_VOICE_DATA_V01 = 2, /**<  Voice and data. */
  MCM_VOICE_CALL_FORWARDING_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_forwarding_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_WAITING_SERVICE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_WAITING_VOICE_ENABLED_V01 = 0, /**<  Voice call waiting enabled. */
  MCM_VOICE_CALL_WAITING_DATA_ENABLED_V01 = 1, /**<  Data call waiting enabled. */
  MCM_VOICE_CALL_WAITING_VOICE_DATA_ENABLED_V01 = 2, /**<  Voice and data call waiting enabled. */
  MCM_VOICE_CALL_WAITING_DISABLED_V01 = 3, /**<  Voice call waiting disabled. */
  MCM_VOICE_CALL_WAITING_SERVICE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_waiting_service_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_SERVICE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_SERVICE_ACTIVATE_V01 = 0, /**<  Activate. */
  MCM_VOICE_SERVICE_DEACTIVATE_V01 = 1, /**<  Deactivate. */
  MCM_VOICE_SERVICE_REGISTER_V01 = 2, /**<  Register. */
  MCM_VOICE_SERVICE_ERASE_V01 = 3, /**<  Erase. */
  MCM_VOICE_CALL_SERVICE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_service_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_FORWARDING_REASON_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_FORWARD_UNCONDITIONALLY_V01 = 0, /**<  Unconditional call forwarding. */
  MCM_VOICE_CALL_FORWARD_MOBILEBUSY_V01 = 1, /**<  Forward when the mobile device is busy. */
  MCM_VOICE_CALL_FORWARD_NOREPLY_V01 = 2, /**<  Forward when there is no reply. */
  MCM_VOICE_CALL_FORWARD_UNREACHABLE_V01 = 3, /**<  Forward when the call is unreachable. */
  MCM_VOICE_CALL_FORWARD_ALLFORWARDING_V01 = 4, /**<  All forwarding. */
  MCM_VOICE_CALL_FORWARD_ALLCONDITIONAL_V01 = 5, /**<  All conditional forwarding. */
  MCM_VOICE_CALL_FORWARDING_REASON_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_forwarding_reason_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CLIR_ACTION_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CLIR_INVOCATION_V01 = 0, /**<  Invocation. */
  MCM_VOICE_CLIR_SUPPRESSION_V01 = 1, /**<  Suppression. */
  MCM_VOICE_CLIR_ACTION_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_clir_action_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CLIR_PRESENTATION_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CLIR_NOT_PROVISIONED_V01 = 0, /**<  Not provisioned. */
  MCM_VOICE_CLIR_PROVISIONED_PERMANENT_MODE_V01 = 1, /**<  Permanently provisioned. */
  MCM_VOICE_CLIR_PRESENTATION_RESTRICTED_V01 = 2, /**<  Restricted presentation. */
  MCM_VOICE_CLIR_PRESENTATION_ALLOWED_V01 = 3, /**<  Allowed presentation. */
  MCM_VOICE_CLIR_PRESENTATION_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_clir_presentation_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_FACILITY_LOCK_STATUS_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_FACILITY_LOCK_ENABLE_V01 = 0, /**<  Enable. */
  MCM_VOICE_FACILITY_LOCK_DISABLE_V01 = 1, /**<  Disable. */
  MCM_VOICE_FACILITY_LOCK_STATUS_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_facility_lock_status_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_FACILITY_CODE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_FACILITY_CODE_AO_V01 = 0, /**< BAOC (Bar All Outgoing Calls) (refer to 3GPP TS 22.088 @xhyperref{S9,[S9]} clause 1). */
  MCM_VOICE_FACILITY_CODE_OI_V01 = 1, /**< BOIC (Bar Outgoing International Calls) (refer to 3GPP TS 22.088 @xhyperref{S9,[S9]}
clause 1). */
  MCM_VOICE_FACILITY_CODE_OX_V01 = 2, /**< BOIC-exHC (Bar Outgoing International Calls except to Home Country)
 (refer to 3GPP TS 22.088 @xhyperref{S9,[S9]} clause 1). */
  MCM_VOICE_FACILITY_CODE_AI_V01 = 3, /**< BAIC (Bar All Incoming Calls) (refer to 3GPP TS 22.088 @xhyperref{S9,[S9]} clause 2). */
  MCM_VOICE_FACILITY_CODE_IR_V01 = 4, /**< BIC-Roam (Bar Incoming Calls when Roaming outside the home country)
 (refer to 3GPP TS 22.088 @xhyperref{S9,[S9]} clause 2). */
  MCM_VOICE_FACILITY_CODE_AB_V01 = 5, /**< All barring services (refer to 3GPP TS 22.030 @xhyperref{S10,[S10]}) (applicable only
 for mode=0). */
  MCM_VOICE_FACILITY_CODE_AG_V01 = 6, /**< All outgoing barring services (refer to 3GPP TS 22.030 @xhyperref{S10,[S10]})
 (applicable only for mode=0). */
  MCM_VOICE_FACILITY_CODE_AC_V01 = 7, /**< All incoming barring services (refer to 3GPP TS 22.030 @xhyperref{S10,[S10]})
 (applicable only for mode=0). */
  MCM_VOICE_FACILITY_CODE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_facility_code_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_ALLOUTGOING_V01 = 0, /**<  All outgoing. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_OUTGOINGINT_V01 = 1, /**<  Outgoing internal. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_OUTGOINGINTEXTOHOME_V01 = 2, /**<  Outgoing external to home. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_ALLINCOMING_V01 = 3, /**<  All incoming. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_INCOMINGROAMING_V01 = 4, /**<  Roaming incoming. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_ALLBARRING_V01 = 5, /**<  All calls are barred. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_ALLOUTGOINGBARRING_V01 = 6, /**<  All outgoing calls are barred. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_ALLINCOMINGBARRING_V01 = 7, /**<  All incoming calls are barred. */
  MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REASON_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_change_call_barring_password_reason_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_USSD_ENCODING_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_USSD_ENCODING_ASCII_V01 = 0, /**<  ASCII coding scheme. */
  MCM_VOICE_USSD_ENCODING_8BIT_V01 = 1, /**<  8-bit coding scheme. */
  MCM_VOICE_USSD_ENCODING_UCS2_V01 = 2, /**<  UCS2. */
  MCM_VOICE_USSD_ENCODING_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ussd_encoding_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_COMMON_DIAL_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_COMMON_DIAL_VOICE_V01 = 0, /**<  Voice. */
  MCM_VOICE_COMMON_DIAL_SS_V01 = 1, /**<  Supplementary service. */
  MCM_VOICE_COMMON_DIAL_USSD_V01 = 2, /**<  Unstructured supplementary service. */
  MCM_VOICE_COMMON_DIAL_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_common_dial_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_MUTE_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_MUTE_V01 = 0, /**<  Mute. */
  MCM_VOICE_UNMUTE_V01 = 1, /**<  Unmute. */
  MCM_VOICE_MUTE_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_mute_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_AUTO_ANSWER_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_AUTO_ANSWER_ENABLE_V01 = 0, /**<  Enable auto-answer. */
  MCM_VOICE_AUTO_ANSWER_DISABLE_V01 = 1, /**<  Disable auto-answer. */
  MCM_VOICE_AUTO_ANSWER_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_auto_answer_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_DTMF_EVENT_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_DTMF_EVENT_BURST_V01 = 0, /**<  Burst DTMF. */
  MCM_VOICE_DTMF_EVENT_START_CONT_V01 = 1, /**<  Continuous DTMF start. */
  MCM_VOICE_DTMF_EVENT_STOP_CONT_V01 = 2, /**<  Continuous DTMF stop. */
  MCM_VOICE_DTMF_EVENT_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_dtmf_event_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_USSD_MSG_TYPE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_USSD_MSG_TYPE_NEW_MESSAGE_V01 = 0, /**<  Initiate a new USSD sesion with network. */
  MCM_VOICE_USSD_MSG_TYPE_REPLY_TO_IND_V01 = 1, /**<  Reply to a USSD indication from the network. */
  MCM_VOICE_USSD_MSG_TYPE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ussd_msg_type_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_USSD_IND_NOTIFICATION_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_USSD_INDICATION_FURTHER_ACTION_NOT_REQUIRED_V01 = 0, /**<  USSD indication requires a USSD reply. */
  MCM_VOICE_USSD_INDICATION_FURTHER_ACTION_REQUIRED_V01 = 1, /**<  USSD indication does not require a reply. */
  MCM_VOICE_USSD_IND_NOTIFICATION_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ussd_ind_notification_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_EMERGENCY_CAT_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_EMER_CAT_POLICE_V01 = 0, /**<  Police */
  MCM_VOICE_EMER_CAT_AMBULANCE_V01 = 1, /**<  Ambulance */
  MCM_VOICE_EMER_CAT_FIRE_BRIGADE_V01 = 2, /**<  Fire brigade */
  MCM_VOICE_EMER_CAT_MARINE_GUARD_V01 = 3, /**<  Marine guard */
  MCM_VOICE_EMER_CAT_MOUNTAIN_RESCUE_V01 = 4, /**<  Mountain rescue */
  MCM_VOICE_EMERGENCY_CAT_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_emergency_cat_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_E911_STATE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_E911_INACTIVE_V01 = 0, /**<  E911 INACTIVE. */
  MCM_VOICE_E911_ACTIVE_V01 = 1, /**<  E911 ACTIVE. */
  MCM_VOICE_E911_STATE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_e911_state_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_ECALL_VARIANT_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_ECALL_TEST_V01 = 0x01, /**<   Test eCall \n   */
  MCM_ECALL_EMERGENCY_V01 = 0x02, /**<   Emergency eCall \n   */
  MCM_ECALL_RECONFIG_V01 = 0x03, /**<   Reconfig eCall   */
  MCM_ECALL_VARIANT_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_ecall_variant_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  mcm_voice_uus_type_t_v01 type;
  /**<   UUS type; range -- 0 to 6.*/

  mcm_voice_uus_dcs_type_t_v01 dcs;
  /**<   UUS data coding scheme; range -- 0 to 4.*/

  uint32_t uus_data_len;  /**< Must be set to # of elements in uus_data */
  uint8_t uus_data[MCM_MAX_UUS_DATA_V01];
  /**<   Voice call UUS data.*/
}mcm_voice_uusdata_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_CALL_END_REASON_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_CALL_END_REASON_NONE_V01 = 0, 
  MCM_VOICE_CALL_END_CAUSE_OFFLINE_V01 = 1, 
  MCM_VOICE_CALL_END_CAUSE_CDMA_LOCK_V01 = 2, 
  MCM_VOICE_CALL_END_CAUSE_NO_SRV_V01 = 3, 
  MCM_VOICE_CALL_END_CAUSE_FADE_V01 = 4, 
  MCM_VOICE_CALL_END_CAUSE_INTERCEPT_V01 = 5, 
  MCM_VOICE_CALL_END_CAUSE_REORDER_V01 = 6, 
  MCM_VOICE_CALL_END_CAUSE_REL_NORMAL_V01 = 7, 
  MCM_VOICE_CALL_END_CAUSE_REL_SO_REJ_V01 = 8, 
  MCM_VOICE_CALL_END_CAUSE_INCOM_CALL_V01 = 9, 
  MCM_VOICE_CALL_END_CAUSE_ALERT_STOP_V01 = 10, 
  MCM_VOICE_CALL_END_CAUSE_CLIENT_END_V01 = 11, 
  MCM_VOICE_CALL_END_CAUSE_ACTIVATION_V01 = 12, 
  MCM_VOICE_CALL_END_CAUSE_MC_ABORT_V01 = 13, 
  MCM_VOICE_CALL_END_CAUSE_MAX_ACCESS_PROBE_V01 = 14, 
  MCM_VOICE_CALL_END_CAUSE_PSIST_N_V01 = 15, 
  MCM_VOICE_CALL_END_CAUSE_UIM_NOT_PRESENT_V01 = 16, 
  MCM_VOICE_CALL_END_CAUSE_ACC_IN_PROG_V01 = 17, 
  MCM_VOICE_CALL_END_CAUSE_ACC_FAIL_V01 = 18, 
  MCM_VOICE_CALL_END_CAUSE_RETRY_ORDER_V01 = 19, 
  MCM_VOICE_CALL_END_CAUSE_CCS_NOT_SUPPORTED_BY_BS_V01 = 20, 
  MCM_VOICE_CALL_END_CAUSE_NO_RESPONSE_FROM_BS_V01 = 21, 
  MCM_VOICE_CALL_END_CAUSE_REJECTED_BY_BS_V01 = 22, 
  MCM_VOICE_CALL_END_CAUSE_INCOMPATIBLE_V01 = 23, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_BLOCK_V01 = 24, 
  MCM_VOICE_CALL_END_CAUSE_ALREADY_IN_TC_V01 = 25, 
  MCM_VOICE_CALL_END_CAUSE_EMERGENCY_FLASHED_V01 = 26, 
  MCM_VOICE_CALL_END_CAUSE_USER_CALL_ORIG_DURING_GPS_V01 = 27, 
  MCM_VOICE_CALL_END_CAUSE_USER_CALL_ORIG_DURING_SMS_V01 = 28, 
  MCM_VOICE_CALL_END_CAUSE_USER_CALL_ORIG_DURING_DATA_V01 = 29, 
  MCM_VOICE_CALL_END_CAUSE_REDIR_OR_HANDOFF_V01 = 30, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_BLOCK_ALL_V01 = 31, 
  MCM_VOICE_CALL_END_CAUSE_OTASP_SPC_ERR_V01 = 32, 
  MCM_VOICE_CALL_END_CAUSE_IS707B_MAX_ACC_V01 = 33, 
  MCM_VOICE_CALL_END_CAUSE_ACC_FAIL_REJ_ORD_V01 = 34, 
  MCM_VOICE_CALL_END_CAUSE_ACC_FAIL_RETRY_ORD_V01 = 35, 
  MCM_VOICE_CALL_END_CAUSE_TIMEOUT_T42_V01 = 36, 
  MCM_VOICE_CALL_END_CAUSE_TIMEOUT_T40_V01 = 37, 
  MCM_VOICE_CALL_END_CAUSE_SRV_INIT_FAIL_V01 = 38, 
  MCM_VOICE_CALL_END_CAUSE_T50_EXP_V01 = 39, 
  MCM_VOICE_CALL_END_CAUSE_T51_EXP_V01 = 40, 
  MCM_VOICE_CALL_END_CAUSE_RL_ACK_TIMEOUT_V01 = 41, 
  MCM_VOICE_CALL_END_CAUSE_BAD_FL_V01 = 42, 
  MCM_VOICE_CALL_END_CAUSE_TRM_REQ_FAIL_V01 = 43, 
  MCM_VOICE_CALL_END_CAUSE_TIMEOUT_T41_V01 = 44, 
  MCM_VOICE_CALL_END_CAUSE_INCOM_REJ_V01 = 45, 
  MCM_VOICE_CALL_END_CAUSE_SETUP_REJ_V01 = 46, 
  MCM_VOICE_CALL_END_CAUSE_NETWORK_END_V01 = 47, 
  MCM_VOICE_CALL_END_CAUSE_NO_FUNDS_V01 = 48, 
  MCM_VOICE_CALL_END_CAUSE_NO_GW_SRV_V01 = 49, 
  MCM_VOICE_CALL_END_CAUSE_NO_CDMA_SRV_V01 = 50, 
  MCM_VOICE_CALL_END_CAUSE_NO_FULL_SRV_V01 = 51, 
  MCM_VOICE_CALL_END_CAUSE_MAX_PS_CALLS_V01 = 52, 
  MCM_VOICE_CALL_END_CAUSE_UNKNOWN_SUBSCRIBER_V01 = 53, 
  MCM_VOICE_CALL_END_CAUSE_ILLEGAL_SUBSCRIBER_V01 = 54, 
  MCM_VOICE_CALL_END_CAUSE_BEARER_SERVICE_NOT_PROVISIONED_V01 = 55, 
  MCM_VOICE_CALL_END_CAUSE_TELE_SERVICE_NOT_PROVISIONED_V01 = 56, 
  MCM_VOICE_CALL_END_CAUSE_ILLEGAL_EQUIPMENT_V01 = 57, 
  MCM_VOICE_CALL_END_CAUSE_CALL_BARRED_V01 = 58, 
  MCM_VOICE_CALL_END_CAUSE_ILLEGAL_SS_OPERATION_V01 = 59, 
  MCM_VOICE_CALL_END_CAUSE_SS_ERROR_STATUS_V01 = 60, 
  MCM_VOICE_CALL_END_CAUSE_SS_NOT_AVAILABLE_V01 = 61, 
  MCM_VOICE_CALL_END_CAUSE_SS_SUBSCRIPTION_VIOLATION_V01 = 62, 
  MCM_VOICE_CALL_END_CAUSE_SS_INCOMPATIBILITY_V01 = 63, 
  MCM_VOICE_CALL_END_CAUSE_FACILITY_NOT_SUPPORTED_V01 = 64, 
  MCM_VOICE_CALL_END_CAUSE_ABSENT_SUBSCRIBER_V01 = 65, 
  MCM_VOICE_CALL_END_CAUSE_SHORT_TERM_DENIAL_V01 = 66, 
  MCM_VOICE_CALL_END_CAUSE_LONG_TERM_DENIAL_V01 = 67, 
  MCM_VOICE_CALL_END_CAUSE_SYSTEM_FAILURE_V01 = 68, 
  MCM_VOICE_CALL_END_CAUSE_DATA_MISSING_V01 = 69, 
  MCM_VOICE_CALL_END_CAUSE_UNEXPECTED_DATA_VALUE_V01 = 70, 
  MCM_VOICE_CALL_END_CAUSE_PWD_REGISTRATION_FAILURE_V01 = 71, 
  MCM_VOICE_CALL_END_CAUSE_NEGATIVE_PWD_CHECK_V01 = 72, 
  MCM_VOICE_CALL_END_CAUSE_NUM_OF_PWD_ATTEMPTS_VIOLATION_V01 = 73, 
  MCM_VOICE_CALL_END_CAUSE_POSITION_METHOD_FAILURE_V01 = 74, 
  MCM_VOICE_CALL_END_CAUSE_UNKNOWN_ALPHABET_V01 = 75, 
  MCM_VOICE_CALL_END_CAUSE_USSD_BUSY_V01 = 76, 
  MCM_VOICE_CALL_END_CAUSE_REJECTED_BY_USER_V01 = 77, 
  MCM_VOICE_CALL_END_CAUSE_REJECTED_BY_NETWORK_V01 = 78, 
  MCM_VOICE_CALL_END_CAUSE_DEFLECTION_TO_SERVED_SUBSCRIBER_V01 = 79, 
  MCM_VOICE_CALL_END_CAUSE_SPECIAL_SERVICE_CODE_V01 = 80, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_DEFLECTED_TO_NUMBER_V01 = 81, 
  MCM_VOICE_CALL_END_CAUSE_MPTY_PARTICIPANTS_EXCEEDED_V01 = 82, 
  MCM_VOICE_CALL_END_CAUSE_RESOURCES_NOT_AVAILABLE_V01 = 83, 
  MCM_VOICE_CALL_END_CAUSE_UNASSIGNED_NUMBER_V01 = 84, 
  MCM_VOICE_CALL_END_CAUSE_NO_ROUTE_TO_DESTINATION_V01 = 85, 
  MCM_VOICE_CALL_END_CAUSE_CHANNEL_UNACCEPTABLE_V01 = 86, 
  MCM_VOICE_CALL_END_CAUSE_OPERATOR_DETERMINED_BARRING_V01 = 87, 
  MCM_VOICE_CALL_END_CAUSE_NORMAL_CALL_CLEARING_V01 = 88, 
  MCM_VOICE_CALL_END_CAUSE_USER_BUSY_V01 = 89, 
  MCM_VOICE_CALL_END_CAUSE_NO_USER_RESPONDING_V01 = 90, 
  MCM_VOICE_CALL_END_CAUSE_USER_ALERTING_NO_ANSWER_V01 = 91, 
  MCM_VOICE_CALL_END_CAUSE_CALL_REJECTED_V01 = 92, 
  MCM_VOICE_CALL_END_CAUSE_NUMBER_CHANGED_V01 = 93, 
  MCM_VOICE_CALL_END_CAUSE_PREEMPTION_V01 = 94, 
  MCM_VOICE_CALL_END_CAUSE_DESTINATION_OUT_OF_ORDER_V01 = 95, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_NUMBER_FORMAT_V01 = 96, 
  MCM_VOICE_CALL_END_CAUSE_FACILITY_REJECTED_V01 = 97, 
  MCM_VOICE_CALL_END_CAUSE_RESP_TO_STATUS_ENQUIRY_V01 = 98, 
  MCM_VOICE_CALL_END_CAUSE_NORMAL_UNSPECIFIED_V01 = 99, 
  MCM_VOICE_CALL_END_CAUSE_NO_CIRCUIT_OR_CHANNEL_AVAILABLE_V01 = 100, 
  MCM_VOICE_CALL_END_CAUSE_NETWORK_OUT_OF_ORDER_V01 = 101, 
  MCM_VOICE_CALL_END_CAUSE_TEMPORARY_FAILURE_V01 = 102, 
  MCM_VOICE_CALL_END_CAUSE_SWITCHING_EQUIPMENT_CONGESTION_V01 = 103, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_INFORMATION_DISCARDED_V01 = 104, 
  MCM_VOICE_CALL_END_CAUSE_REQUESTED_CIRCUIT_OR_CHANNEL_NOT_AVAILABLE_V01 = 105, 
  MCM_VOICE_CALL_END_CAUSE_RESOURCES_UNAVAILABLE_OR_UNSPECIFIED_V01 = 106, 
  MCM_VOICE_CALL_END_CAUSE_QOS_UNAVAILABLE_V01 = 107, 
  MCM_VOICE_CALL_END_CAUSE_REQUESTED_FACILITY_NOT_SUBSCRIBED_V01 = 108, 
  MCM_VOICE_CALL_END_CAUSE_INCOMING_CALLS_BARRED_WITHIN_CUG_V01 = 109, 
  MCM_VOICE_CALL_END_CAUSE_BEARER_CAPABILITY_NOT_AUTH_V01 = 110, 
  MCM_VOICE_CALL_END_CAUSE_BEARER_CAPABILITY_UNAVAILABLE_V01 = 111, 
  MCM_VOICE_CALL_END_CAUSE_SERVICE_OPTION_NOT_AVAILABLE_V01 = 112, 
  MCM_VOICE_CALL_END_CAUSE_ACM_LIMIT_EXCEEDED_V01 = 113, 
  MCM_VOICE_CALL_END_CAUSE_BEARER_SERVICE_NOT_IMPLEMENTED_V01 = 114, 
  MCM_VOICE_CALL_END_CAUSE_REQUESTED_FACILITY_NOT_IMPLEMENTED_V01 = 115, 
  MCM_VOICE_CALL_END_CAUSE_ONLY_DIGITAL_INFORMATION_BEARER_AVAILABLE_V01 = 116, 
  MCM_VOICE_CALL_END_CAUSE_SERVICE_OR_OPTION_NOT_IMPLEMENTED_V01 = 117, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_TRANSACTION_IDENTIFIER_V01 = 118, 
  MCM_VOICE_CALL_END_CAUSE_USER_NOT_MEMBER_OF_CUG_V01 = 119, 
  MCM_VOICE_CALL_END_CAUSE_INCOMPATIBLE_DESTINATION_V01 = 120, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_TRANSIT_NW_SELECTION_V01 = 121, 
  MCM_VOICE_CALL_END_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE_V01 = 122, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_MANDATORY_INFORMATION_V01 = 123, 
  MCM_VOICE_CALL_END_CAUSE_MESSAGE_TYPE_NON_IMPLEMENTED_V01 = 124, 
  MCM_VOICE_CALL_END_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE_V01 = 125, 
  MCM_VOICE_CALL_END_CAUSE_INFORMATION_ELEMENT_NON_EXISTENT_V01 = 126, 
  MCM_VOICE_CALL_END_CAUSE_CONDITONAL_IE_ERROR_V01 = 127, 
  MCM_VOICE_CALL_END_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROTOCOL_STATE_V01 = 128, 
  MCM_VOICE_CALL_END_CAUSE_RECOVERY_ON_TIMER_EXPIRED_V01 = 129, 
  MCM_VOICE_CALL_END_CAUSE_PROTOCOL_ERROR_UNSPECIFIED_V01 = 130, 
  MCM_VOICE_CALL_END_CAUSE_INTERWORKING_UNSPECIFIED_V01 = 131, 
  MCM_VOICE_CALL_END_CAUSE_OUTGOING_CALLS_BARRED_WITHIN_CUG_V01 = 132, 
  MCM_VOICE_CALL_END_CAUSE_NO_CUG_SELECTION_V01 = 133, 
  MCM_VOICE_CALL_END_CAUSE_UNKNOWN_CUG_INDEX_V01 = 134, 
  MCM_VOICE_CALL_END_CAUSE_CUG_INDEX_INCOMPATIBLE_V01 = 135, 
  MCM_VOICE_CALL_END_CAUSE_CUG_CALL_FAILURE_UNSPECIFIED_V01 = 136, 
  MCM_VOICE_CALL_END_CAUSE_CLIR_NOT_SUBSCRIBED_V01 = 137, 
  MCM_VOICE_CALL_END_CAUSE_CCBS_POSSIBLE_V01 = 138, 
  MCM_VOICE_CALL_END_CAUSE_CCBS_NOT_POSSIBLE_V01 = 139, 
  MCM_VOICE_CALL_END_CAUSE_IMSI_UNKNOWN_IN_HLR_V01 = 140, 
  MCM_VOICE_CALL_END_CAUSE_ILLEGAL_MS_V01 = 141, 
  MCM_VOICE_CALL_END_CAUSE_IMSI_UNKNOWN_IN_VLR_V01 = 142, 
  MCM_VOICE_CALL_END_CAUSE_IMEI_NOT_ACCEPTED_V01 = 143, 
  MCM_VOICE_CALL_END_CAUSE_ILLEGAL_ME_V01 = 144, 
  MCM_VOICE_CALL_END_CAUSE_PLMN_NOT_ALLOWED_V01 = 145, 
  MCM_VOICE_CALL_END_CAUSE_LOCATION_AREA_NOT_ALLOWED_V01 = 146, 
  MCM_VOICE_CALL_END_CAUSE_ROAMING_NOT_ALLOWED_IN_THIS_LOCATION_AREA_V01 = 147, 
  MCM_VOICE_CALL_END_CAUSE_NO_SUITABLE_CELLS_IN_LOCATION_AREA_V01 = 148, 
  MCM_VOICE_CALL_END_CAUSE_NETWORK_FAILURE_V01 = 149, 
  MCM_VOICE_CALL_END_CAUSE_MAC_FAILURE_V01 = 150, 
  MCM_VOICE_CALL_END_CAUSE_SYNCH_FAILURE_V01 = 151, 
  MCM_VOICE_CALL_END_CAUSE_NETWORK_CONGESTION_V01 = 152, 
  MCM_VOICE_CALL_END_CAUSE_GSM_AUTHENTICATION_UNACCEPTABLE_V01 = 153, 
  MCM_VOICE_CALL_END_CAUSE_SERVICE_NOT_SUBSCRIBED_V01 = 154, 
  MCM_VOICE_CALL_END_CAUSE_SERVICE_TEMPORARILY_OUT_OF_ORDER_V01 = 155, 
  MCM_VOICE_CALL_END_CAUSE_CALL_CANNOT_BE_IDENTIFIED_V01 = 156, 
  MCM_VOICE_CALL_END_CAUSE_INCORRECT_SEMANTICS_IN_MESSAGE_V01 = 157, 
  MCM_VOICE_CALL_END_CAUSE_MANDATORY_INFORMATION_INVALID_V01 = 158, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_FAILURE_V01 = 159, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_SIM_V01 = 160, 
  MCM_VOICE_CALL_END_CAUSE_WRONG_STATE_V01 = 161, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_CLASS_BLOCKED_V01 = 162, 
  MCM_VOICE_CALL_END_CAUSE_NO_RESOURCES_V01 = 163, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_USER_DATA_V01 = 164, 
  MCM_VOICE_CALL_END_CAUSE_TIMER_T3230_EXPIRED_V01 = 165, 
  MCM_VOICE_CALL_END_CAUSE_NO_CELL_AVAILABLE_V01 = 166, 
  MCM_VOICE_CALL_END_CAUSE_ABORT_MSG_RECEIVED_V01 = 167, 
  MCM_VOICE_CALL_END_CAUSE_RADIO_LINK_LOST_V01 = 168, 
  MCM_VOICE_CALL_END_CAUSE_TIMER_T303_EXPIRED_V01 = 169, 
  MCM_VOICE_CALL_END_CAUSE_CNM_MM_REL_PENDING_V01 = 170, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_RR_REL_IND_V01 = 171, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_RR_RANDOM_ACCESS_FAILURE_V01 = 172, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_RRC_REL_IND_V01 = 173, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_RRC_CLOSE_SESSION_IND_V01 = 174, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_RRC_OPEN_SESSION_FAILURE_V01 = 175, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_LOW_LEVEL_FAIL_V01 = 176, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_LOW_LEVEL_FAIL_REDIAL_NOT_ALLOWED_V01 = 177, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_LOW_LEVEL_IMMED_RETRY_V01 = 178, 
  MCM_VOICE_CALL_END_CAUSE_ACCESS_STRATUM_REJ_ABORT_RADIO_UNAVAILABLE_V01 = 179, 
  MCM_VOICE_CALL_END_CAUSE_SERVICE_OPTION_NOT_SUPPORTED_V01 = 180, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_UL_DATA_CNF_FAILURE_TXN_V01 = 181, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_UL_DATA_CNF_FAILURE_HO_V01 = 182, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_UL_DATA_CNF_FAILURE_CONN_REL_V01 = 183, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_UL_DATA_CNF_FAILURE_RLF_V01 = 184, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_UL_DATA_CNF_FAILURE_CTRL_NOT_CONN_V01 = 185, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_SUCCESS_V01 = 186, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_V01 = 187, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_ABORTED_V01 = 188, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_ACCESS_BARRED_V01 = 189, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_CELL_RESEL_V01 = 190, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_CONFIG_FAILURE_V01 = 191, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_TIMER_EXPIRED_V01 = 192, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_LINK_FAILURE_V01 = 193, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_NOT_CAMPED_V01 = 194, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_SI_FAILURE_V01 = 195, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_EST_FAILURE_CONN_REJECT_V01 = 196, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_NORMAL_V01 = 197, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_RLF_V01 = 198, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_CRE_FAILURE_V01 = 199, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_OOS_DURING_CRE_V01 = 200, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_ABORTED_V01 = 201, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_SIB_READ_ERROR_V01 = 202, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_CONN_REL_ABORTED_IRAT_SUCCESS_V01 = 203, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_LRRC_RADIO_LINK_FAILURE_V01 = 204, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_DETACH_WITH_REATTACH_LTE_NW_DETACH_V01 = 205, 
  MCM_VOICE_CALL_END_CAUSE_AS_REJ_DETACH_WITH_OUT_REATTACH_LTE_NW_DETACH_V01 = 206, 
  MCM_VOICE_CALL_END_CAUSE_BAD_REQ_WAIT_INVITE_V01 = 207, 
  MCM_VOICE_CALL_END_CAUSE_BAD_REQ_WAIT_REINVITE_V01 = 208, 
  MCM_VOICE_CALL_END_CAUSE_INVALID_REMOTE_URI_V01 = 209, 
  MCM_VOICE_CALL_END_CAUSE_REMOTE_UNSUPP_MEDIA_TYPE_V01 = 210, 
  MCM_VOICE_CALL_END_CAUSE_PEER_NOT_REACHABLE_V01 = 211, 
  MCM_VOICE_CALL_END_CAUSE_NETWORK_NO_RESP_TIME_OUT_V01 = 212, 
  MCM_VOICE_CALL_END_CAUSE_NETWORK_NO_RESP_HOLD_FAIL_V01 = 213, 
  MCM_VOICE_CALL_END_CAUSE_DATA_CONNECTION_LOST_V01 = 214, 
  MCM_VOICE_CALL_END_CAUSE_UPGRADE_DOWNGRADE_REJ_V01 = 215, 
  MCM_VOICE_CALL_END_CAUSE_SIP_403_FORBIDDEN_V01 = 216, 
  MCM_VOICE_CALL_END_CAUSE_NO_NETWORK_RESP_V01 = 217, 
  MCM_VOICE_CALL_END_CAUSE_UPGRADE_DOWNGRADE_FAILED_V01 = 218, 
  MCM_VOICE_CALL_END_CAUSE_UPGRADE_DOWNGRADE_CANCELLED_V01 = 219, 
  MCM_VOICE_CALL_END_CAUSE_SSAC_REJECT_V01 = 220, 
  MCM_VOICE_CALL_END_CAUSE_THERMAL_EMERGENCY_V01 = 221, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_SOFT_FAILURE_V01 = 222, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_HARD_FAILURE_V01 = 223, 
  MCM_VOICE_CALL_END_CAUSE_CONNECTION_EST_FAILURE_V01 = 224, 
  MCM_VOICE_CALL_END_CAUSE_CONNECTION_FAILURE_V01 = 225, 
  MCM_VOICE_CALL_END_CAUSE_RRC_CONN_REL_NO_MT_SETUP_V01 = 226, 
  MCM_VOICE_CALL_END_CAUSE_ESR_FAILURE_V01 = 227, 
  MCM_VOICE_CALL_END_CAUSE_MT_CSFB_NO_RESPONSE_FROM_NW_V01 = 228, 
  MCM_VOICE_CALL_END_CAUSE_BUSY_EVERYWHERE_V01 = 229, 
  MCM_VOICE_CALL_END_CAUSE_ANSWERED_ELSEWHERE_V01 = 230, 
  MCM_VOICE_CALL_END_CAUSE_RLF_DURING_CC_DISCONNECT_V01 = 231, 
  MCM_VOICE_CALL_END_CAUSE_TEMP_REDIAL_ALLOWED_V01 = 232, 
  MCM_VOICE_CALL_END_CAUSE_PERM_REDIAL_NOT_NEEDED_V01 = 233, 
  MCM_VOICE_CALL_END_CAUSE_MERGED_TO_CONFERENCE_V01 = 234, 
  MCM_VOICE_CALL_END_CAUSE_LOW_BATTERY_V01 = 235, 
  MCM_VOICE_CALL_END_CAUSE_CALL_DEFLECTED_V01 = 236, 
  MCM_VOICE_CALL_END_CAUSE_RTP_RTCP_TIMEOUT_V01 = 237, 
  MCM_VOICE_CALL_END_CAUSE_RINGING_RINGBACK_TIMEOUT_V01 = 238, 
  MCM_VOICE_CALL_END_CAUSE_REG_RESTORATION_V01 = 239, 
  MCM_VOICE_CALL_END_CAUSE_CODEC_ERROR_V01 = 240, 
  MCM_VOICE_CALL_END_CAUSE_UNSUPPORTED_SDP_V01 = 241, 
  MCM_VOICE_CALL_END_CAUSE_RTP_FAILURE_V01 = 242, 
  MCM_VOICE_CALL_END_CAUSE_QoS_FAILURE_V01 = 243, 
  MCM_VOICE_CALL_END_CAUSE_MULTIPLE_CHOICES_V01 = 244, 
  MCM_VOICE_CALL_END_CAUSE_MOVED_PERMANENTLY_V01 = 245, 
  MCM_VOICE_CALL_END_CAUSE_MOVED_TEMPORARILY_V01 = 246, 
  MCM_VOICE_CALL_END_CAUSE_USE_PROXY_V01 = 247, 
  MCM_VOICE_CALL_END_CAUSE_ALTERNATE_SERVICE_V01 = 248, 
  MCM_VOICE_CALL_END_CAUSE_ALTERNATE_EMERGENCY_CALL_V01 = 249, 
  MCM_VOICE_CALL_END_CAUSE_UNAUTHORIZED_V01 = 250, 
  MCM_VOICE_CALL_END_CAUSE_PAYMENT_REQUIRED_V01 = 251, 
  MCM_VOICE_CALL_END_CAUSE_METHOD_NOT_ALLOWED_V01 = 252, 
  MCM_VOICE_CALL_END_CAUSE_NOT_ACCEPTABLE_V01 = 253, 
  MCM_VOICE_CALL_END_CAUSE_PROXY_AUTHENTICATION_REQUIRED_V01 = 254, 
  MCM_VOICE_CALL_END_CAUSE_GONE_V01 = 255, 
  MCM_VOICE_CALL_END_CAUSE_REQUEST_ENTITY_TOO_LARGE_V01 = 256, 
  MCM_VOICE_CALL_END_CAUSE_REQUEST_URI_TOO_LARGE_V01 = 257, 
  MCM_VOICE_CALL_END_CAUSE_UNSUPPORTED_URI_SCHEME_V01 = 258, 
  MCM_VOICE_CALL_END_CAUSE_BAD_EXTENSION_V01 = 259, 
  MCM_VOICE_CALL_END_CAUSE_EXTENSION_REQUIRED_V01 = 260, 
  MCM_VOICE_CALL_END_CAUSE_INTERVAL_TOO_BRIEF_V01 = 261, 
  MCM_VOICE_CALL_END_CAUSE_CALL_OR_TRANS_DOES_NOT_EXIST_V01 = 262, 
  MCM_VOICE_CALL_END_CAUSE_LOOP_DETECTED_V01 = 263, 
  MCM_VOICE_CALL_END_CAUSE_TOO_MANY_HOPS_V01 = 264, 
  MCM_VOICE_CALL_END_CAUSE_ADDRESS_INCOMPLETE_V01 = 265, 
  MCM_VOICE_CALL_END_CAUSE_AMBIGUOUS_V01 = 266, 
  MCM_VOICE_CALL_END_CAUSE_REQUEST_TERMINATED_V01 = 267, 
  MCM_VOICE_CALL_END_CAUSE_NOT_ACCEPTABLE_HERE_V01 = 268, 
  MCM_VOICE_CALL_END_CAUSE_REQUEST_PENDING_V01 = 269, 
  MCM_VOICE_CALL_END_CAUSE_UNDECIPHERABLE_V01 = 270, 
  MCM_VOICE_CALL_END_CAUSE_SERVER_INTERNAL_ERROR_V01 = 271, 
  MCM_VOICE_CALL_END_CAUSE_NOT_IMPLEMENTED_V01 = 272, 
  MCM_VOICE_CALL_END_CAUSE_BAD_GATEWAY_V01 = 273, 
  MCM_VOICE_CALL_END_CAUSE_SERVER_TIME_OUT_V01 = 274, 
  MCM_VOICE_CALL_END_CAUSE_VERSION_NOT_SUPPORTED_V01 = 275, 
  MCM_VOICE_CALL_END_CAUSE_MESSAGE_TOO_LARGE_V01 = 276, 
  MCM_VOICE_CALL_END_CAUSE_DOES_NOT_EXIST_ANYWHERE_V01 = 277, 
  MCM_VOICE_CALL_END_CAUSE_SESS_DESCR_NOT_ACCEPTABLE_V01 = 278, 
  MCM_VOICE_CALL_END_CAUSE_SRVCC_END_CALL_V01 = 279, 
  MCM_VOICE_CALL_END_CAUSE_INTERNAL_ERROR_V01 = 280, 
  MCM_VOICE_CALL_END_CAUSE_SERVER_UNAVAILABLE_V01 = 281, 
  MCM_VOICE_CALL_END_CAUSE_PRECONDITION_FAILURE_V01 = 282, 
  MCM_VOICE_CALL_END_CAUSE_DRVCC_IN_PROG_V01 = 283, 
  MCM_VOICE_CALL_END_CAUSE_DRVCC_END_CALL_V01 = 284, 
  MCM_VOICE_CALL_END_CAUSE_CS_HARD_FAILURE_V01 = 285, 
  MCM_VOICE_CALL_END_CAUSE_CS_ACQ_FAILURE_V01 = 286, 
  MCM_VOICE_CALL_END_CAUSE_FALLBACK_TO_CS_V01 = 287, 
  MCM_VOICE_CALL_END_CAUSE_DEAD_BATTERY_V01 = 288, 
  MCM_VOICE_CALL_END_CAUSE_HO_NOT_FEASIBLE_V01 = 289, 
  MCM_VOICE_CALL_END_CAUSE_PDN_DISCONNECTED_V01 = 290, 
  MCM_VOICE_CALL_END_CAUSE_REJECTED_ELSEWHERE_V01 = 291, 
  MCM_VOICE_CALL_END_CAUSE_CALL_PULLED_V01 = 292, 
  MCM_VOICE_CALL_END_CAUSE_CALL_PULL_OUT_OF_SYNC_V01 = 293, 
  MCM_VOICE_CALL_END_CAUSE_HOLD_RESUME_FAILED_V01 = 294, 
  MCM_VOICE_CALL_END_CAUSE_HOLD_RESUME_CANCELED_V01 = 295, 
  MCM_VOICE_CALL_END_CAUSE_REINVITE_COLLISION_V01 = 296, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_MSG_INVAILD_V01 = 297, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_MSG_IGNORE_V01 = 298, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_ACQ_FAIL_V01 = 299, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_CALL_REL_REL_ORDER_V01 = 300, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_CALL_REL_REORDER_V01 = 301, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_CALL_REL_INTERCEPT_ORDER_V01 = 302, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_CALL_REL_NORMAL_V01 = 303, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_CALL_REL_SO_REJ_V01 = 304, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAIL_CALL_REL_OTASP_SPC_ERR_V01 = 305, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAILURE_SRCH_TT_FAIL_V01 = 306, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAILURE_TCH_INIT_FAIL_V01 = 307, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAILURE_FAILURE_USER_CALL_END_V01 = 308, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAILURE_FAILURE_RETRY_EXHAUST_V01 = 309, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAILURE_FAILURE_CALL_REL_REG_REJ_V01 = 310, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_FAILURE_FAILURE_CALL_REL_NW_REL_ODR_V01 = 311, 
  MCM_VOICE_CALL_END_CAUSE_1XCSFB_HO_FAILURE_V01 = 312, 
  MCM_VOICE_CALL_END_CAUSE_EMM_REJ_TIMER_T3417_EXT_EXP_V01 = 313, 
  MCM_VOICE_CALL_END_CAUSE_EMM_REJ_TIMER_T3417_EXP_V01 = 314, 
  MCM_VOICE_CALL_END_CAUSE_EMM_REJ_SERVICE_REQ_FAILURE_LTE_NW_REJECT_V01 = 315, 
  MCM_VOICE_CALL_END_CAUSE_EMM_REJ_SERVICE_REQ_FAILURE_CS_DOMAIN_NOT_AVAILABLE_V01 = 316, 
  MCM_VOICE_CALL_END_CAUSE_EMM_REJ_V01 = 317, 
  MCM_VOICE_CALL_END_REASON_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_call_end_reason_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t call_id;
  /**<   Call ID associated with this call.*/

  mcm_voice_call_state_t_v01 state;
  /**<   Current call state (mcm_voice_call_state).*/

  mcm_voice_tech_t_v01 tech;
  /**<   Technology (mcm_tech).*/

  char number[MCM_MAX_PHONE_NUMBER_V01 + 1];
  /**<   Phone number.*/

  mcm_voice_call_number_presentation_type_t_v01 number_presentation;
  /**<   Number presentation.*/

  mcm_voice_call_direction_type_t_v01 direction;
  /**<   Voice call direction.*/

  uint8_t uusdata_valid;
  /**<   Indicates whether UUS data is valid.*/

  mcm_voice_uusdata_t_v01 uusdata;
  /**<   User-to-user signaling data.*/

  uint8_t call_end_reason_valid;
  /**<   Indicates whether call_end_reason is valid.*/

  mcm_voice_call_end_reason_t_v01 call_end_reason;

  uint8_t type;
}mcm_voice_call_record_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  uint32_t call_id;
  /**<   Call ID associated with this DTMF event.*/

  mcm_voice_dtmf_event_type_t_v01 dtmf_event;
  /**<   DTMF event type.*/

  uint32_t digit_len;  /**< Must be set to # of elements in digit */
  char digit[MCM_MAX_DTMF_LENGTH_V01];
  /**<   DTMF character.*/
}mcm_voice_dtmf_info_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  mcm_voice_call_forwarding_type_t_v01 type;
  /**<   Call forwarding type.*/

  char number[MCM_MAX_PHONE_NUMBER_V01 + 1];
  /**<   Call forwarding number.*/
}mcm_voice_call_forwarding_info_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_ECALL_MSD_TRANSMISSION_STATUS_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_MSD_TRANSMISSION_STATUS_SUCCESS_V01 = 0x00, /**<   Success \n   */
  MCM_VOICE_ECALL_MSD_TRANSMISSION_STATUS_FAILURE_V01 = 0x01, /**<   Generic failure   */
  MCM_ECALL_MSD_TRANSMISSION_STATUS_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_ecall_msd_transmission_status_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_COMMAND_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_COMMAND_PUSH_V01 = 0, /**<  IVS PUSH command */
  MCM_VOICE_ECALL_COMMAND_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_command_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_STATE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_INACTIVE_V01 = 0, 
  MCM_VOICE_ECALL_ORIGINATING_CALL_V01 = 1, 
  MCM_VOICE_ECALL_IN_CALL_TRANSMITTING_V01 = 2, /**<  ECALL APP TRANSMITTING */
  MCM_VOICE_ECALL_WATING_FOR_AL_ACK_V01 = 3, 
  MCM_VOICE_ECALL_IN_CALL_V01 = 4, 
  MCM_VOICE_ECALL_IDLE_ALLOW_MT_ECALL_V01 = 5, 
  MCM_VOICE_ECALL_STATE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_state_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_MODE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_MODE_NOMAL_V01 = 0, 
  MCM_VOICE_ECALL_MODE_ONLY_V01 = 1, 
  MCM_VOICE_ECALL_MODE_DEFAULT_V01 = 2, /**<  ECALL APP TRANSMITTING */
  MCM_VOICE_ECALL_MODE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_mode_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t enable;
  /**<   Enable or disable ecall. 
 0 -- Disable; 1 -- Enable.*/

  uint8_t voiceconfig;
  /**<   0 -- Disable to mute IVS speaker automatical in MSD transmission.
 1 -- Enable to mute IVS speaker automatical in MSD transmission.*/

  /*  Enable or disable to mute IVS speaker in MSD. */
  mcm_voice_ecall_mode_t_v01 ecallmode;
  /**<   The Ecall mode.*/

  uint8_t processinfo;
  /**<   Enable or disable to report ecall event info.
 0 -- Disable; 1 -- Enable*/

  uint16_t T5;
  /**<   The timer of IVS waiting for "START".*/

  uint16_t T6;
  /**<   The timer of IVS waiting for "HACK".*/

  uint16_t T7;
  /**<   The timer of MSD transmission.*/

  uint8_t mofailredial;
  /**<   The dial fail times.*/

  uint8_t dropredial;
  /**<   The ecall abnormal disconnenct redial times.*/
}mcm_voice_ecall_config_info_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_EVENT_FAIL_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_EVENT_FAIL_START_TIMEOUT_V01 = 1, /**<  Wait for START timeout. */
  MCM_VOICE_ECALL_EVENT_FAIL_HACK_TIMEOUT_V01 = 2, /**<  Wait for HACK timeout.	 */
  MCM_VOICE_ECALL_EVENT_FAIL_MSD_TRANSMISSION_TIMEOUT_V01 = 3, /**<  MSD transmission timeout.	 */
  MCM_VOICE_ECALL_EVENT_FAIL_IVS_RESET_TIMEOUT_V01 = 4, /**<  IVS reset. */
  MCM_VOICE_ECALL_EVENT_FAIL_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_event_fail_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_EVENT_PROCESS_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_EVENT_PROCESS_IVS_START_RECEIVED_MSD_V01 = 1, /**<  IVS Link Layer receives START message and starts to send MSD */
  MCM_VOICE_ECALL_EVENT_PROCESS_IVS_NACK_RECEIVED_V01 = 2, /**<  IVS Link Layer receives NACK message. */
  MCM_VOICE_ECALL_EVENT_PROCESS_IVS_ACK_RECEIVED_V01 = 3, /**<  IVS Link Layer receives the first LACK message. */
  MCM_VOICE_ECALL_EVENT_PROCESS_IVS_TX_COMPLETED_V01 = 4, /**<  IVS MSD transmission is complete. */
  MCM_VOICE_ECALL_EVENT_PROCESS_IVS_HLACK_RECEIVED_V01 = 5, /**<  IVS Link Layer receives first HACK message. */
  MCM_VOICE_ECALL_EVENT_PROCESS_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_event_process_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_EVENT_MSDUPADTE_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_EVENT_MSDUPDATE_IVS_UPDATING_MSD_V01 = 0, /**<  Indicates MSD has been updated. */
  MCM_VOICE_ECALL_EVENT_MSDUPDATE_PSAP_REQURE_UPDATE_MSD_V01 = 1, /**<  Indicate to update MSD in 5 seconds. */
  MCM_VOICE_ECALL_EVENT_MSDUPDATE_IVS_UPDATE_MSD_TIMEOUT_V01 = 2, /**<  Indicate timeout of updating MSD and module starts to transfer the old MSD. */
  MCM_VOICE_ECALL_EVENT_MSDUPADTE_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_event_msdupadte_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_enums
    @{
  */
typedef enum {
  MCM_VOICE_ECALL_EVENT_ESTABLISH_T_MIN_ENUM_VAL_V01 = -2147483647, /**< To force a 32 bit signed enum.  Do not change or use*/
  MCM_VOICE_ECALL_EVENT_ECALL_ESTABLISHNG_SUCCESS_V01 = 0, /**<  Establish eCall successfully. */
  MCM_VOICE_ECALL_EVENT_ECALL_ESTABLISHNG_FAIL_V01 = 1, /**<  Establish eCall fails. */
  MCM_VOICE_ECALL_EVENT_ESTABLISH_T_MAX_ENUM_VAL_V01 = 2147483647 /**< To force a 32 bit signed enum.  Do not change or use*/
}mcm_voice_ecall_event_establish_t_v01;
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  uint16_t hack_code;
  /**<   psap hack code.*/
}mcm_voice_ecall_event_hackcode_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t ori_remainder_times;
  /**<   originate fail remainder times*/

  uint16_t time;
  /**<   the minimum time duration between the previous call attempt*/
}mcm_voice_ecall_event_originate_fail_and_redial_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_aggregates
    @{
  */
typedef struct {

  uint8_t drop_remainder_times;
  /**<   dorp remainder times*/

  uint16_t time;
  /**<   the minimum time duration between the previous call attempt*/
}mcm_voice_ecall_event_drop_and_redial_t_v01;  /* Type */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Gets the list of current calls. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_get_calls_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Gets the list of current calls. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Optional */
  uint8_t calls_valid;  /**< Must be set to true if calls is being passed */
  uint32_t calls_len;  /**< Must be set to # of elements in calls */
  mcm_voice_call_record_t_v01 calls[MCM_MAX_VOICE_CALLS_V01];
  /**<   Calls.*/
}mcm_voice_get_calls_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Dials a call to a specified address and returns a connection ID. */
typedef struct {

  /* Optional */
  uint8_t address_valid;  /**< Must be set to true if address is being passed */
  char address[MCM_MAX_PHONE_NUMBER_V01 + 1];
  /**<   End point address of the connection to make.*/

  /* Optional */
  uint8_t call_type_valid;  /**< Must be set to true if call_type is being passed */
  mcm_voice_call_type_t_v01 call_type;
  /**<   Connection (call) details, or NULL.*/

  /* Optional */
  uint8_t uusdata_valid;  /**< Must be set to true if uusdata is being passed */
  mcm_voice_uusdata_t_v01 uusdata;
  /**<   Token ID used to track this command; NULL is OK.*/

  /* Optional */
  uint8_t emergency_cat_valid;  /**< Must be set to true if emergency_cat is being passed */
  mcm_voice_emergency_cat_t_v01 emergency_cat;
  /**<   Emergency call category.*/

  /* Optional */
  uint8_t ecall_msd_valid;  /**< Must be set to true if ecall_msd is being passed */
  uint32_t ecall_msd_len;  /**< Must be set to # of elements in ecall_msd */
  uint8_t ecall_msd[MCM_MAX_ECALL_MSD_V01];
  /**<  Minimum Set of Data in ASN.1 PER unaligned format
 as per CEN EN 15722. Only honored when
 call_type is MCM_VOICE_CALL_TYPE_ECALL_AUTO or
 MCM_VOICE_CALL_TYPE_ECALL_MANUAL. Ignored otherwise.*/

  /* Optional */
  uint8_t ecall_variant_valid;  /**< Must be set to true if ecall_variant is being passed */
  mcm_ecall_variant_t_v01 ecall_variant;
  /**<     eCall variant. Values: \n
        - ECALL_TEST (0x01)      --  Test eCall \n 
        - ECALL_EMERGENCY (0x02) --  Emergency eCall \n 
        - ECALL_RECONFIG (0x03)  --  Reconfig eCall */
}mcm_voice_dial_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Dials a call to a specified address and returns a connection ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Optional */
  uint8_t call_id_valid;  /**< Must be set to true if call_id is being passed */
  uint32_t call_id;
  /**<  Call ID.*/
}mcm_voice_dial_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Gets the status associated with the connection ID. */
typedef struct {

  /* Mandatory */
  uint32_t call_id;
  /**<   Call ID of the connection to query.*/
}mcm_voice_get_call_status_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Gets the status associated with the connection ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Optional */
  uint8_t status_valid;  /**< Must be set to true if status is being passed */
  mcm_voice_call_record_t_v01 status;
  /**<   Call status.*/
}mcm_voice_get_call_status_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Sends a DTMF character over the connection ID. */
typedef struct {

  /* Mandatory */
  char dtmf[MCM_MAX_DTMF_LENGTH_V01 + 1];
  /**<   DTMF character to be sent.
                           Valid DTMF characters are 0-9, A-D, '*', '#'.*/
}mcm_voice_dtmf_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Sends a DTMF character over the connection ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code. @newpagetable*/
}mcm_voice_dtmf_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Starts sending a DTMF character over the call ID. */
typedef struct {

  /* Mandatory */
  uint32_t call_id;
  /**<  Call ID.*/

  /* Mandatory */
  char digit;
  /**<   DTMF character to be sent.
                           Valid DTMF characters are 0-9, A-D, '*', '#'.*/
}mcm_voice_start_dtmf_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Starts sending a DTMF character over the call ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Optional */
  uint8_t call_id_valid;  /**< Must be set to true if call_id is being passed */
  uint32_t call_id;
  /**<   Call ID.*/
}mcm_voice_start_dtmf_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Stops sending a DTMF character over the call ID. */
typedef struct {

  /* Mandatory */
  uint32_t call_id;
  /**<   Call ID.*/
}mcm_voice_stop_dtmf_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Stops sending a DTMF character over the call ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Optional */
  uint8_t call_id_valid;  /**< Must be set to true if call_id is being passed */
  uint32_t call_id;
  /**<   Call ID.*/
}mcm_voice_stop_dtmf_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Mutes/unmutes a voice call. */
typedef struct {

  /* Mandatory */
  uint32_t call_id;
  /**<   Call ID of the connection to mute/unmute.*/

  /* Mandatory */
  mcm_voice_mute_type_t_v01 mute_type;
  /**<   Mute or unmute the voice call.*/
}mcm_voice_mute_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Mutes/unmutes a voice call. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_mute_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Sends a flash sequence character over the connection call ID. */
typedef struct {

  /* Mandatory */
  char sflash_string[MCM_MAX_PHONE_NUMBER_V01 + 1];
  /**<   A NULL-terminated flash string to be sent;
 Maximum 82 characters.*/
}mcm_voice_flash_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Sends a flash sequence character over the connection call ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
}mcm_voice_flash_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Hangs up or disconnects a voice call connection with the specified call ID. */
typedef struct {

  /* Mandatory */
  uint32_t call_id;
  /**<   Call ID associated with the connection.*/
}mcm_voice_hangup_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Hangs up or disconnects a voice call connection with the specified call ID. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_hangup_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Provides various operations for a voice call. */
typedef struct {

  /* Mandatory */
  mcm_voice_call_operation_t_v01 call_operation;
  /**<   Call operation.*/

  /* Optional */
  uint8_t call_id_valid;  /**< Must be set to true if call_id is being passed */
  uint32_t call_id;
  /**<   Call ID.*/

  /* Optional */
  uint8_t cause_valid;  /**< Must be set to true if cause is being passed */
  uint32_t cause;
  /**<   Cause.*/
}mcm_voice_command_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Provides various operations for a voice call. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_command_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Enables/disables an incoming voice call. */
typedef struct {

  /* Mandatory */
  mcm_voice_auto_answer_type_t_v01 auto_answer_type;
  /**<   Auto-answer type.*/

  /* Optional */
  uint8_t anto_answer_timer_valid;  /**< Must be set to true if anto_answer_timer is being passed */
  uint32_t anto_answer_timer;
  /**<   Auto-answer timer.*/
}mcm_voice_auto_answer_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Enables/disables an incoming voice call. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_auto_answer_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Registers for an indication of events. */
typedef struct {

  /* Optional */
  uint8_t register_voice_call_event_valid;  /**< Must be set to true if register_voice_call_event is being passed */
  uint8_t register_voice_call_event;
  /**<   MCM_VOICE_CALL_INDICATION*/

  /* Optional */
  uint8_t register_mute_event_valid;  /**< Must be set to true if register_mute_event is being passed */
  uint8_t register_mute_event;
  /**<   MCM_VOICE_MUTE_INDICATION*/

  /* Optional */
  uint8_t register_dtmf_event_valid;  /**< Must be set to true if register_dtmf_event is being passed */
  uint8_t register_dtmf_event;
  /**<   MCM_VOICE_DTMF_INDICATION*/

  /* Optional */
  uint8_t register_e911_state_event_valid;  /**< Must be set to true if register_e911_state_event is being passed */
  uint8_t register_e911_state_event;
  /**<   MCM_VOICE_E911_STATE_INDICATION*/

  /* Optional */
  uint8_t register_ecall_status_event_valid;  /**< Must be set to true if register_ecall_status_event is being passed */
  uint8_t register_ecall_status_event;
  /**<   MCM_VOICE_ECALL_STATUE_INDICATION*/

  /* Optional */
  uint8_t register_ecall_urc_event_valid;  /**< Must be set to true if register_ecall_urc_event is being passed */
  uint8_t register_ecall_urc_event;
  /**<   MCM_VOICE_ECALL_URC_INDICATION*/

  /* Optional */
  uint8_t register_ecall_event_valid;  /**< Must be set to true if register_ecall_event is being passed */
  uint8_t register_ecall_event;
  /**<   MCM_VOICE_ECALL_EVENT_INDICATION*/
}mcm_voice_event_register_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Registers for an indication of events. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_event_register_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Indication Message; Indication for MCM_VOICE_CONNECTION_EV. */
typedef struct {

  /* Mandatory */
  uint32_t calls_len;  /**< Must be set to # of elements in calls */
  mcm_voice_call_record_t_v01 calls[MCM_MAX_VOICE_CALLS_V01];
  /**<   Calls.*/
}mcm_voice_call_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Indication Message; Indication for MCM_VOICE_MUTE_EV. */
typedef struct {

  /* Mandatory */
  uint8_t is_mute;
  /**<   Indicates whether a call is muted.*/
}mcm_voice_mute_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Indication Message; Indication for DTMF */
typedef struct {

  /* Mandatory */
  mcm_voice_dtmf_info_t_v01 dtmf_info;
  /**<   DTMF information.*/
}mcm_voice_dtmf_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Call forwarding status query. */
typedef struct {

  /* Mandatory */
  mcm_voice_call_forwarding_reason_t_v01 reason;
  /**<   Call forwarding reason.*/
}mcm_voice_get_call_forwarding_status_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Call forwarding status query. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Mandatory */
  mcm_voice_call_forwarding_status_t_v01 status;
  /**<   Call forwarding status.*/

  /* Optional */
  uint8_t info_valid;  /**< Must be set to true if info is being passed */
  uint32_t info_len;  /**< Must be set to # of elements in info */
  mcm_voice_call_forwarding_info_t_v01 info[MCM_MAX_CALL_FORWARDING_INFO_V01];
  /**<   Call forwarding information.*/
}mcm_voice_get_call_forwarding_status_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Sets call forwarding. */
typedef struct {

  /* Mandatory */
  mcm_voice_call_service_t_v01 fwdservice;
  /**<   Call forwarding service.*/

  /* Mandatory */
  mcm_voice_call_forwarding_reason_t_v01 reason;
  /**<   Call forwarding reason.*/

  /* Optional */
  uint8_t forwarding_number_valid;  /**< Must be set to true if forwarding_number is being passed */
  char forwarding_number[MCM_MAX_PHONE_NUMBER_V01 + 1];
  /**<   Call forwarding number.*/
}mcm_voice_set_call_forwarding_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Sets call forwarding. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<  Result code. @newpagetable*/
}mcm_voice_set_call_forwarding_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Call waiting status query. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_get_call_waiting_status_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Call waiting status query. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Mandatory */
  mcm_voice_call_waiting_service_t_v01 status;
  /**<   Call waiting status.*/
}mcm_voice_get_call_waiting_status_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Sets call waiting. */
typedef struct {

  /* Mandatory */
  mcm_voice_call_waiting_service_t_v01 cwservice;
  /**<   Call waiting service.*/
}mcm_voice_set_call_waiting_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Sets call waiting. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_set_call_waiting_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; CLIR status query. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_get_clir_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; CLIR status query. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Mandatory */
  mcm_voice_clir_action_t_v01 action;

  /* Mandatory */
  mcm_voice_clir_presentation_t_v01 presentation;
  /**<   CLIR presentation.*/
}mcm_voice_get_clir_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Set CLIR. */
typedef struct {

  /* Mandatory */
  mcm_voice_clir_action_t_v01 clir_action;
}mcm_voice_set_clir_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Set CLIR. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
}mcm_voice_set_clir_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Sets a facility lock. */
typedef struct {

  /* Mandatory */
  mcm_voice_facility_code_t_v01 code;
  /**<  Facility code. Refer to 3GPP TS 27.007 @xhyperref{S8,[S8]}, Section 6.4.*/

  /* Mandatory */
  mcm_voice_facility_lock_status_t_v01 status;
  /**<   Facility lock status.*/

  /* Mandatory */
  char password[MCM_MAX_PASSWORD_LENGTH_V01 + 1];
  /**<   Facility lock password.*/
}mcm_voice_set_facility_lock_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Sets a facility lock. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_set_facility_lock_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Changes the call barring password. */
typedef struct {

  /* Mandatory */
  mcm_voice_change_call_barring_password_reason_t_v01 reason;
  /**<  Reason for the password change. Refer to 3GPP TS 27.007 @xhyperref{S8,[S8]}, Section 7.4.*/

  /* Mandatory */
  char old_password[MCM_MAX_PASSWORD_LENGTH_V01 + 1];
  /**<   Old password.*/

  /* Mandatory */
  char new_password[MCM_MAX_PASSWORD_LENGTH_V01 + 1];
  /**<   New password.*/
}mcm_voice_change_call_barring_password_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Changes the call barring password. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_change_call_barring_password_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Sends Unstructured Supplementary Service Data (USSD). */
typedef struct {

  /* Mandatory */
  mcm_voice_ussd_msg_type_t_v01 type;
  /**<   Whether sending a new request or a reply to indication*/

  /* Mandatory */
  mcm_voice_ussd_encoding_t_v01 encoding;
  /**<   USSD encoding.*/

  /* Mandatory */
  char ussd_string[MCM_MAX_USSD_LENGTH_V01 + 1];
  /**<   USSD string.*/
}mcm_voice_send_ussd_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Sends Unstructured Supplementary Service Data (USSD). */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_send_ussd_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Cancels USSD. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_cancel_ussd_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Cancels USSD. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/
}mcm_voice_cancel_ussd_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Indication Message; Receives a USSD indication. */
typedef struct {

  /* Mandatory */
  mcm_voice_ussd_ind_notification_t_v01 notification;

  /* Mandatory */
  char ussd[MCM_MAX_USSD_LENGTH_V01 + 1];
  /**<   USSD indication message.*/
}mcm_voice_receive_ussd_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Voice/SS/USSD common dial API. */
typedef struct {

  /* Mandatory */
  char request[MCM_MAX_PHONE_NUMBER_V01 + 1];

  /* Optional */
  uint8_t call_type_valid;  /**< Must be set to true if call_type is being passed */
  mcm_voice_call_type_t_v01 call_type;
  /**<   Connection (call) details, or NULL,*/

  /* Optional */
  uint8_t uusdata_valid;  /**< Must be set to true if uusdata is being passed */
  mcm_voice_uusdata_t_v01 uusdata;
  /**<   Token ID used to track this command; NULL is OK.*/

  /* Optional */
  uint8_t emergency_cat_valid;  /**< Must be set to true if emergency_cat is being passed */
  mcm_voice_emergency_cat_t_v01 emergency_cat;
  /**<   Emergency call category.*/

  /* Optional */
  uint8_t ecall_msd_valid;  /**< Must be set to true if ecall_msd is being passed */
  uint32_t ecall_msd_len;  /**< Must be set to # of elements in ecall_msd */
  uint8_t ecall_msd[MCM_MAX_ECALL_MSD_V01];
  /**<  Minimum Set of Data in ASN.1 PER unaligned format
 as per CEN EN 15722. Only honored when
 call_type is MCM_VOICE_CALL_TYPE_ECALL_AUTO or
 MCM_VOICE_CALL_TYPE_ECALL_MANUAL. Ignored otherwise.*/
}mcm_voice_common_dial_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Voice/SS/USSD common dial API. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<   Result code.*/

  /* Optional */
  uint8_t req_changed_to_type_valid;  /**< Must be set to true if req_changed_to_type is being passed */
  mcm_voice_common_dial_type_t_v01 req_changed_to_type;
  /**<   If SS, check optional SS fields. If not present, the voice call went through.*/

  /* Optional */
  uint8_t call_id_valid;  /**< Must be set to true if call_id is being passed */
  uint32_t call_id;
  /**<   Call ID.*/

  /* Optional */
  uint8_t ss_get_cf_status_valid;  /**< Must be set to true if ss_get_cf_status is being passed */
  mcm_voice_call_forwarding_status_t_v01 ss_get_cf_status;
  /**<   Get call forwarding status.*/

  /* Optional */
  uint8_t ss_get_cf_info_valid;  /**< Must be set to true if ss_get_cf_info is being passed */
  uint32_t ss_get_cf_info_len;  /**< Must be set to # of elements in ss_get_cf_info */
  mcm_voice_call_forwarding_info_t_v01 ss_get_cf_info[MCM_MAX_CALL_FORWARDING_INFO_V01];
  /**<   Call forwarding information.*/

  /* Optional */
  uint8_t ss_get_cw_status_valid;  /**< Must be set to true if ss_get_cw_status is being passed */
  mcm_voice_call_waiting_service_t_v01 ss_get_cw_status;
  /**<   Call waiting status.*/

  /* Optional */
  uint8_t ss_get_clir_action_valid;  /**< Must be set to true if ss_get_clir_action is being passed */
  mcm_voice_clir_action_t_v01 ss_get_clir_action;
  /**<   CLIR action.*/

  /* Optional */
  uint8_t ss_get_clir_presentation_valid;  /**< Must be set to true if ss_get_clir_presentation is being passed */
  mcm_voice_clir_presentation_t_v01 ss_get_clir_presentation;
  /**<   CLIR presentation.*/
}mcm_voice_common_dial_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Update the Minimum Set of Data (MSD) for an ongoing or subsequent eCall call. */
typedef struct {

  /* Optional */
  uint8_t ecall_msd_valid;  /**< Must be set to true if ecall_msd is being passed */
  uint32_t ecall_msd_len;  /**< Must be set to # of elements in ecall_msd */
  uint8_t ecall_msd[MCM_MAX_ECALL_MSD_V01];
  /**<  Minimum Set of Data. in ASN.1 PER unaligned format.*/
}mcm_voice_update_msd_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Update the Minimum Set of Data (MSD) for an ongoing or subsequent eCall call. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<  Result code.*/
}mcm_voice_update_msd_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Indication Message; Indication for MCM_VOICE_E911_STATE_IND. */
typedef struct {

  /* Mandatory */
  mcm_voice_e911_state_t_v01 e911_state;
  /**<   E911 state.*/
}mcm_voice_e911_state_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Indication for MCM_VOICE_GET_E911_STATE. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_get_e911_state_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_GET_E911_STATE. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<  Result code.*/

  /* Optional */
  uint8_t e911_state_valid;  /**< Must be set to true if e911_state is being passed */
  mcm_voice_e911_state_t_v01 e911_state;
  /**<   E911 state.*/
}mcm_voice_get_e911_state_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Indication for MCM_VOICE_ECALL_HANGUP. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_ecall_hangup_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_HANGUP. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<  Result code.*/
}mcm_voice_ecall_hangup_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_STATUS_IND. */
typedef struct {

  /* Mandatory */
  uint8_t call_id;
  /**<  call_id.*/

  /* Optional */
  uint8_t ecall_msd_tx_status_valid;  /**< Must be set to true if ecall_msd_tx_status is being passed */
  mcm_ecall_msd_transmission_status_t_v01 ecall_msd_tx_status;
}mcm_voice_ecall_status_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_URC_IND. */
typedef struct {

  /* Mandatory */
  uint8_t call_id;
  /**<  call_id.*/

  /* Mandatory */
  uint32_t ecall_urc_event_len;  /**< Must be set to # of elements in ecall_urc_event */
  char ecall_urc_event[MCM_MAX_ECALL_URC_EVENT_LENGTH_V01];
}mcm_voice_ecall_urc_ind_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Indication for MCM_VOICE_ECALL_COMMAND. */
typedef struct {

  /* Mandatory */
  mcm_voice_ecall_command_t_v01 ecall_command_ivs;
}mcm_voice_ecall_command_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_COMMAND. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<  Result code.*/

  /* Optional */
  uint8_t ecall_state_valid;  /**< Must be set to true if ecall_state is being passed */
  mcm_voice_ecall_state_t_v01 ecall_state;
  /**<  ecall state*/
}mcm_voice_ecall_command_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Indication for MCM_VOICE_ECALL_SET_CONFIG.
Indication for MCM_VOICE_ECALL_GET_CONFIG. */
typedef struct {

  /* Optional */
  uint8_t enable_valid;  /**< Must be set to true if enable is being passed */
  uint8_t enable;

  /* Optional */
  /*  Enable or disable ecall 
	0 -- Disable; 1 -- Enable */
  uint8_t voiceconfig_valid;  /**< Must be set to true if voiceconfig is being passed */
  uint8_t voiceconfig;

  /* Optional */
  /*  Enable or disable to mute IVS speaker in MSD
	0 -- Disable to mute IVS speaker automatical in MSD transmission
	1 -- Enable to mute IVS speaker automatical in MSD transmission */
  uint8_t ecallmode_valid;  /**< Must be set to true if ecallmode is being passed */
  mcm_voice_ecall_mode_t_v01 ecallmode;

  /* Optional */
  /*  The Ecall mode. */
  uint8_t processinfo_valid;  /**< Must be set to true if processinfo is being passed */
  uint8_t processinfo;

  /* Optional */
  /*  Enable or disable to report ecall event info.
	0 -- Disable; 1 -- Enable */
  uint8_t T5_valid;  /**< Must be set to true if T5 is being passed */
  uint16_t T5;

  /* Optional */
  /*  The timer of IVS waiting for "START". */
  uint8_t T6_valid;  /**< Must be set to true if T6 is being passed */
  uint16_t T6;

  /* Optional */
  /*  The timer of IVS waiting for "HACK". */
  uint8_t T7_valid;  /**< Must be set to true if T7 is being passed */
  uint16_t T7;

  /* Optional */
  /*  The timer of MSD transmission. */
  uint8_t mofailredial_valid;  /**< Must be set to true if mofailredial is being passed */
  uint8_t mofailredial;

  /* Optional */
  /*  The dial fail times. */
  uint8_t dropredial_valid;  /**< Must be set to true if dropredial is being passed */
  uint8_t dropredial;
}mcm_voice_ecall_set_config_req_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_SET_CONFIG.
Indication for MCM_VOICE_ECALL_GET_CONFIG. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;
  /**<  Result code.*/
}mcm_voice_ecall_set_config_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Request Message; Indication for MCM_VOICE_ECALL_SET_CONFIG.
Indication for MCM_VOICE_ECALL_GET_CONFIG. */
typedef struct {
  /* This element is a placeholder to prevent the declaration of
     an empty struct.  DO NOT USE THIS FIELD UNDER ANY CIRCUMSTANCE */
  char __placeholder;
}mcm_voice_ecall_get_config_req_msg_v01;

  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_SET_CONFIG.
Indication for MCM_VOICE_ECALL_GET_CONFIG. */
typedef struct {

  /* Mandatory */
  mcm_response_t_v01 response;

  /* Mandatory */
  mcm_voice_ecall_config_info_t_v01 ecall_config_info;
}mcm_voice_ecall_get_config_resp_msg_v01;  /* Message */
/**
    @}
  */

/** @addtogroup mcm_voice_qmi_messages
    @{
  */
/** Response Message; Indication for MCM_VOICE_ECALL_EVENT_IND. */
typedef struct {

  /* Optional */
  uint8_t ecall_event_fails_valid;  /**< Must be set to true if ecall_event_fails is being passed */
  mcm_voice_ecall_event_fail_t_v01 ecall_event_fails;
  /**<   event of eCall Failed.*/

  /* Optional */
  uint8_t ecall_event_process_valid;  /**< Must be set to true if ecall_event_process is being passed */
  mcm_voice_ecall_event_process_t_v01 ecall_event_process;
  /**<   event of eCall process.*/

  /* Optional */
  uint8_t ecall_event_msdupdate_valid;  /**< Must be set to true if ecall_event_msdupdate is being passed */
  mcm_voice_ecall_event_msdupadte_t_v01 ecall_event_msdupdate;
  /**<   event of ecall msd update.*/

  /* Optional */
  uint8_t ecall_event_establish_valid;  /**< Must be set to true if ecall_event_establish is being passed */
  mcm_voice_ecall_event_establish_t_v01 ecall_event_establish;
  /**<   event of eCall establish.*/

  /* Optional */
  uint8_t ecall_event_hackcode_valid;  /**< Must be set to true if ecall_event_hackcode is being passed */
  mcm_voice_ecall_event_hackcode_t_v01 ecall_event_hackcode;
  /**<   event of eCall hack code.*/

  /* Optional */
  uint8_t ecall_event_ori_redial_valid;  /**< Must be set to true if ecall_event_ori_redial is being passed */
  mcm_voice_ecall_event_originate_fail_and_redial_t_v01 ecall_event_ori_redial;
  /**<   event of originate fail and redial.*/

  /* Optional */
  uint8_t ecall_event_drop_redial_valid;  /**< Must be set to true if ecall_event_drop_redial is being passed */
  mcm_voice_ecall_event_drop_and_redial_t_v01 ecall_event_drop_redial;
  /**<   event of drop and redial.*/
}mcm_voice_ecall_event_ind_msg_v01;  /* Message */
/**
    @}
  */

#define MCM_VOICE_GET_CALLS_REQ_V01 0x1000
#define MCM_VOICE_GET_CALLS_RESP_V01 0x1000
#define MCM_VOICE_DIAL_REQ_V01 0x1001
#define MCM_VOICE_DIAL_RESP_V01 0x1001
#define MCM_VOICE_GET_CALL_STATUS_REQ_V01 0x1002
#define MCM_VOICE_GET_CALL_STATUS_RESP_V01 0x1002
#define MCM_VOICE_DTMF_REQ_V01 0x1003
#define MCM_VOICE_DTMF_RESP_V01 0x1003
#define MCM_VOICE_START_DTMF_REQ_V01 0x1004
#define MCM_VOICE_START_DTMF_RESP_V01 0x1004
#define MCM_VOICE_STOP_DTMF_REQ_V01 0x1005
#define MCM_VOICE_STOP_DTMF_RESP_V01 0x1005
#define MCM_VOICE_MUTE_REQ_V01 0x1006
#define MCM_VOICE_MUTE_RESP_V01 0x1006
#define MCM_VOICE_FLASH_REQ_V01 0x1007
#define MCM_VOICE_FLASH_RESP_V01 0x1007
#define MCM_VOICE_HANGUP_REQ_V01 0x1008
#define MCM_VOICE_HANGUP_RESP_V01 0x1008
#define MCM_VOICE_COMMAND_REQ_V01 0x1009
#define MCM_VOICE_COMMAND_RESP_V01 0x1009
#define MCM_VOICE_AUTO_ANSWER_REQ_V01 0x100A
#define MCM_VOICE_AUTO_ANSWER_RESP_V01 0x100A
#define MCM_VOICE_EVENT_REGISTER_REQ_V01 0x100B
#define MCM_VOICE_EVENT_REGISTER_RESP_V01 0x100B
#define MCM_VOICE_GET_CALL_FORWARDING_STATUS_REQ_V01 0x100C
#define MCM_VOICE_GET_CALL_FORWARDING_STATUS_RESP_V01 0x100C
#define MCM_VOICE_SET_CALL_FORWARDING_REQ_V01 0x100D
#define MCM_VOICE_SET_CALL_FORWARDING_RESP_V01 0x100D
#define MCM_VOICE_GET_CALL_WAITING_STATUS_REQ_V01 0x100E
#define MCM_VOICE_GET_CALL_WAITING_STATUS_RESP_V01 0x100E
#define MCM_VOICE_SET_CALL_WAITING_REQ_V01 0x100F
#define MCM_VOICE_SET_CALL_WAITING_RESP_V01 0x100F
#define MCM_VOICE_GET_CLIR_REQ_V01 0x1010
#define MCM_VOICE_GET_CLIR_RESP_V01 0x1010
#define MCM_VOICE_SET_CLIR_REQ_V01 0x1011
#define MCM_VOICE_SET_CLIR_RESP_V01 0x1011
#define MCM_VOICE_SET_FACILITY_LOCK_REQ_V01 0x1012
#define MCM_VOICE_SET_FACILITY_LOCK_RESP_V01 0x1012
#define MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_REQ_V01 0x1013
#define MCM_VOICE_CHANGE_CALL_BARRING_PASSWORD_RESP_V01 0x1013
#define MCM_VOICE_SEND_USSD_REQ_V01 0x1014
#define MCM_VOICE_SEND_USSD_RESP_V01 0x1014
#define MCM_VOICE_CANCEL_USSD_REQ_V01 0x1015
#define MCM_VOICE_CANCEL_USSD_RESP_V01 0x1015
#define MCM_VOICE_COMMON_DIAL_REQ_V01 0x1016
#define MCM_VOICE_COMMON_DIAL_RESP_V01 0x1016
#define MCM_VOICE_CALL_IND_V01 0x1017
#define MCM_VOICE_MUTE_IND_V01 0x1018
#define MCM_VOICE_DTMF_IND_V01 0x1019
#define MCM_VOICE_RECEIVE_USSD_IND_V01 0x101A
#define MCM_VOICE_UPDATE_ECALL_MSD_REQ_V01 0x101B
#define MCM_VOICE_UPDATE_ECALL_MSD_RESP_V01 0x101B
#define MCM_VOICE_E911_STATE_IND_V01 0x101C
#define MCM_VOICE_GET_E911_STATE_REQ_V01 0x101D
#define MCM_VOICE_GET_E911_STATE_RESP_V01 0x101D
#define MCM_VOICE_ECALL_HANGUP_REQ_V01 0x10A0
#define MCM_VOICE_ECALL_HANGUP_RESP_V01 0x10A0
#define MCM_VOICE_ECALL_STATUE_IND_V01 0x10A1
#define MCM_VOICE_ECALL_URC_IND_V01 0x10A2
#define MCM_VOICE_ECALL_COMMAND_REQ_V01 0x10A3
#define MCM_VOICE_ECALL_COMMAND_RESP_V01 0x10A3
#define MCM_VOICE_ECALL_SET_CONFIG_REQ_V01 0x10A4
#define MCM_VOICE_ECALL_SET_CONFIG_RESP_V01 0x10A4
#define MCM_VOICE_ECALL_GET_CONFIG_REQ_V01 0x10A5
#define MCM_VOICE_ECALL_GET_CONFIG_RESP_V01 0x10A5
#define MCM_VOICE_ECALL_EVENT_IND_V01 0x10A6
#ifdef __cplusplus
}
#endif
#endif

