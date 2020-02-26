
#include "IInstance.h"
#include "mt_lib/configObj.h"
#include "mt_lib/utils_local.h"
#include "mt_lib/CUtils.h"
#include "tools_mt.h"
#include "url.h"
#include "objectHandler.h"
#include <signal.h>
#include "Events/System/Net/socket/AddToConnectTCP.h"
#include "Events/System/Net/socket/ConnectFailed.h"
#include "Events/System/Net/socket/Connected.h"
#include "Events/System/Net/socket/Disconnected.h"
#include "Events/System/Net/socket/StreamRead.h"
#include "Events/System/timer/SetAlarm.h"
#include "Events/System/timer/ResetAlarm.h"
#include "Events/System/timer/TickAlarm.h"
class PeerObserver: public ObjectHandlerThreaded
{
    enum timers
    {
        TI_NEXT_PING
    };
    const real TI_NEXT_PING_val=5;
public:
    ~PeerObserver(){}
    PeerObserver(IInstance *ins): ObjectHandlerThreaded("PeerObserver",ins){}

    struct _mx: public Mutexable
    {

        std::set<msockaddr_in> peers_online;
        std::set<msockaddr_in> offline_printed;

    };
    _mx mx;
    void addPeer(const msockaddr_in& sa)
    {
        SOCKET_id sockId=iUtils->getSocketId();
        sendEvent(ServiceEnum::Socket,new socketEvent::AddToConnectTCP(sockId,sa,"",NULL,this));
    }
    void markOnline(const msockaddr_in& sa, bool isUp)
    {
        bool needPrint=false;
        {
            M_LOCK(mx);
            auto it=mx.peers_online.find(sa);
            bool isOnlineBefore= it!=mx.peers_online.end();
            if(isUp && !isOnlineBefore)
            {
                mx.peers_online.insert(sa);
                needPrint=true;

            }
            if(!isUp && (isOnlineBefore || !mx.offline_printed.count(sa)))
            {
                mx.peers_online.erase(sa);
                mx.offline_printed.insert(sa);
                needPrint=true;
            }
        }
        if(needPrint)
        {
            ///dd-MM-yyyy hh:mm:ss.fff, ip:port down
            timeb tb;
            ftime(&tb);
            struct tm tm;
            localtime_r(&tb.time,&tm);
            logErr2("%02d-%02d-%04d "
                    "%02d:%02d:%02d.%03d "
                    "%s %s",
                    tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900,
                    tm.tm_hour,tm.tm_min,tm.tm_sec,tb.millitm,
                    sa.dump().c_str(),
                    isUp?"Up":"Down");
        }
    }
    bool OH_handleObjectEvent(const REF_getter<Event::Base>& e)
    {
        if(e->id==socketEventEnum::ConnectFailed)
        {
            auto ee=dynamic_cast<socketEvent::ConnectFailed*>(e.operator->());
            sendEvent(ServiceEnum::Timer, new timerEvent::ResetAlarm(TI_NEXT_PING,outV(ee->esi->remote_name),nullptr,TI_NEXT_PING_val,this));
            markOnline(ee->esi->remote_name,false);
            return true;

        }
        if(e->id==socketEventEnum::StreamRead)
        {
            /// do nothing
            return true;
        }

        if(e->id==socketEventEnum::Disconnected)
        {
            /// do nothing
            return true;
        }
        if(e->id==socketEventEnum::Connected)
        {
            auto ee=dynamic_cast<socketEvent::Connected*>(e.operator->());
            sendEvent(ServiceEnum::Timer, new timerEvent::ResetAlarm(TI_NEXT_PING,outV(ee->esi->remote_name),nullptr,TI_NEXT_PING_val,this));
            ee->esi->close("manual close");
            markOnline(ee->esi->remote_name,true);
            return true;

        }
        if(e->id==timerEventEnum::TickAlarm)
        {

            auto ee=dynamic_cast<timerEvent::TickAlarm*>(e.operator->());
            if(ee->tid==TI_NEXT_PING)
            {
                inBuffer in(ee->data);
                msockaddr_in sa;
                in>>sa;
                SOCKET_id sockId=iUtils->getSocketId();
                sendEvent(ServiceEnum::Socket,new socketEvent::AddToConnectTCP(sockId,sa,"",NULL,this));
                return true;
            }
            return false;

        }
        return false;
    }

};

void registerSocketModule(const char* pn);
void registerTimerService(const char* pn);
void registerObjectProxyModule(const char* pn);

bool terminating=false;
void onterm(int signum)
{
    printf("signal %d\n",signum);
    if(signum==SIGINT)
    {
	terminating=true;
    }
    printf("terminating %d",terminating);
}
int main(int argc, char *argv[])
{


    signal(SIGINT,onterm);

    std::string appName=argv[0];
    iUtils=new CUtils(argc,argv,appName);
    IInstance *iInstance=iUtils->createNewInstance(argv[0]);

    ConfigObj *cnf=new ConfigObj(appName+".conf");
    iInstance->setConfig(cnf);
    registerSocketModule(nullptr);
    registerTimerService(nullptr);
    registerObjectProxyModule(nullptr);


    PeerObserver obs(iInstance);
    if(argc!=2)
    {

        printf("usage: %s <addlist>\n",argv[0]);
        return 1;
    }
    {
    
    auto proxy_list=iUtils->load_file(argv[1]);
//    auto proxy_list=iUtils->load_file("proxy_list.txt");

    auto ls=iUtils->splitString("\r\n",proxy_list);
    for(auto& l:ls)
    {
        Url u;
        u.parse(l);

        msockaddr_in sa;
        sa.init(u);
        obs.addPeer(sa);
    }
    }
    while(!terminating)
    {
//	printf("slp %d \n",terminating);
        sleep(1);
    }

    delete iUtils;



}
