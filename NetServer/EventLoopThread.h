//
// Created by yzm on 19-5-30.
//

#ifndef NETSERVER_EVENTLOOPTHREAD_H
#define NETSERVER_EVENTLOOPTHREAD_H


#include "base/Condition.h"
#include "base/MutexLock.h"
#include "base/Thread.h"
#include "base/noncopyable.h"
#include "EventLoop.h"

namespace NetServer {
    class EventLoopThread : noncopyable {
    public:
        EventLoopThread();

        ~EventLoopThread();

        EventLoop *startLoop();

    private:
        void threadFunc();

        EventLoop *loop_;
        bool exiting_;
        Thread thread_;
        MutexLock mutex_;
        Condition cond_;
    };
}
#endif //NETSERVER_EVENTLOOPTHREAD_H
