//
// Created by yzm on 19-5-27.
//

#include "Logging.h"
#include "CurrentThread.h"
#include "Thread.h"
#include "AsyncLogging.h"
#include <assert.h>
#include <iostream>
#include <time.h>
#include <sys/time.h>
namespace NetServer {
    class T {
    public:
        T(const char *str, unsigned len)
                : str_(str),
                  len_(len) {
            assert(strlen(str) == len_);
        }

        const char *str_;
        const unsigned len_;
    };

    inline LogStream &operator<<(LogStream &s, T v) {
        s.append(v.str_, v.len_);
        return s;
    }

    inline LogStream &operator<<(LogStream &s, const Logger::SourceFile &v) {
        s.append(v.data_, v.size_);
        return s;
    }

    void defaultOutput(const char *msg, int len) {
        size_t n = fwrite(msg, 1, len, stdout);
        //FIXME check n
        (void) n;
    }

    void defaultFlush() {
        fflush(stdout);
    }

    Logger::OutputFunc output = defaultOutput;
    Logger::FlushFunc g_flush = defaultFlush;

}
namespace  NetServer{


//    static pthread_once_t once_control_ = PTHREAD_ONCE_INIT;
//    static AsyncLogging *AsyncLogger_;
//
//    //std::string Logger::logFileName_ = "/yzm_NetServer.log";
//
//    void once_init() {
//        AsyncLogger_ = new AsyncLogging(Logger::getLogFileName());
//        std::cout << Logger::getLogFileName()<<std::endl;
//        AsyncLogger_->start();
//    }
//
//    void output(const char *msg, int len) {
//        pthread_once(&once_control_, once_init);
//        AsyncLogger_->append(msg, len);
//    }

    Logger::Impl::Impl(const SourceFile& file, int line)
            : stream_(),
              line_(line),
              basename_(file) {
        formatTime();
     //   std::cout << "Impl" << std::endl;
    }

    void Logger::Impl::formatTime() {
        struct timeval tv;
        time_t time;
        char str_t[26] = {0};
        gettimeofday(&tv, NULL);
        time = tv.tv_sec;
        struct tm *p_time = localtime(&time);
        strftime(str_t, 26, "%Y-%m-%d %H:%M:%S\n", p_time);
     //   std::cout<<p_time<<std::endl;
        stream_ << str_t;
    }

    Logger::Logger(SourceFile file, int line)
            : impl_(file, line) {

    }

    Logger::~Logger() {
        impl_.stream_ << " -- " << impl_.basename_ << ':' << impl_.line_ << '\n';

        const LogStream::Buffer &buf(stream().buffer());
        output(buf.data(), buf.length());
    }

    void Logger::setOutput(Logger::OutputFunc out) {
        output = out;
    }
}