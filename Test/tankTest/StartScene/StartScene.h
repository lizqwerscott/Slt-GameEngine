#ifndef STARTSCENE_H
#define STARTSCENE_H

#include "../../../src/AllSub.h"

using namespace slt;

class StartScene : public Scene
{
public:
    StartScene();
    ~StartScene();
public:
    static StartScene * create();
    virtual void init() override;
    virtual void DrawUi() override;
    virtual void UpdateSelf(sf::Time &dt) override;
private:
};

#endif
