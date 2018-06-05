/*
* udp_client.h
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define SERVER "255.255.255.255"
#define PORT 8888   //The port on which to send data

class UDP_Client
{
public:
  UDP_Client();
  ~UDP_Client();
  void die(char *s);
  void envoiMessage(std::string messageToSend);
  void init_client();

private:
  struct sockaddr_in si_other;
  int sock, slen=sizeof(si_other);

};
#endif //UDP_CLIENT_H
