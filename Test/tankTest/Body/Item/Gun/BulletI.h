#ifndef BULLETI_H
#define BULLETI_H

#include "../Item.h"

class BulletI : public Item
{
public:
    BulletI(std::string name, double volume, double quality);
    ~BulletI() {}
};

#endif /* BULLETI_H */

