//
// Created by ariel on 1/10/19.
//

#ifndef EX4_MYSERIALSERVER_H
#define EX4_MYSERIALSERVER_H

#include "Server.h"

class MySerialServer : public server_side::Server {

public:
    MySerialServer();
    virtual ~MySerialServer();

    virtual void open(int port, ClientHandler* ch);
    virtual void stop(int sockfd);
};


#endif //EX4_MYSERIALSERVER_H
