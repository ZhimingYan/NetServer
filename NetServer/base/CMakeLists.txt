set(LIB_SRC
        Timestamp.cc
        #uncopyable.h
        Thread.cpp
        #Thread.h
        CountDownLatch.cpp
        CountDownLatch.h
        CurrentThread.h
        Atomic.h
        MutexLock.h Condition.h ThreadPool.cpp ThreadPool.h LogFile.cpp LogFile.h FileUtil.cpp FileUtil.h Logging.cpp Logging.h LogStream.cpp LogStream.h AsyncLogging.cpp AsyncLogging.h )
file(GLOB HEADERS "*.h")
add_library(libserver_base ${LIB_SRC})
target_link_libraries(libserver_base pthread rt)

set_target_properties(libserver_base PROPERTIES OUTPUT_NAME "server_base")

add_subdirectory(tests)