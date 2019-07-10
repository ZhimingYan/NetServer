//
// Created by yzm on 19-5-27.
//

#include "FileUtil.h"
#include <assert.h>


#include <iostream>
NetServer::AppendFile::AppendFile(std::string filename)
    :   fp_(::fopen(filename.c_str(), "ae"))

{
    assert(fp_);
    ::setbuffer(fp_, buffer_, sizeof buffer_);
}

NetServer::AppendFile::~AppendFile() {
    ::fclose(fp_);
}

void NetServer::AppendFile::append(const char *logline, const size_t len) {
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while (remain > 0)
    {
        size_t x = this->write(logline + n, remain);
        if (x == 0)
        {
            int err = ferror(fp_);
            if (err)
                fprintf(stderr, "AppendFile::append() failed !\n");
            break;
        }
        n += x;
        remain = len - n;
    }
}

void NetServer::AppendFile::flush() {
    ::fflush(fp_);
}

size_t NetServer::AppendFile::write(const char *logline, size_t len) {
    return fwrite_unlocked(logline, 1, len, fp_);
}
