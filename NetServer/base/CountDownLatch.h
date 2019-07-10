//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_COUNTDOWNLATCH_H
#define NETSERVER_COUNTDOWNLATCH_H


#include "CountDownLatch.h"
#include "MutexLock.h"
#include "Condition.h"
#include "noncopyable.h"

namespace NetServer{
    class CountDownLatch : noncopyable
    {
    public:
        explicit CountDownLatch(int count);
        void wait();
        void countDown();

    private:
        mutable MutexLock mutex_;
        Condition condition_;
        int count_;
    };

}

#endif //NETSERVER_COUNTDOWNLATCH_H
