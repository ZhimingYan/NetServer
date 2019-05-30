//
// Created by yzm on 19-5-30.
//

#ifndef NETSERVER_EVENTLOOPTHREADPOOL_H
#define NETSERVER_EVENTLOOPTHREADPOOL_H
#include "base/noncopyable.h"
#include "EventLoopThread.h"
#include "base/Logging.h"
#include <memory>
#include <vector>

namespace NetServer {
    class EventLoopThreadPool : noncopyable {
    public:
        EventLoopThreadPool(EventLoop *baseLoop, int numThreads);

        ~EventLoopThreadPool() {
            LOG << "~EventLoopThreadPool()";
        }

        void start();

        EventLoop *getNextLoop();

    private:
        EventLoop *baseLoop_;
        bool started_;
        int numThreads_;
        int next_;
        std::vector<std::shared_ptr<EventLoopThread>> threads_;
        std::vector<EventLoop *> loops_;
    };

}
#endif //NETSERVER_EVENTLOOPTHREADPOOL_H
