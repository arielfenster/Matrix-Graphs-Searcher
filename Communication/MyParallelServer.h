//
// Created by ariel on 1/14/19.
//

#ifndef EX4_MYPARALLELSERVER_H
#define EX4_MYPARALLELSERVER_H

#include "Server.h"
#include <vector>
#include <thread>

class MyParallelServer : public server_side::Server{
    vector<thread> m_threads;
    ClientHandler* m_handler;

private:
    static void clientHandlerObjectFunctionAdapter(ClientHandler* ch, int sockfd);

public:
    MyParallelServer();
    virtual ~MyParallelServer();

    virtual void open(int port, ClientHandler* ch);
    virtual void stop(int sockfd);
};



#endif //EX4_MYPARALLELSERVER_H
