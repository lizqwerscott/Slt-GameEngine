#ifndef NETCONTROL_H
#define NETCONTROL_H

#include "../Net.h"

class NetControl : public Net
{
public:
    NetControl(std::string typeName);
    virtual ~NetControl();
public:
    std::string m_controlTypeName;
};

#endif
