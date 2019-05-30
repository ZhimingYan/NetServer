
set(SRCS
        HttpData.cpp HttpData.h Epoll.cpp Epoll.h Channel.cpp Channel.h EventLoop.cpp EventLoop.h Util.cpp Util.h Timer.cpp Timer.h ThreadPool.cpp ThreadPool.h EventLoopThread.cpp EventLoopThread.h EventLoopThreadPool.cpp EventLoopThreadPool.h Server.cpp Server.h Main.cpp)
include_directories(${PROJECT_SOURCE_DIR}/base)


add_executable(NetServer ${SRCS})
target_link_libraries(NetServer libserver_base)


