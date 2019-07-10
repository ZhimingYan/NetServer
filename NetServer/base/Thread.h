//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_THREAD_H
#define NETSERVER_THREAD_H

#include"noncopyable.h"
#include "CountDownLatch.h"


#include <functional>
#include <memory>
#include <pthread.h>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>

namespace NetServer{

    class Thread : noncopyable{
    public:
        typedef std::function<void ()>ThreadFunc;
        explicit Thread(const ThreadFunc&,const std::string& name = std:: string());
        ~Thread();
        void start();
        //void *startThread(void* obj);
        int join();
        bool started() const{return started_ ;};

    private:
        void setDefaultName();
        bool started_;
        bool joined_;
        pthread_t pthreadId_;
        pid_t tid_;
        ThreadFunc func_;
        std::string name_;
        NetServer::CountDownLatch latch_;
    };



};


#endif //NETSERVER_THREAD_H
