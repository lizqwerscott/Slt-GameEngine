#ifndef EVENT_H
#define EVENT_H

#include <map>
#include "../Math/StringHash.h"

namespace slt
{
typedef StringHash EventKey;
typedef std::map<StringHash, void *> EventData;
}

#endif
