#include "udp_client.h"
/*
* udp_client.cpp
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#include "udp_client.h"

UDP_Client::UDP_Client()
{

}

UDP_Client::~UDP_Client()
{

}

void UDP_Client::die(char *s)
{
  perror(s);
  exit(1);
}

void UDP_Client::init_client()
{
  if ( (sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
    die("socket");
  }

  memset((char *) &si_other, 0, sizeof(si_other));
  si_other.sin_family = AF_INET;
  si_other.sin_port = htons(PORT);

  if (inet_aton(SERVER , &si_other.sin_addr) == 0)
  {
    fprintf(stderr, "inet_aton() failed\n");
    exit(1);
  }

  int broadcastEnable=1;
  setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));

}

void UDP_Client::envoiMessage(std::string messageToSend)
{
  //send the message
  if (sendto(sock, messageToSend.c_str(), messageToSend.length() , 0 , (struct sockaddr *) &si_other, slen)==-1)
  {
    die("sendto()");
  }
}
