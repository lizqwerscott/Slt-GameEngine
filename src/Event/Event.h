#ifndef EVENT_H
#define EVENT_H

#include <map>
#include <string>

namespace slt
{
typedef unsigned int EventKey;
typedef std::map<unsigned int, void *> EventData;
}

#endif
