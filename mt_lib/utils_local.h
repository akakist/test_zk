#ifndef UTILS_LOCAL_H
#define UTILS_LOCAL_H
#include "mutexable.h"
#include "SERVICE_id.h"
#include "ifaces.h"
#include "unknown.h"
#include "ITests.h"
#include "IUtils.h"
#include "mutexInspector.h"
#include "colorOutput.h"
class IInstance;

struct Utils_local
{
    struct _ifaces: public Mutexable
    {
        std::map<SERVICE_id,Ifaces::Base*> container;
        void clear()
        {

            MUTEX_INSPECTOR;

            std::map<SERVICE_id,Ifaces::Base*> ifs;

            {
                M_LOCK(this);
                ifs=container;
                container.clear();

            }
            for(auto & z: ifs)
            {
                std::string name=z.first.dump().c_str();
                printf(BLUE("deleting %s"),z.first.dump().c_str());
                delete z.second;
                printf(BLUE("deleted %s"),name.c_str());

            }

        }
    };
    _ifaces ifaces;
    struct _itests
    {
    private:
        Mutex mx;
        std::map<SERVICE_id,itest_static_constructor> container;
    public:
        std::map<SERVICE_id,itest_static_constructor> getContainer()
        {
            M_LOCK(mx);
            return container;
        }
        void insert(const SERVICE_id& id, const itest_static_constructor &c)
        {
            M_LOCK(mx);
            container.insert(std::make_pair(id,c));
        }
        void clear()
        {
            MUTEX_INSPECTOR;


            M_LOCK(mx);
            container.clear();

        }
    };
    _itests itests;
    struct _plugin_info: public Mutexable
    {
        std::map<SERVICE_id,std::string> services;
        std::map<SERVICE_id,std::string> ifaces;
        std::map<SERVICE_id,std::string> itests;
        std::map<EVENT_id, std::set<std::string> > events;
        void clear()
        {

            MUTEX_INSPECTOR;

            M_LOCK(this);
            services.clear();
            ifaces.clear();
            itests.clear();
            events.clear();
        }

    };
    _plugin_info pluginInfo;
    struct __service_names: public Mutexable
    {
        std::map<std::string, SERVICE_id> name2id;
        std::map<SERVICE_id,std::string> id2name;
        void clear()
        {
            MUTEX_INSPECTOR;


            M_LOCK(this);
            name2id.clear();
            id2name.clear();
        }
    };
    struct __service_constructors: public Mutexable
    {
        std::map<SERVICE_id,unknown_static_constructor> container;
        void clear()
        {

            MUTEX_INSPECTOR;
            M_LOCK(this);

            container.clear();
        }
    };
    struct __event_constructors: public Mutexable
    {
        std::map<EVENT_id,event_static_constructor> container;
        void clear()
        {

            MUTEX_INSPECTOR;
            M_LOCK(this);

            container.clear();
        }

    };
    __service_names service_names;
    __service_constructors service_constructors;
    __event_constructors event_constructors;

    void clear()
    {

        MUTEX_INSPECTOR;

        service_constructors.clear();
        event_constructors.clear();


        ifaces.clear();


        itests.clear();


        pluginInfo.clear();


        service_names.clear();






    }

};
#endif // UTILS_LOCAL_H
