//
// Created by yzm on 19-5-27.
//

#include "ThreadPool.h"
#include <assert.h>
#include <algorithm>
#include <exception>

NetServer::ThreadPool::ThreadPool(const std::string &name)
        : mutex_(),
          cond_(mutex_),
          name_(name),
          running_(false)
{
}

NetServer::ThreadPool::~ThreadPool() {
    if (running_)
    {
        stop();
    }
}

void NetServer::ThreadPool::start(int numThreads) {
    assert(threads_.empty());
    running_ = true;
    threads_.reserve(numThreads);
    for (int i = 0; i < numThreads; ++i)
    {
        char id[32];
        snprintf(id, sizeof id, "%d", i);
        threads_.push_back(new NetServer::Thread(
                std::bind(&ThreadPool::runInThread, this), name_+id));
        threads_[i]->start();
    }
}

void NetServer::ThreadPool::stop() {
    {
        MutexLockGuard lock(mutex_);
        running_ = false;
        cond_.notifyAll();
    }
   std::for_each(threads_.begin(),
             threads_.end(),
             std::bind(&NetServer::Thread::join, std::placeholders::_1));
}

void NetServer::ThreadPool::run(const NetServer::ThreadPool::Task &f) {
    if (threads_.empty())
    {
        f();
    }
    else
    {
        MutexLockGuard lock(mutex_);
        queue_.push_back(f);
        cond_.notify();
    }
}

void NetServer::ThreadPool::runInThread() {
    try
    {
        while (running_)
        {
            Task task(take());
            if (task)
            {
                task();
            }
        }
    }

    catch (const std::exception& ex)
    {
        fprintf(stderr, "exception caught in ThreadPool %s\n", name_.c_str());
        fprintf(stderr, "reason: %s\n", ex.what());
        abort();
    }
    catch (...)
    {
        fprintf(stderr, "unknown exception caught in ThreadPool %s\n", name_.c_str());
        throw; // rethrow
    }
}

NetServer::ThreadPool::Task NetServer::ThreadPool::take() {
    MutexLockGuard lock(mutex_);
    // always use a while-loop, due to spurious wakeup
    while (queue_.empty() && running_)
    {
        cond_.wait();
    }
    Task task;
    if(!queue_.empty())
    {
        task = queue_.front();
        queue_.pop_front();
    }
    return task;
}




