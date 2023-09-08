#pragma once

#include <iostream>
#include <queue>
#include <pthread.h>
#include "Task.cpp"

#define NUM 6
class PthreadPool {
    private:
        int num;
        bool stop;
        std::queue<Task> task_queue;
        pthread_mutex_t lock;
        pthread_cond_t cond;

        PthreadPool(int _num = NUM) : num(_num) , stop(false){
            pthread_mutex_init(&lock , nullptr);
            pthread_cond_init(&cond , nullptr);
        } 
        PthreadPool(const PthreadPool&){}

        static PthreadPool *single_instance;
    public:
        void InitPthreadPool();
        static PthreadPool* getinstance(){
            static pthread_mutex_t _mutex = PTHREAD_MUTEX_INITIALIZER;
            if(single_instance == nullptr){
                pthread_mutex_lock(&_mutex);
                single_instance = new PthreadPool();
                single_instance->InitPthreadPool();
            }
        }
}