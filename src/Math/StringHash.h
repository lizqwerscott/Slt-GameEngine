#ifndef STRINGHASH_H
#define STRINGHASH_H

#include <string>

namespace slt
{
class StringHash
{
public:
    /// Construct with zero value.
    StringHash() : value_(0) {}

    /// Copy-construct from another hash.
    StringHash(const StringHash & rhs) :value_(rhs.value_) {}

    /// Construct with an initial value.
    explicit StringHash(unsigned value) : value_(value) {}

    /// Construct from a C string case-insensitively.
    StringHash(const char* str);
    /// Construct from a string case-insensitively.
    StringHash(const std::string & str);

    /// Assign from another hash.
    StringHash & operator =(const StringHash & rhs)
    {
        value_ = rhs.value_;
        return *this;
    }

    /// Add a hash.
    StringHash operator +(const StringHash & rhs) const
    {
        StringHash ret;
        ret.value_ = value_ + rhs.value_;
        return ret;
    }

    /// Add-assign a hash.
    StringHash & operator +=(const StringHash & rhs)
    {
        value_ += rhs.value_;
        return *this;
    }

    /// Test for equality with another hash.
    bool operator ==(const StringHash& rhs) const { return value_ == rhs.value_; }

    /// Test for inequality with another hash.
    bool operator !=(const StringHash& rhs) const { return value_ != rhs.value_; }

    /// Test if less than another hash.
    bool operator <(const StringHash& rhs) const { return value_ < rhs.value_; }

    /// Test if greater than another hash.
    bool operator >(const StringHash& rhs) const { return value_ > rhs.value_; }

    /// Return true if nonzero hash value.
    operator bool() const { return value_ != 0; }

    /// Return hash value.
    unsigned Value() const { return value_; }

    /// Return as string.
    std::string ToString() const;

    /// Return hash value for HashSet & HashMap.
    unsigned ToHash() const { return value_; }

    /// Calculate hash value case-insensitively from a C string.
    static unsigned Calculate(const char * str);

    /// Zero hash.
    static const StringHash ZERO;

private:
    /// Hash value.
    unsigned value_;
	
};
}

#endif
