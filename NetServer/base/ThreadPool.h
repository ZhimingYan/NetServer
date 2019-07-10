//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_THREADPOOL_H
#define NETSERVER_THREADPOOL_H

#include "noncopyable.h"
#include "MutexLock.h"
#include "Thread.h"

#include <functional>
#include <string>
#include <vector>
#include <deque>
#include <utility>
#include <boost/ptr_container/ptr_vector.hpp>

namespace NetServer{
    class ThreadPool : noncopyable{
    public:
        typedef std::function<void ()> Task;

        explicit ThreadPool(const std::string& name = std::string());
        ~ThreadPool();

        void start(int numThreads);
        void stop();

        void run(const Task& f);

    private:
        void runInThread();
        Task take();

        MutexLock mutex_;
        Condition cond_;
        std::string name_;
        std::vector<NetServer::Thread*> threads_;
        //std::vector<std::unique_ptr<NetServer::Thread>>threads_;
        //boost::ptr_vector<NetServer::Thread> threads_;
        std::deque<Task> queue_;
        bool running_;

    };
}


#endif //NETSERVER_THREADPOOL_H
