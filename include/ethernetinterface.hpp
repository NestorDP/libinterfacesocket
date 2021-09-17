/**
 * @ Copyright 2020
 */

/**
 * @mainpage Ethernet Interface Library Documentation
 * @section intro_sec Indroduction
 * This is the ethernet interface C++ library for socket communication
 * 
 * 
 */
#ifndef _ETHERNET_INTERFACE_HPP_
#define _ETHERNET_INTERFACE_HPP_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <cstdlib>

#define BUFFER_LEN 512
#define TCP 1
#define UDP 0

/**
 * @brief Ethernet Interface Library namespace
 * @author Nestor Pereira Neto
 * 
 */

namespace sock {

/**
 * @brief EthernetInterface class 
 * 
 */

class EthernetInterface{
 public:
    /**
     * @brief Construct a new Ethernet Interface object
     * 
     */
    EthernetInterface();

    /**
     * @brief Destroy the Ethernet Interface object
     * 
     */
    ~EthernetInterface();

    /**
     * @brief Create a socket object
     * 
     * @param ip_server 
     * @param port 
     * @param protocol 
     */
    void create_socket(std::string ip_server, int port, bool protocol);

    /**
     * @brief Create a socket object
     * 
     * @param port 
     * @param protocol 
     */
    void create_socket(int port, bool protocol);

    /**
     * @brief 
     * 
     * @param msg 
     * @param len_buffer 
     * @param len_msg 
     * @return int 
     */
    int net_send(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg);

    /**
     * @brief 
     * 
     * @param msg 
     * @param len_buffer 
     * @param len_msg 
     * @return int 
     */
    int net_recv(uint8_t *msg, unsigned int len_buffer, int unsigned len_msg);

 private:
    /** remote_addr variable */
    struct sockaddr_in remote_addr;

    /** remote_addr variable */
    struct sockaddr_in local_addr;

    /** remote_addr variable */
    int port;

    /** remote_addr variable */
    int localfd = 1;

    /** remote_addr variable */
    int remotefd = 1;

    /** remote_addr variable */
    bool prtlc;
};
}  // namespace sock

#endif  // _ETHERNET_INTERFACE_HPP_
