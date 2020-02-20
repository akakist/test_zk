#ifndef ____________________SYSEVENT____H
#define ____________________SYSEVENT____H

#include "REF.h"
#include "ioBuffer.h"
#include "event.h"


namespace systemEventEnum
{

    const EVENT_id startService("startService");
}
namespace systemEvent
{
    /**
     * \brief
     */
    class startService:public Event::NoPacked
    {
    public:
        static Base* construct(const route_t &)
        {
            return NULL;
        }
        startService():NoPacked( systemEventEnum::startService) {}
        void jdump(Json::Value &) const
        {

        }
    };

}
#endif
