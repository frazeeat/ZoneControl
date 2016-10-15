//
//  Network.cpp
//  CSE486AIProject
//
//  Created by Yunlong Nick Liu on 6/4/15.
//  Copyright (c) 2015 Yunlong Nick Liu. All rights reserved.
//

#include "Network.h"

#ifdef _WIN32
const char *NEW_LINE_CHARACTER = "\r\n";

bool TCPClient::create(std::string address , int port) {
    WSAData wsaData;        //We need to check the version.
    int iResult = WSAStartup(MAKEWORD(2,2),&wsaData);
    if(iResult != 0) {
        std::cout<<"Startup fail.\n" << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }
    sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(sock == INVALID_SOCKET) {
        std::cout<<"Creating socket fail\n";
        WSACleanup();
        return false;
    }
 //   std::cout<<"socket created";
    
    //Socket address information
    sockaddr_in addr;
    addr.sin_family=AF_INET;
#pragma warning(disable: 4996) /* Disable deprecation */
	addr.sin_addr.s_addr = inet_addr(address.c_str());
#pragma warning(default: 4996) /* Restore default */
    addr.sin_port=htons(port);
    /*==========Addressing finished==========*/
    
    //Now we connect
    int conn = connect(sock, (SOCKADDR*)&addr, sizeof(addr));
    if(conn==SOCKET_ERROR){
        std::cout<<"Error - when connecting "<<WSAGetLastError()<<std::endl;
        closesocket(sock);
        WSACleanup();
        return false;
    }
    return true;
}

TCPClient::~TCPClient() {
    WSACleanup();
    closesocket(sock);
}

#else
const char NEW_LINE_CHARACTER = '\n';
bool TCPClient::create(std::string address , int port) {
    if(sock == -1) {
        sock = socket(AF_INET , SOCK_STREAM , 0);
        if (sock == -1) {
            std::perror("Could not create socket");
            return false;
        }
    }
    server.sin_addr.s_addr = inet_addr(address.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons( port );
    if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0) {
        std::perror("connect failed. Error");
        return false;
    }
    std::cout << "Connected\n";
    return true;
}

TCPClient::~TCPClient() {
    close(sock);
}

#endif

TCPClient::TCPClient() : sock(-1), port(0), address(""), internalBuf("") {}

bool TCPClient::sendMsg(const std::string &msg) const {
	std::string oMsg = msg + NEW_LINE_CHARACTER;
	const char* cMsg = oMsg.c_str();
    if(send(sock , cMsg , strlen(cMsg) , 0) < 0) {
        std::perror("Send failed : ");
        return false;
    }
    return true;
}

std::string TCPClient::receiveMsg() {
    if (internalBuf.empty()) {
        char buffer[DEFAULT_BUFF_LENGTH];
        size_t len = recv(sock , buffer , DEFAULT_BUFF_LENGTH , 0);
		buffer[len] = '\0';
        internalBuf = buffer;
    }
    std::stringstream strm(internalBuf);
    std::string next;
    std::getline(strm, next);
	if (next[next.length() - 1] == '\r')
		next = next.substr(0, next.length() - 1);
    std::getline(strm, internalBuf, '\xff');
    return next;
}









