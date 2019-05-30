//
// Created by yzm on 19-5-30.
//

#include "NetServer/base/AsyncLogging.h"
#include "NetServer/base/Logging.h"
#include "NetServer/base/Timestamp.h"

#include <stdio.h>
#include <sys/resource.h>
#include <unistd.h>

off_t kRollSize = 500*1000*1000;

NetServer::AsyncLogging* g_asyncLog = NULL;

void asyncOutput(const char* msg, int len)
{
    g_asyncLog->append(msg, len);
}

void bench(bool longLog)
{
    NetServer::Logger::setOutput(asyncOutput);

    int cnt = 0;
    const int kBatch = 1000;
    std::string empty = " ";
    std::string longStr(3000, 'X');
    longStr += " ";

    for (int t = 0; t < 30; ++t)
    {
        NetServer::Timestamp start = NetServer::Timestamp::now();
        for (int i = 0; i < kBatch; ++i)
        {
            NetServer::LOG << "Hello 0123456789" << " abcdefghijklmnopqrstuvwxyz "
                     << (longLog ? longStr : empty)
                     << cnt;
            ++cnt;
        }
        NetServer::Timestamp end = NetServer::Timestamp::now();
        printf("%f\n", timeDifference(end, start)*1000000/kBatch);
        struct timespec ts = { 0, 500*1000*1000 };
        nanosleep(&ts, NULL);
    }
}

int main(int argc, char* argv[])
{
    {
        // set max virtual memory to 2GB.
        size_t kOneGB = 1000*1024*1024;
        rlimit rl = { 2*kOneGB, 2*kOneGB };
        setrlimit(RLIMIT_AS, &rl);
    }

    printf("pid = %d\n", getpid());

    char name[256] = { 0 };
    strncpy(name, argv[0], sizeof name - 1);
    NetServer::AsyncLogging log(::basename(name), kRollSize);
    log.start();
    g_asyncLog = &log;

    bool longLog = argc > 1;
    bench(longLog);
}
