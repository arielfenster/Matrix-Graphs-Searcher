//
// Created by ariel on 1/10/19.
//

#include "MySerialServer.h"

MySerialServer::MySerialServer() {}

MySerialServer::~MySerialServer() {}


void MySerialServer::open(int port, ClientHandler *ch) {
    int sockfd, newsockfd = -1;

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
        this->stop(sockfd);
        cout << strerror(errno);
        exit(-2);
    }
    // Listen for connections until a certain amount of time
    listen(sockfd, SOMAXCONN);
    int clientSize = sizeof(client_addr);

    timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));

    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &clientSize);
    if (newsockfd < 0) {
        cout << strerror(errno);
        cerr << "Error accepting connection" << endl;
        cout << strerror(errno);
        this->stop(sockfd);
        return;
    }
    thread t(&ClientHandler::handleClient, ch, newsockfd);
    t.join();


    timeout.tv_sec = 1;
    timeout.tv_usec = 0;
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
    while (true) {
        // Accept incoming connection
        newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &clientSize);
        if (newsockfd < 0) {
            cerr << "Error accepting connection" << endl;
            cout << strerror(errno);
            break;
        }
        // Create a thread that runs the function and wait for it to finish
        thread t2(&ClientHandler::handleClient, ch, newsockfd);
        t2.join();
    }
    // Close socket
    this->stop(sockfd);
    if (newsockfd != -1) {
        this->stop(newsockfd);
    }
}

void MySerialServer::stop(int sockfd) {
    close(sockfd);
}