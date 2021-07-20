#ifndef BOXBASE_H
#define BOXBASE_H

#include <string>
#include <vector>
#include <map>

class Item;

class BoxBase
{
public:
    BoxBase(double volume, double quality);
    virtual ~BoxBase();
public:
    void DrawBoxUi(std::string name, int column = 3);
public:
    bool addItem(Item * item);
    std::vector<Item *> getItem(std::string name, int number);
    Item * getItem(); //for only one
    bool transferItem(std::string name, BoxBase * target, int number);
public:
    void releaseEmptyItems();
public:
    double getNowVolume();
    double getNowQuality();
    double getMaxVolume();
    double getMaxQuality();
    void setMaxVolume(double volume);
    void setMaxQuality(double quality);
private:
    double m_maxVolume;
    double m_maxQuality;
    double m_nowVolume = 0;
    double m_nowQuality = 0;
protected:
    std::map<std::string, std::vector<Item *>> m_container;
};

#endif /* BOXBASE_H */
