#include "Computer.h"
#include "../Thruster/Thruster.h"

Computer::Computer(std::string name, GameObject * parent, b2Vec2 nodePos, double hp) :
    Entity(name, "Computer", parent, nodePos, hp)
{
    this->m_isDrawUi = false;
    m_isControl = true;
    m_isConnect = true;

    sf::Texture * computer = ResourceManager::GetTexture("computer");
    computer->setSmooth(true);

    m_mainShape = CreateRectangleShape(b2Vec2(1, 1), computer);

    Clear();
    memset(m_inputBuf, 0, sizeof(m_inputBuf));
}

Computer::~Computer()
{
}

void Computer::onFace(Person *person)
{
    Log::setLevel(LOG_LEVEL_INFO);
    Log::printLog("[Computer]report computer\n");
    this->m_isDrawUi = !this->m_isDrawUi;
}

void Computer::addControl(Entity * entity)
{
    if (entity->m_typeName == std::string("Thruster")) {
        Thruster * thruster = static_cast<Thruster *>(entity);
        Log::setLevel(LOG_LEVEL_INFO);
        Log::printLog("add thruster\n");
        m_thrusters.push_back(thruster);
    }
}

void Computer::DrawUiSelf()
{
    if (m_isDrawUi) {
        ImGui::SetNextWindowSize(ImVec2(500, 500), ImGuiCond_FirstUseEver);
        ImGui::Begin("Computer");
        //Options menu
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Auto-scroll", &m_isAutoScroll);
            ImGui::EndPopup();
        }
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::Separator();
        if (ImGui::Button("Push")) {
            for (auto thruster : m_thrusters) {
                thruster->increaseThrust(10);
                thruster->push();
                Log::setLevel(LOG_LEVEL_INFO);
                Log::printLog("Push\n");
            }
        }
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;

        if (ImGui::InputText("Input", m_inputBuf, IM_ARRAYSIZE(m_inputBuf), input_text_flags)) {
            char * s = m_inputBuf;
            Script::Strtrim(s);
            if (s[0]) {
                Script::lisp(s);
            }
            strcpy(s, "");
            reclaim_focus = true;
        }

        ImGui::SetItemDefaultFocus();
        if (reclaim_focus) {
            ImGui::SetKeyboardFocusHere(-1);
        }

        //Main window
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");
        ImGui::SameLine();
        bool clear = ImGui::Button("Clear");
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        m_filter.Draw("Filter", -100.0f);

        ImGui::Separator();
        ImGui::BeginChild("scroling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        if (clear)
            Clear();
        if (copy)
            ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char * buf = m_buf.begin();
        const char * buf_end = m_buf.end();
        if (m_filter.IsActive()) {
            for (int line_no = 0; line_no < m_lineOffsets.Size; line_no++) {
                const char* line_start = buf + m_lineOffsets[line_no];
                const char* line_end = (line_no + 1 < m_lineOffsets.Size) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
                if (m_filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }

        } else {
            ImGuiListClipper clipped;
            clipped.Begin(m_lineOffsets.Size);
            while (clipped.Step()) {
                for (int line_no = clipped.DisplayStart; line_no < clipped.DisplayEnd; line_no++) {
                    const char * line_start = buf + m_lineOffsets[line_no];
                    const char * line_end = (line_no + 1 < m_lineOffsets.Size) ? (buf + m_lineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipped.End();
        }

        ImGui::PopStyleVar();

        if (m_isAutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }

        ImGui::EndChild();
        ImGui::End();
    }
}

void Computer::addLog(const char *fmt, ...)
{
    int old_size = m_buf.size();
    va_list args;
    va_start(args, fmt);
    m_buf.appendfv(fmt, args);
    va_end(args);
    for (int new_size = m_buf.size(); old_size < new_size; old_size++) {
        if ((m_buf)[old_size] == '\n')
            m_lineOffsets.push_back(old_size + 1);
    }
}

void Computer::Clear()
{
    m_buf.clear();
    m_lineOffsets.clear();
    m_lineOffsets.push_back(0);
}
