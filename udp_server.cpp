#include "udp_server.h"

Server_UDP::Server_UDP()
{
  listMessages = new std::vector<std::string>();
}

Server_UDP::~Server_UDP()
{

}

void Server_UDP::die(char *s)
{
  perror(s);
  exit(1);
}

int Server_UDP::init_server()
{
  struct sockaddr_in si_me;
  if ((sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
  {
    die("socket");
  }

  // zero out the structure
  memset((char *) &si_me, 0, sizeof(si_me));
  si_me.sin_family = AF_INET;
  si_me.sin_port = htons(PORT);
  si_me.sin_addr.s_addr = INADDR_ANY;
  //bind socket to port
  if( bind(sock , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
  {
    die("bind");
  }
  threadUDP = new std::thread(&Server_UDP::run,this);

}

int Server_UDP::run()
{
  struct sockaddr_in si_other;
  int slen = sizeof(si_other) , recv_len;
  while(1)
  {
    //try to receive some data, this is a blocking call
    recv_len =  recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr *) &si_other, (unsigned int*)(&slen));
    if ( recv_len== -1)
    {
      die("recvfrom()");
    }
    *newMessage = true;

    listMessages->push_back(buf);

    cv->notify_one();
    //Clear the buffer before the next incoming message.
    memset(buf, 0, (BUFLEN));
  }
  return 0;
}
