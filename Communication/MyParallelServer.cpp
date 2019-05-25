//
// Created by ariel on 1/14/19.
//

#include "MyParallelServer.h"

MyParallelServer::MyParallelServer() {}

MyParallelServer::~MyParallelServer() {
    // Waiting for all the threads to finish
    for (int i = 0; i < m_threads.size(); i++) {
        m_threads.at(i).join();
    }
}

void MyParallelServer::open(int port, ClientHandler *ch) {
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr{}, client_addr{};
    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        cerr << "Error opening socket" << endl;
        cout << strerror(errno);
        exit(-1);
    }
    // Bind IP_address to socket
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        cerr << "Error binding to address" << endl;
        cout << strerror(errno) << endl;
        this->stop(sockfd);
        exit(-2);
    }
    // Listen for connections until a certain amount of time
    listen(sockfd, SOMAXCONN);
    int clientSize = sizeof(client_addr);
    listen(sockfd, SOMAXCONN);
    // Accept first connection
    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &clientSize);
    if (newsockfd < 0) {
        cerr << "Error accepting connection" << endl;
        cout << strerror(errno) << endl;
        this->stop(sockfd);
        return;
    }
    // Creating a thread that handles the client
    m_threads.emplace_back(thread(clientHandlerObjectFunctionAdapter, ch, newsockfd));

    // Setting info for future threads
    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    while (true) {
        newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &clientSize);
        if (newsockfd < 0) {
            cerr << "Error accepting connection" << endl;
            cout << strerror(errno) << endl;
            break;
        }
        m_threads.emplace_back(thread(clientHandlerObjectFunctionAdapter, ch, newsockfd));
    }
    this->stop(sockfd);
    if (newsockfd != -1) {
        this->stop(newsockfd);
    }
}

void MyParallelServer::stop(int sockfd) {
    close(sockfd);
}

void MyParallelServer::clientHandlerObjectFunctionAdapter(ClientHandler *ch, int sockfd) {
    ch->handleClient(sockfd);
}