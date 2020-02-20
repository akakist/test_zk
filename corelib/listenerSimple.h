#ifndef ____________LISTENER_____H
#define ____________LISTENER_____H
#include "listenerBase.h"


/// simple listener w/o buffering and threads

class ListenerSimple:public ListenerBase
{
public:
    ListenerSimple(UnknownBase *i, const std::string& name,IConfigObj*, const SERVICE_id& sid);

    /// call method in inherited class to process event
    virtual bool handleEvent(const REF_getter<Event::Base>& e)=0;
    virtual ~ListenerSimple();

    /// implementation of base virtuals
    void listenToEvent(const REF_getter<Event::Base>& e);
    void listenToEvent(const std::deque<REF_getter<Event::Base> >&);

};
#endif

