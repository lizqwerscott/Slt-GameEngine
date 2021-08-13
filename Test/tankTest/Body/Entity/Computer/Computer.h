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
    virtual void UpdateSelf(sf::Time &dt) override;
    virtual void DrawUiSelf() override;
private:
    //推进器 其他
    std::vector<Thruster *> m_thrusters;
    void move(int direction, float force);
public:
    void addLog(const char * fmt, ...);
private:
    void Clear();
public:
    static Computer * findSelf(int id);
    static cl_object getThrusters();
    static void push(int computerId, int id, int force);

    //static void move(int direction, float force);
    static void rotate(float angle);
private:
    bool m_isAutoScroll = true;
    ImGuiTextBuffer m_buf;
    ImGuiTextFilter m_filter;
    ImVector<int> m_lineOffsets;

    char m_inputBuf[256];
    const char * m_commands;
};

#endif /* COMPUTER_H */
