/*
* udp_manager.h
*
* Copyright (c) 2018 STMicroelectronics - All Rights Reserved
* Copyright (c) 2018 CREN - Action de Recherche Tifaifai
*
* Author: Guyot Tifaine <tifaine.guyot@st.com>
*/

#ifndef UDP_MANAGER_H
#define UDP_MANAGER_H
#include "udp_server.h"

/*!
* \file UDP_Manager.h
* \brief DBUS_Server class.
* \author GUYOT Tifaine
* \version 0.1
*/

/*! \class UDP_Manager
* \brief Class which manage the incoming DBUS message.
*
*  This class manage all the incoming message and inform the MTPS when he received a message.
*/
class UDP_Manager
{
public:
  /*!
  *  \brief builder
  *
  *  Builder of the DBUS_Manager class
  *
  */
  UDP_Manager();
  UDP_Manager(std::condition_variable* _cond_var, bool* _isDataAvailable,
    std::vector<std::string> *_listMessagesParent);

  ~UDP_Manager();

private:
  std::condition_variable cond_var;
  std::mutex mut;
  bool isDataAvailable;
  Server_UDP* serv;
  void run();
  std::thread* threadManagerUDP;

  bool* parentWatcher;
  std::condition_variable* cond_var_Parent;
  std::vector<std::string> *listMessagesParent;
};

#endif //UDP_MANAGER_H
