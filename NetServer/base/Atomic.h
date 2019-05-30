//
// Created by yzm on 19-5-27.
//

#ifndef NETSERVER_ATOMIC_H
#define NETSERVER_ATOMIC_H

#include <stdint.h>
#include "noncopyable.h"

namespace NetServer
{

    namespace detail
    {
        template<typename T>
        class AtomicIntegerT : noncopyable
        {
        public:
            AtomicIntegerT()
                    : value_(0)
            {
            }

            // uncomment if you need copying and assignment
            //
            // AtomicIntegerT(const AtomicIntegerT& that)
            //   : value_(that.get())
            // {}
            //
            // AtomicIntegerT& operator=(const AtomicIntegerT& that)
            // {
            //   getAndSet(that.get());
            //   return *this;
            // }

            T get()
            {
                return __sync_val_compare_and_swap(&value_, 0, 0);
            }

            T getAndAdd(T x)
            {
                return __sync_fetch_and_add(&value_, x);
            }

            T addAndGet(T x)
            {
                return getAndAdd(x) + x;
            }

            T incrementAndGet()
            {
                return addAndGet(1);
            }

            T decrementAndGet()
            {
                return addAndGet(-1);
            }

            void add(T x)
            {
                getAndAdd(x);
            }

            void increment()
            {
                incrementAndGet();
            }

            void decrement()
            {
                decrementAndGet();
            }

            T getAndSet(T newValue)
            {
                return __sync_lock_test_and_set(&value_, newValue);
            }

        private:
            volatile T value_;
        };
    }

    typedef detail::AtomicIntegerT<int32_t> AtomicInt32;
    typedef detail::AtomicIntegerT<int64_t> AtomicInt64;
}


#endif //NETSERVER_ATOMIC_H
