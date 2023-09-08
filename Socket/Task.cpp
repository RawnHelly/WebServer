#pragma once 

#include <iostream>

#include "Protocol.hpp"

class Task{
    private:
        int sock;
        Callback hander;
    public:
        Task() {}
        Task(int _sock) : sock(_sock) {}
        ~Task() {}

        void Prosson(){
            hander(sock);
        }
};