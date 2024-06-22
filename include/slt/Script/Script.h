#ifndef SCRIPT_H
#define SCRIPT_H

#include <vector>

namespace slt
{
class Script
{
private:
    Script();
    ~Script();
public:
    static void Create();
    static void Destory();
    static void init(int argc, char *argv[]);
public:
    static void Strtrim(char* s);
public:
    static void drawUi();
public:
    static void setDrawUi();
private:
    char m_inputBuf[256];
    const char * m_commands;
    bool m_open = false;
    bool m_autoScroll = true;
};
};

#endif /* SCRIPT_H */
