#include "udp_client.h"

int main()
{
  UDP_Client client;
  client.init_client();
  client.envoiMessage("Coucou");
}
