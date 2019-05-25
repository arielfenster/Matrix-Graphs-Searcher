//
// Created by ariel on 1/10/19.
//

#ifndef EX4_CLIENTHANDLER_H
#define EX4_CLIENTHANDLER_H

#include <string>

class ClientHandler {

protected:
    void copySolToBuffer(std::string &sol, char *buffer) {
        int i;
        for (i = 0; i < sol.size(); i++) {
            buffer[i] = sol[i];
        }
    }

    void removeStringEnd(std::string &str) {
        if (str.back() == '\n') {
            str = str.substr(0, str.size() - 1);
        }
        if (str.back() == '\r') {
            str = str.substr(0, str.size() - 1);
        }
    }

public:
    virtual void handleClient(int socketId) = 0;
};


#endif //EX4_CLIENTHANDLER_H
