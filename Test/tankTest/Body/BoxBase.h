#ifndef BOXBASE_H
#define BOXBASE_H

#include <string>
#include <vector>

class Item;

class BoxBase
{
public:
    BoxBase(double volume, double quality);
    ~BoxBase();
public:
    bool addItem(Item * item);
    Item * getItem(std::string name);
    Item * getItem(int index);
    bool transferItem(std::string name, BoxBase * target);
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
    
    std::vector<Item *> m_container;
};

#endif /* BOXBASE_H */
