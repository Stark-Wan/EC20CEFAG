/**
 * @file quectel_string.h
 * @brief Quectel string public function declarations.
 *
 * @note
 *
 * @copyright Copyright (c) 2010-2017 @ Quectel Wireless Solutions Co., Ltd.
 */
/*=============================================================================
  Copyright (c) 2018 Quectel Wireless Solution, Co., Ltd.  All Rights Reserved.
  Quectel Wireless Solution Proprietary and Confidential.
=============================================================================*/

/*============================================================================

                          EDIT HISTORY FOR MODULE
  
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
  
  WHEN             WHO         WHAT, WHERE, WHY
  ------------     -------     ----------------------------------------
  07/06/2018       Mike        Adds MAC format defined.
============================================================================*/
#ifndef __QUECTEL_STRING_H__
#define __QUECTEL_STRING_H__

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/* the mac format string */
#ifndef MACSTR
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#ifndef MAC2STR
#define MAC2STR(a) (unsigned char)(a)[0], (unsigned char)(a)[1], (unsigned char)(a)[2], \
		(unsigned char)(a)[3], (unsigned char)(a)[4], (unsigned char)(a)[5]
#endif

/**
 * Checks string for a digit (0 through 9).
 *
 * @param[in] str    Character string
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_string_isdigit(const char *str);

/**
 * checks for an alphanumeric character (A through Z).
 *
 * @param[in] letter    Character.
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_isalpha_upper(char letter);

/**
 * checks string for an alphanumeric character (A through Z).
 *
 * @param[in] str    Character string
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_string_isalpha_upper(const char *str);

/**
 * converts the IPv4 numbers-and-dots natation into from the internet host address
 *
 * @param[in] ip    The internet host address
 *
 * @return the IPv4 numbers-and-dots natation into
 * 
 */
extern char *quectel_ip_int_to_string(int ip);

/**
 * converts the IPv6 numbers-and-dots natation into from the internet host address
 *
 * @param[in] addr6    The internet IPv6 host address
 *
 * @return the IPv6 numbers-and-dots natation into
 * 
 */
extern char *quectel_ipv6_ntop(struct in6_addr addr6);

/**
 * converts the IPv4 numbers-and-dots natation into from the internet host address
 *
 * @param[in] addr4    The internet IPv4 host address
 *
 * @return the IPv4 numbers-and-dots natation into
 * 
 */
extern char *quectel_ipv4_ntoa(unsigned int addr4);

/**
 * Verify the IPv4 address format
 *
 * @param[in] addr4    The numbers-and-dots IPv4 host address
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_ipv4_check(char *addr4);

/**
 * convert a string to an integer
 *
 * @param[in] nptr     string pointer
 * @param[out] val     converts the initial portion of the string pointed to val
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_atoi(const char *nptr, int *val);

/**
 * The function returns a pointer to a new string which is a duplicate of the string.
 * Memory for the new string is obtained with malloc(3), and can be freed with free(3).
 *
 * @param[in] fmt     the string format
 *
 * @return On success, the function returns a pointer to the duplicated string.
 *         It returns NULL if insufficient memory was available
 * 
 */
extern char *quectel_strdup(const char *fmt, ...) __attribute ((format(printf, 1, 2)));

/**
 * The function remove the string before and after the double quotation marks
 *
 * @param[out] dest     the string remove before and after the double quotation marks
 * @param[in] src       source string
 * @param[in] dst_len   the length of dest.
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_double_quotes_to_string(char *dest, const char *src, int dst_len);

/**
 * The function convert string type mac address to bytes.
 * such as: AA:BB:CC:DD:EE:FF ==> char mac[6] = {0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
 *
 * @param[out] dest     the string remove before and after the double quotation marks
 * @param[in] src       source string
 *
 * @return On success, Zero is returned. On error, -1 is returned.
 * 
 */
extern int quectel_mac_to_char(const char *src_mac, char *dst_mac);

#endif /* end of __QUECTEL_STRING_H__ */
