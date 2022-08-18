#ifndef NETCONTROL_H
#define NETCONTROL_H

#include "../Net.h"

class Entity;

enum DeviceSignalType {
    Bool,
    String,
    Number
};

struct DeviceSignalData
{
    DeviceSignalType type;
    Entity * sender;
};

struct DeviceSignalDataBool : public DeviceSignalData
{
    bool data;
    DeviceSignalDataBool() { this->type = DeviceSignalType::Bool; }
};

struct DeviceSignalDataString : public DeviceSignalData
{
    std::string data;
    DeviceSignalDataString() { this->type = DeviceSignalType::String; }
};

struct DeviceSignalDataNumber : public DeviceSignalData
{
    double data;
    DeviceSignalDataNumber() { this->type = DeviceSignalType::Number; }
};

typedef std::function<void (DeviceSignalData &)> SignalReciveFunction;


class NetControl : public Net
{
public:
    NetControl(std::string typeName);
    virtual ~NetControl();
public:
    std::string m_controlTypeName;
};

#endif
