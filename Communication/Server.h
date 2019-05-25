//
// Created by ariel on 1/10/19.
//

#ifndef EX4_SERVER_H
#define EX4_SERVER_H

#include "../ClientHandler/ClientHandler.h"
#include <iostream>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <chrono>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include <cstring>
#define TIME_OUT 1

using namespace std;

namespace server_side {

    class Server {

    public:
        virtual ~Server() {}
        virtual void open(int port, ClientHandler* c) = 0;
        virtual void stop(int sockfd) = 0;
    };
}

#endif //EX4_SERVER_H
