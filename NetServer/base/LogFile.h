//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_LOGFILE_H
#define NETSERVER_LOGFILE_H

#include "FileUtil.h"
#include "MutexLock.h"
#include "noncopyable.h"
#include <memory>
#include <string>

namespace NetServer {
        class LogFile : noncopyable
        {
        public:
            // 每被append flushEveryN次，flush一下，会往文件写，只不过，文件也是带缓冲区的
            LogFile(const std::string& basename,
                    off_t rollSize,
                    bool threadSafe = true,
                    int flushInterval = 3,
                    int checkEveryN = 1024);
            ~LogFile();

            void append(const char* logline, int len);
            void flush();
            bool rollFile();

        private:
            void append_unlocked(const char* logline, int len);

            static std::string getLogFileName(const std::string& basename, time_t* now);

            const std::string basename_;
            const off_t rollSize_;
            const int flushInterval_;
            const int checkEveryN_;

            int count_;

            std::unique_ptr<MutexLock> mutex_;
            time_t startOfPeriod_;
            time_t lastRoll_;
            time_t lastFlush_;
            std::unique_ptr<AppendFile> file_;

            const static int kRollPerSeconds_ = 60*60*24;
        };
}


#endif //NETSERVER_LOGFILE_H
