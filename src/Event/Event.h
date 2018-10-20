#ifndef EVENT_H
#define EVENT_H

#include <ext/hash_map>

namespace slt
{
typedef unsigned int EventKey;
typedef __gnu_cxx::hash_map<unsigned int, void *> EventData;
}

#endif
