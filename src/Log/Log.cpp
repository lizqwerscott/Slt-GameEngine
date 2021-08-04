#include "Log.h"
#include <cstdio>
#include <ctime>

using namespace slt;

Log::Log() :
    m_nowLevel(LOG_LEVEL_NONE),
    m_nowTarget(TARGET_GUI),
    m_isDrawUi(false),
    m_isAutoScroll(true)
{
    clear();
}

Log::~Log()
{
}

Log * _log = nullptr;

void Log::Create()
{
    if (_log == nullptr) {
        _log = new Log();
    }
}

void Log::Destory()
{
    if (_log != nullptr) {
        delete _log;
        _log = nullptr;
    }
}

void Log::setLevel(LOGLEVEL level)
{
    _log->m_nowLevel = level;
}

void Log::setTarget(TARGET target)
{
    _log->m_nowTarget = target;
}

void Log::printLog(const char * fmt, ...)
{
    std::string levelStr = _log->LogLevelToStr();
    time_t now = time(0);
    tm *ltm = localtime(&now);
    switch (_log->m_nowTarget) {
    case TARGET_TERMINAL: {
        printf("%s:%s\n", levelStr.c_str(), fmt);
    }
    break;
    case TARGET_GUI: {
        ImGuiTextBuffer * Buf = &_log->m_buf;
        int old_size = Buf->size();
        va_list args;
        Buf->append("[");
        Buf->append(std::to_string(ltm->tm_hour).c_str());
        Buf->append(":");
        Buf->append(std::to_string(ltm->tm_min).c_str());
        Buf->append(":");
        Buf->append(std::to_string(ltm->tm_sec).c_str());
        Buf->append("]");
        Buf->append(levelStr.c_str());
        Buf->append(":");
        va_start(args, fmt);
        Buf->appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf->size(); old_size < new_size; old_size++) {
            if ((*Buf)[old_size] == '\n')
                _log->m_lineOffsets.push_back(old_size + 1);
        }
    }
    break;
    }
}

void Log::drawUi()
{
    if (_log->m_isDrawUi) {
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Log");

        //Options menu
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Auto-scroll", &_log->m_isAutoScroll);
            ImGui::EndPopup();
        }

        //Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        _log->m_filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scroling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            _log->clear();
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char * buf = _log->m_buf.begin();
        const char * buf_end = _log->m_buf.end();
        if (_log->m_filter.IsActive()) {
            for (int line_no = 0; line_no < _log->m_lineOffsets.Size; line_no++) {
                const char* line_start = buf + _log->m_lineOffsets[line_no];
                const char* line_end = (line_no + 1 < _log->m_lineOffsets.Size) ? (buf + _log->m_lineOffsets[line_no + 1] - 1) : buf_end;
                if (_log->m_filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }

        } else {
            ImGuiListClipper clipped;
            clipped.Begin(_log->m_lineOffsets.Size);
            while (clipped.Step()) {
                for (int line_no = clipped.DisplayStart; line_no < clipped.DisplayEnd; line_no++) {
                    const char * line_start = buf + _log->m_lineOffsets[line_no];
                    const char * line_end = (line_no + 1 < _log->m_lineOffsets.Size) ? (buf + _log->m_lineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipped.End();
        }

        ImGui::PopStyleVar();

        if (_log->m_isAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }
}

void Log::setDrawUi()
{
    _log->m_isDrawUi = !_log->m_isDrawUi;
}

std::string Log::LogLevelToStr()
{
    std::string result;
    switch (m_nowLevel) {
    case LOG_LEVEL_NONE:
        result = std::string("[NONE]");
        break;
    case LOG_LEVEL_ERROR:
        result = std::string("[ERROR]");
        break;
    case LOG_LEVEL_WARNING:
        result = std::string("[WARNING]");
        break;
    case LOG_LEVEL_DEBUG:
        result = std::string("[DEBUG]");
        break;
    case LOG_LEVEL_INFO:
        result = std::string("[INFO]");
        break;
    }
    return result;
}

void Log::clear()
{
    m_buf.clear();
    m_lineOffsets.clear();
    m_lineOffsets.push_back(0);
}
