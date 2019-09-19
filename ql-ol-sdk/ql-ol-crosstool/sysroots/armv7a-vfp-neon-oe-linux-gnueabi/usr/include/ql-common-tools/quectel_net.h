/**
 * @file quectel_net.h
 * @brief Quectel network public function declarations.
 *
 * @note 
 *
 * @copyright Copyright (c) 2010-2017 @ Quectel Wireless Solutions Co., Ltd.
 */

#ifndef __QUECTEL_NET_H__
#define __QUECTEL_NET_H__

/**
 * Get IPv4/IPv6 address for the given URL.
 *
 * @param[in] url    URL or IP address.
 *
 * @return On success, the IPv4/IPv6 Character is returned. On error, NULL is returned.
 * 
 */
extern const char *quectel_gethostbyurl(char *url);

/**
 * Resolve the domain name through the specified dns server
 *
 * @param[in] nameserver    the dns server, it format nameserver x.x.x.x or nameserver xx::xx
 * @param[in] url           URL or IP address.
 * @param[out] dst          the IP address from url
 *
 * @return On success, the IPv4/IPv6 Character is returned. On error, NULL is returned.
 * 
 */
extern int quectel_resolver_dns(const char *nameserver, const char *url, void *dst);

#endif /* end of __QUECTEL_NET_H__ */

