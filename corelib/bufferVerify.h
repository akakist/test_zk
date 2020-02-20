#ifndef _________________BUFFERVERIFY_H
#define _________________BUFFERVERIFY_H

#include <string>
#include "ioBuffer.h"

inline bool bufferVerify(const std::string& s)
{
    inBuffer b(s);
    bool success;
    b.get_8_nothrow(success);

    if (!success)
    {
        return false;
    }
    size_t len=b.get_PN_nothrow(success);

    if (!success) return false;

    if(b.remains()<len)
    {
        return false;
    }
    return true;

}

#endif // BUFFERVERIFY_H
