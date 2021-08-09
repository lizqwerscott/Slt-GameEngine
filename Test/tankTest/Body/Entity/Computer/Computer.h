#ifndef COMPUTER_H
#define COMPUTER_H

#include "../Entity.h"
#include <vector>

class Thruster;

class Computer : public Entity
{
public:
    Computer(std::string name, GameObject * parent, b2Vec2 nodePos, double hp = 30);
    virtual ~Computer();
public:
    virtual void onFace(Person * person) override;
public:
    void addControl(Entity * entity);
public:
    virtual void DrawUiSelf() override;
private:
    //推进器 其他
    std::vector<Thruster *> m_thrusters;
public:
    void addLog(const char * fmt, ...);
private:
    void Clear();
private:
    bool m_isAutoScroll = true;
    ImGuiTextBuffer m_buf;
    ImGuiTextFilter m_filter;
    ImVector<int> m_lineOffsets;

    char m_inputBuf[256];
    const char * m_commands;
};

#endif /* COMPUTER_H */
