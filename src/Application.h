#ifndef APPLICATION_H
#define APPLICATION_H

namespace slt
{
class Engine;
class Application
{
public:
    Application(int argc, char * argv[]);
    virtual ~Application();
public:
    virtual void init() = 0;
    int run();
    virtual void end() = 0;
protected:
    Engine * engine;
};
}
#endif
