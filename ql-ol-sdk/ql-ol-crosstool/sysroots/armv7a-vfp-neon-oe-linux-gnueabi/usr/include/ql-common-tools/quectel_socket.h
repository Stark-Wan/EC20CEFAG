/**
 * @file quectel_socket.h
 * @brief Quectel socket public function declarations.
 * 
 * @note Provide socket interface, include tcp, udp, unix
 *
 * @copyright Copyright (c) 2010-2017 @ Quectel Wireless Solutions Co., Ltd.
 */
/*============================================================================

                          EDIT HISTORY FOR MODULE
  
  This section contains comments describing changes made to the module.
  Notice that changes are listed in reverse chronological order.
  
  WHEN             WHO         WHAT, WHERE, WHY
  ------------     -------     ----------------------------------------
  08/24/2018       Mike        Adds Unix UDP server
============================================================================*/
#ifndef __QUECTEL_SOCKET_H__
#define __QUECTEL_SOCKET_H__

#include <stdbool.h>

/**
 * create tcp server
 * 
 * @param[in] addr                   The server bind source ipv4 address
 * @param[in] listen_port            The server bind source port
 * @param[in] backlog                The maximum length to which the queue of pending connections for sockfd may grow.
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
extern int quectel_create_tcp_server(const char *addr, const short listen_port, int backlog);

/**
 * create tcp client to connect tcp socket server
 * 
 * @param[in] src_addr              The client bind source ipv4 address
 * @param[in] src_port              The client bind source por
 * @param[in] src_addr              The client connect destination ipv4 address
 * @param[in] src_port              The server connect destination port
 * @param[in] non_block             Setting Non-blocking, if false, connect is nonblock
 * @param[in] timeout               nonblock checking timeout
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
int quectel_create_tcp_client(const char *src_addr, const short src_port, const char *dst_addr,
			      const short dst_port, const bool non_block, const int timeout);

/**
 * create unix socket server
 * 
 * @param[in] sock_name              The unix socket path
 * @param[in] backlog                The maximum length to which the queue of pending connections for sockfd may grow.
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
extern int quectel_create_unix_server(const char *sock_name, int backlog);

/**
 * create unix socket client to connect unix socket server
 * 
 * @param[in] sock_name              The unix socket path
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
extern int quectel_create_unix_client(const char *sock_name);

/**
 * create UDP socket server
 * 
 * @param[in] addr              bind source ipv4 address
 * @param[in] port              bind source port
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
extern int quectel_create_udp(const char *addr, const short port);

/**
 * create PF_PACKET SOCK_RAW socket server
 * 
 * @param[in] ifname            bind nic name
 * @param[in] type              bind network protocol(ETH_P_IP, ETH_P_ALL)
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
extern int quectel_packet_listen(const char *ifname, int type);

/**
 * create UDP unix socket server
 * 
 * @param[in] sock_name              The unix socket path
 *
 * @return 
 *   On success, a file descriptor for the new socket is returned.  On error, -1 is returned.
 * 
 */
extern int quectel_create_unix_udp_server(const char *sock_name);
#endif /* __QUECTEL_SOCKET_H__ */
