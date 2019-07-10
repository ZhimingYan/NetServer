//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_FILEUTIL_H
#define NETSERVER_FILEUTIL_H

#include "noncopyable.h"
#include <string>

namespace NetServer{
    class AppendFile : noncopyable{
    public:
        explicit AppendFile(std::string filename);
        ~AppendFile();


        void append(const char *logline, const size_t len);
        void flush();

        off_t writtenBytes() const { return writtenBytes_; }


    private:
        size_t write(const char *logline, size_t len);
        FILE* fp_;
        char buffer_[64*1024];
        off_t writtenBytes_;
    };
}

#endif //NETSERVER_FILEUTIL_H
