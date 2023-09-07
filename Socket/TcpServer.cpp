/*create a class for tcp*/
#pragma once

#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<cstdlib>
#include<cstring>
#include<iostream>

#include "Log.hpp"

class TcpServer{
    private:
        int port;
        int listen_fd;
        static TcpServer* server_fd;
    private:
        TcpServer(int _port) : port(_port) , listen_fd(-1){} //这里我们将构造函数定义为private，这样子类就无法继承
        TcpServer(const TcpServer &s){}
    public:

        void init();
        void Socket();
        void Listen();
        void Bind();
        int Sock(); //返回链接的套接字
        static TcpServer *getinstance(int port){
            static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
            if(server_fd == nullptr){
                pthread_mutex_lock(&lock); // 先加锁
                server_fd = new TcpServer(port);
                server_fd->init();
                pthread_mutex_unlock(&lock);
            }

            return server_fd;
        }

        void init(){
            Socket(); //创建
            Bind(); //绑定
            Listen(); //监听
        }

        void Socket(){
            listen_fd = socket(AF_INET , SOCK_STREAM , 0);
            if(listen_fd < 0)
                exit(1);
            int opt = 1;
            setsockopt(listen_fd , SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        }

        void Bind(){
            struct sockaddr_in local;
            memset(&local, 0, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = INADDR_ANY; //云服务器不能直接绑定公网IP

            if(bind(listen_fd, (struct sockaddr*)&local, sizeof(local)) < 0){
                LOG(FATAL, "bind error!");
                exit(2);
            }
        }

        void Listen(){
            if(listen(listen_fd , 5) < 0){
                exit(3);
            }
        }

        int Sock(){
            return listen_fd;
        }

        ~TcpServer(){
            if(listen_fd > 0)
                close(listen_fd);
        }
};

TcpServer* TcpServer::server_fd = nullptr;