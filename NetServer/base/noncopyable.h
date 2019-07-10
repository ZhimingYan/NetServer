//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_UNCOPYABLE_H
#define NETSERVER_UNCOPYABLE_H

class noncopyable
{
protected:
    noncopyable() {}
    ~noncopyable() {}
private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};

#endif //NETSERVER_UNCOPYABLE_H
