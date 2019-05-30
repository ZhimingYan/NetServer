//
// Created by yzm on 19-5-27.
//

#include "CountDownLatch.h"

NetServer::CountDownLatch::CountDownLatch(int count)
    :   mutex_(),
        condition_(mutex_),
        count_(count)
{

}

void NetServer::CountDownLatch::wait() {
    MutexLockGuard lock(mutex_);
    while (count_ > 0)
        condition_.wait();
}

void NetServer::CountDownLatch::countDown() {
    MutexLockGuard lock(mutex_);
    --count_;
    if (count_ == 0)
        condition_.notifyAll();
}


