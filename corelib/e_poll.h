#ifndef ______E_POLL_H
#define ______E_POLL_H
#include "pconfig.h"
#if defined(WIN32)
#define HAVE_SELECT
#elif defined (__MACH__) || defined(__IOS__) || defined(__FreeBSD__)
#define HAVE_KQUEUE
#else
#define HAVE_EPOLL
#endif

#ifdef HAVE_EPOLL
struct e_poll
{
    e_poll()
        :
        m_epollFd(-1),size(10),timeout_millisec(10)
    {
    }
    int m_epollFd;

    // conf vars
    int size;
    int timeout_millisec;
};
#endif


#endif // E_POLL_H
