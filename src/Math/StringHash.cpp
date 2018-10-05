#include "StringHash.h"
#include "Math.h"
#include <cstdio>

using namespace slt;

const StringHash StringHash::ZERO;

#define CONVERSION_BUFFER_LENGTH 128;

StringHash::StringHash(const char * str) : value_(Calculate(str))
{
}

StringHash::StringHash(const std::string & str) : value_(Calculate(str.c_str()))
{
}

unsigned 
StringHash::Calculate(const char* str)
{
    return Math::bkdrHash(str);
}

std::string 
StringHash::ToString() const
{
    //char tempBuffer[CONVERSION_BUFFER_LENGTH];
    char tempBuffer[128];
    sprintf(tempBuffer, "%08X", value_);
    return std::string(tempBuffer);
}
