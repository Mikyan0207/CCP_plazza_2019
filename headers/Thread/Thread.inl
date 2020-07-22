#ifndef THREAD_INL_
#define THREAD_INL_

#include <Thread/Thread.hpp>

namespace Plazza
{
    template<typename T, typename ... Targs>
    void Thread::Run(T&& function, Targs&& ... args)
    {
        this->_thread = std::thread(function, std::forward<Targs>(args)...);
    }
}

#endif