#ifndef LOG_H
#define LOG_H

#include <string>
#include "../Graphic/UI/imgui.h"
#include "../Graphic/UI/imgui-SFML.h"

class b2Vec2;

namespace slt
{
enum LOGLEVEL
{
    LOG_LEVEL_NONE,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO
};
enum TARGET
{
    TARGET_TERMINAL,
    TARGET_GUI
};

class Log
{
public:
    static void setLevel(LOGLEVEL level);
    static void setTarget(TARGET target);
    static void printLog(const char * fmt, ...);
    static void printVec2(const char * fmt, b2Vec2 pos);
public:
    static void drawUi();
    static void setDrawUi();
public:
    static void Create();
    static void Destory();
private:
    std::string LogLevelToStr();
private:
    void clear();
private:
    LOGLEVEL m_nowLevel;
    TARGET m_nowTarget;
private:
    bool m_isDrawUi;
    ImGuiTextBuffer m_buf;
    ImGuiTextFilter m_filter;
    ImVector<int> m_lineOffsets;
    bool m_isAutoScroll;
private:
    Log();
    ~Log();
};
}

#endif /* LOG_H */
