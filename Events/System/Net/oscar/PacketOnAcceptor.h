#ifndef ______OSCAR_EVENT___H9
#define ______OSCAR_EVENT___H9
#include "___oscarEvent.h"
namespace oscarEvent
{

/// приход буфера на слушателе
    class PacketOnAcceptor: public Event::NoPacked
    {
    public:
        static Base* construct(const route_t &)
        {
            return NULL;
        }
        PacketOnAcceptor(const REF_getter<epoll_socket_info> & _esi, const REF_getter<refbuffer> &_buf, const route_t &r)
            :NoPacked(oscarEventEnum::PacketOnAcceptor,r),
             esi(_esi),buf(_buf) {}
        /// сокет
        const REF_getter<epoll_socket_info>  esi;
        /// buffer
        const REF_getter<refbuffer> buf;
        void jdump(Json::Value &) const
        {
        }
    };
}
#endif
