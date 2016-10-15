//
//  Network.h
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/4/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#ifndef __CSE486AIProject__Network__
#define __CSE486AIProject__Network__

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <sstream>
#ifdef _WIN32
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#include<sys/socket.h>    //socket
#include<arpa/inet.h> //inet_addr
#include<netdb.h> //hostent
#endif

class TCPClient {
    
public:
    static const int DEFAULT_BUFF_LENGTH = 512;
    
    TCPClient();
    bool create(std::string, int);
    bool sendMsg(const std::string &data) const;
    std::string receiveMsg();
    ~TCPClient();
    
private:
#ifdef _WIN32
    SOCKET sock;
#else
    int sock;
#endif
    std::string address;
    int port;
    struct sockaddr_in server;
    std::string internalBuf;
};


#endif /* defined(__CSE486AIProject__Network__) */
