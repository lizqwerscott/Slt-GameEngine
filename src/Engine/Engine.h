#ifndef ENGINE_H
#define ENGINE_H

#include <memory>
#include <string>
#include <SFML/System.hpp>
#include <box2d/box2d.h>
#include "../MemoryManager/Ref.h"

namespace slt
{
class Graphic;
class view;

class Engine : public Ref
{
public:
    Engine();
    ~Engine();
public:
    int Run(sf::Time &dt);
public:
    bool isClose();
private:

};
}
#endif
