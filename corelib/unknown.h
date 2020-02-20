#ifndef ________UNKNWN___H
#define ________UNKNWN___H
#include "CLASS_id.h"
#include <map>
#include "mutexable.h"
#include "CONTAINER.h"
#include "commonError.h"
#include "SERVICE_id.h"
#include "IConfigObj.h"

/// base class for interfaces with casting ability

class UnknownBase
{
private:
    Mutex __m_lock$;
    std::map<CLASS_id,void*> __container$;
protected:
public:
    const char* app_name;
    const std::string classname;
    void addClass(const CLASS_id& c, void* instance);
    void* cast(const CLASS_id& c) const;
    virtual ~UnknownBase();
    virtual void deinit()=0;
    UnknownBase(const std::string& nm);

};

#endif
