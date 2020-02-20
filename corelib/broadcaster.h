#ifndef _______________BROADCASTER____H
#define _______________BROADCASTER____H
#include "IInstance.h"

/**
* Базовый класс для сервисов, дающим им возможность посылки сообщений
*/
class Broadcaster
{
public:
    Broadcaster(IInstance* _if):__BRD$ifa(_if) {}
    /// послать евент в сервис
    void sendEvent(const SERVICE_id& svs, const REF_getter<Event::Base>&e);
    /// послать евент в удаленный сервис по RPC
    void sendEvent(const msockaddr_in& addr, const SERVICE_id& svs, const REF_getter<Event::Base>&e);
    void sendEvent(const std::set<msockaddr_in>& addr, const SERVICE_id& svs, const REF_getter<Event::Base>&e);
    /// послать евент в удаленный сервис по RPC
    void sendEvent(const std::string& addr, const SERVICE_id& svs, const REF_getter<Event::Base>&e);
    /// послать евент обратно по маршруту
    void passEvent(const REF_getter<Event::Base>&e);
    IInstance* getIInstance()
    {
        return __BRD$ifa;
    }

private:
    IInstance* __BRD$ifa;

};
#endif
