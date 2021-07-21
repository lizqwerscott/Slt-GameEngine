#ifndef BOXBASE_H
#define BOXBASE_H

#include <vector>
#include <map>

#include "ContainerBase.h"

class BoxBase : public ContainerBase
{
public:
    BoxBase(double volume, double quality);
    virtual ~BoxBase();
public:
    void DrawBoxUi(std::string name, int column = 3);
public:
    virtual bool addItem(Item * item);
    std::vector<Item *> getItem(std::string name, int number);
    virtual Item * getItem(); //for only one
    virtual bool transferItem(ContainerBase * target, std::string name, int number);
public:
    void releaseEmptyItems();
protected:
    std::map<std::string, std::vector<Item *>> m_container;
};

#endif /* BOXBASE_H */
