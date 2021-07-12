#ifndef BAG_H
#define BAG_H

#include "../Item.h"
#include "../../BoxBase.h"

class Bag : public Item, BoxBase
{
public:
    Bag(std::string name, double volume, double quality, double maxVolume, double maxQuality);
    ~Bag();
};

#endif /* BAG_H */
