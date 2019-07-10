//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_LOGGING_H
#define NETSERVER_LOGGING_H

#include "LogStream.h"
#include <pthread.h>
#include <string.h>
#include <string>
#include <stdio.h>

namespace  NetServer{
    class Logger
    {
    public:

        // compile time calculation of basename of source file
        class SourceFile
        {
        public:
            template<int N>
            SourceFile(const char (&arr)[N])
                    : data_(arr),
                      size_(N-1)
            {
                const char* slash = strrchr(data_, '/'); // builtin function
                if (slash)
                {
                    data_ = slash + 1;
                    size_ -= static_cast<int>(data_ - arr);
                }
            }

            explicit SourceFile(const char* filename)
                    : data_(filename)
            {
                const char* slash = strrchr(filename, '/');
                if (slash)
                {
                    data_ = slash + 1;
                }
                size_ = static_cast<int>(strlen(data_));
            }

            const char* data_;
            int size_;
        };

        Logger(SourceFile file, int line);

        ~Logger();

        LogStream& stream() { return impl_.stream_; }

        typedef void (*OutputFunc)(const char* msg, int len);
        typedef void (*FlushFunc)();
        static void setOutput(OutputFunc);
        static void setFlush(FlushFunc);


    private:

        class Impl
        {
        public:
            Impl(const SourceFile& file, int line);
            void formatTime();
            void finish();

            //Timestamp time_;
            LogStream stream_;
           // LogLevel level_;
            int line_;
            SourceFile basename_;
        };

        Impl impl_;

    };
#define LOG Logger(__FILE__, __LINE__).stream()


}

#endif //NETSERVER_LOGGING_H
