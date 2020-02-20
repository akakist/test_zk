#include "jsonHandler.h"
#include "mutexInspector.h"
#ifdef __ANDROID__
#include "jni.h"
#endif
#include "Events/System/timer/TickAlarm.h"
#include "Events/DFS/Referrer/SubscribeNotifications.h"
#include "Events/System/Net/rpc/IncomingOnConnector.h"
#include "Events/System/Net/rpc/IncomingOnAcceptor.h"
#include "Events/DFS/Referrer/UpdateConfig.h"
#include "Events/DFS/Referrer/UpdateConfig.h"

JsonHandler::JsonHandler(IInstance *ins):
    TimerHelper(ins),
#ifdef __MOBILE__
    ObjectHandlerThreaded("JsonHandler",ins),
#else
    ObjectHandlerPolled("JsonHandler",ins),

#endif
    isConnected(false)
{
    iUtils->registerEvent(jsonRefEvent::JsonREQ::construct);
    iUtils->registerEvent(jsonRefEvent::JsonRSP::construct);
    iUtils->registerEvent(dfsReferrerEvent::UpdateConfigRSP::construct);
    iUtils->registerEvent(dfsReferrerEvent::UpdateConfigREQ::construct);

    sendEvent(ServiceEnum::ReferrerClient,new dfsReferrerEvent::SubscribeNotifications(this));
}

bool JsonHandler::on_NotifyReferrerUplinkIsConnected(const dfsReferrerEvent::NotifyReferrerUplinkIsConnected *)
{
    isConnected=true;
    signal_connected();
    return true;
}
bool JsonHandler::on_NotifyReferrerUplinkIsDisconnected(const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected *)
{
    isConnected=false;
    signal_disconnected();
    return true;

}
bool JsonHandler::on_ToplinkDeliverRSP(const dfsReferrerEvent::ToplinkDeliverRSP* e)
{
    XTRY;
    MUTEX_INSPECTOR;
    REF_getter<Event::Base> z=e->getEvent();
    if(!z.valid())
        return false;
    passEvent(z);
    XPASS;
    return true;
}
bool JsonHandler::on_TickAlarm(const timerEvent::TickAlarm*)
{
    return false;
}

bool JsonHandler::OH_handleObjectEvent(const REF_getter<Event::Base>& e)
{
    XTRY;
    MUTEX_INSPECTOR;
    try {
        if(handleEventInDerived(e))
            return true;
        auto& ID=e->id;
        if(jsonRefEventEnum::JsonRSP==ID)
            return on_JsonRSP((const jsonRefEvent::JsonRSP*) e.operator ->());
        if( dfsReferrerEventEnum::ToplinkDeliverRSP==ID)
            return on_ToplinkDeliverRSP((const dfsReferrerEvent::ToplinkDeliverRSP*)e.operator ->());
        if( dfsReferrerEventEnum::NotifyReferrerUplinkIsConnected==ID)
            return on_NotifyReferrerUplinkIsConnected((const dfsReferrerEvent::NotifyReferrerUplinkIsConnected*)e.operator ->());
        if( dfsReferrerEventEnum::NotifyReferrerUplinkIsDisconnected==ID)
            return on_NotifyReferrerUplinkIsDisconnected((const dfsReferrerEvent::NotifyReferrerUplinkIsDisconnected*)e.operator ->());

        if(timerEventEnum::TickAlarm==ID)
            return on_TickAlarm((const timerEvent::TickAlarm*)e.operator ->());

        if(rpcEventEnum::IncomingOnConnector==ID)
        {
            const rpcEvent::IncomingOnConnector*ze=(const rpcEvent::IncomingOnConnector*)e.operator ->();
            auto& IDC=ze->e->id;
            if(dfsReferrerEventEnum::UpdateConfigRSP==IDC)
            {
                const dfsReferrerEvent::UpdateConfigRSP*xe=(const dfsReferrerEvent::UpdateConfigRSP*)ze->e.operator ->();
                config_body=xe->body;
                logErr2("JsonHandler: if(dfsReferrerEventEnum::UpdateConfigRSP==IDC) %s",config_body.c_str());
                return true;
            }

        }

    }
    catch(std::exception &e)
    {

        logErr2("exception %s",e.what());
        push_err("Common Error",e.what(),"BROADCAST");
    }
    catch(...)
    {

        logErr2("exception ...");
        push_err("Unknown error","Unknown exception","BROADCAST");
    }
    XPASS;
    return false;
}







void JsonHandler::push_msg(const Json::Value &s,const std::string& binData, const std::string &javaCookie)
{
    (void) binData;
    M_LOCK(mx);
    Json::Value j;
    j["data"]=s;
    j["errcode"]="0";
    j["javaCookie"]=javaCookie;
#ifdef __MOBILE__
    mx.java_msgs.push_back(std::make_pair(j.toStyledString(),binData));
#else
#endif

}
void JsonHandler::push_err(const std::string & action, const std::string& s, const std::string &javaCookie)
{

    M_LOCK(mx);
    Json::Value j;
    j["data"]=s;
    j["action"]=action;
    j["errcode"]="1";
    j["javaCookie"]=javaCookie;
#ifdef __MOBILE__
    mx.java_msgs.push_back(std::make_pair(j.toStyledString(),""));
#else
#endif

}
#ifdef __MOBILE__
std::pair<std::string,std::string> JsonHandler::getMessage()
{
    M_LOCK(mx);
    if(mx.java_msgs.size())
    {
        auto msg=*mx.java_msgs.begin();
        mx.java_msgs.pop_front();
        return msg;
    }
    return std::make_pair("","");
}

#endif



/// если емейл еще не зареген, то он вставляется в базу в привязке к UID, в ответе прилетает uid/cookie,
/// если зареген, то в ответе прилетает новая uid/cookie.

