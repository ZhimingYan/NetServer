//
// Created by yzm on 19-5-30.
//

#ifndef NETSERVER_SERVER_H
#define NETSERVER_SERVER_H

#include "EventLoop.h"
#include "Channel.h"
#include "EventLoopThreadPool.h"
#include <memory>

namespace  NetServer {
    class Server {
    public:
        Server(EventLoop *loop, int threadNum, int port);

        ~Server() {}

        EventLoop *getLoop() const { return loop_; }

        void start();

        void handNewConn();

        void handThisConn() { loop_->updatePoller(acceptChannel_); }

    private:
        EventLoop *loop_;
        int threadNum_;
        std::unique_ptr<EventLoopThreadPool> eventLoopThreadPool_;
        bool started_;
        std::shared_ptr<Channel> acceptChannel_;
        int port_;
        int listenFd_;
        static const int MAXFDS = 100000;
    };
}


#endif //NETSERVER_SERVER_H
