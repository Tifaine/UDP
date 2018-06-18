/*
* udp_manager.cpp
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#include "udp_manager.h"

UDP_Manager::UDP_Manager()
{
  serv = new Server_UDP();
  serv->setCV(&cond_var);
  serv->setNewMessage(&isDataAvailable);
  serv->init_server();
  threadManagerUDP = new std::thread(&UDP_Manager::run,this);
}

UDP_Manager::UDP_Manager(std::condition_variable* _cond_var,
  bool* _isDataAvailable,
  std::vector<std::string> *_listMessagesParent)
{
  serv = new Server_UDP();

  cond_var_Parent = _cond_var;
  parentWatcher = _isDataAvailable;
  listMessagesParent = _listMessagesParent;

  serv->setCV(&cond_var);
  serv->setNewMessage(&isDataAvailable);
  serv->init_server();
  threadManagerUDP = new std::thread(&UDP_Manager::run,this);
}



UDP_Manager::~UDP_Manager()
{

}

void UDP_Manager::run()
{
  while(1)
  {
    std::unique_lock<std::mutex> lk(mut);
    cond_var.wait(lk, [this]{return isDataAvailable;});
    isDataAvailable = false;
    while (!serv->getListMessage()->empty())
    {
      std::cout<<(serv->getListMessage()->back())<<std::endl;
      //Do whatever you want with your message here !
      *parentWatcher = true;
      listMessagesParent->push_back(serv->getListMessage()->back());
      cond_var_Parent->notify_one();

      serv->getListMessage()->pop_back();
    }
  }
}
