/*
* udp_server.h
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#ifndef UDP_SERVER_H
#define UDP_SERVER_H
#include <iostream>
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <condition_variable>
#include <mutex>
#include <vector>
#include <thread>
#include <errno.h>
#define SOCKET_ERROR -1
#define BUFLEN 2048
#define PORT 8888

/*!
* \file udp_server.h
* \brief UDP_Server class.
* \author GUYOT Tifaine
* \version 0.1
*/

class Server_UDP
{
public:
  Server_UDP();
  ~Server_UDP();

  int init_server();

  void die(char *s);

  std::condition_variable* getCV(){return cv;}
  void setCV(std::condition_variable* _cv){cv = _cv;}

  std::vector<std::string>* getListMessage(){return listMessages;}

  void setNewMessage(bool* _nm){newMessage = _nm;}
  bool* getNewMessage(){return newMessage;}

private:
  int run();

  bool* newMessage;
  std::thread* threadUDP;
  std::vector<std::string>* listMessages;
  std::condition_variable *cv;

  int sock;
  char buf[BUFLEN];


};


#endif //UDP_SERVER_H
