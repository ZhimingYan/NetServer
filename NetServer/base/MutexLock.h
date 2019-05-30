//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_MUTEXLOCK_H
#define NETSERVER_MUTEXLOCK_H

#include "noncopyable.h"
#include <pthread.h>
#include <cstdio>
namespace NetServer {
    class MutexLock: noncopyable
    {
    public:
        MutexLock()
        {
            pthread_mutex_init(&mutex, NULL);
        }
        ~MutexLock()
        {
            pthread_mutex_lock(&mutex);
            pthread_mutex_destroy(&mutex);
        }
        void lock()
        {
            pthread_mutex_lock(&mutex);
        }
        void unlock()
        {
            pthread_mutex_unlock(&mutex);
        }
        pthread_mutex_t *get()
        {
            return &mutex;
        }
    private:
        pthread_mutex_t mutex;

// 友元类不受访问权限影响
    private:
        friend class Condition;
    };


    class MutexLockGuard: noncopyable
    {
    public:
        explicit MutexLockGuard(MutexLock &_mutex):
                mutex(_mutex)
        {
            mutex.lock();
        }
        ~MutexLockGuard()
        {
            mutex.unlock();
        }
    private:
        MutexLock &mutex;
    };
};


#endif //NETSERVER_MUTEXLOCK_H
