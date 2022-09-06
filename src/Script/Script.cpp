#include "Script.h"

#include <string>

#include "../Graphic/UI/imgui.h"
#include "../Graphic/UI/imgui-SFML.h"

#include "../Log/Log.h"

#include "../AllSub.h"

using namespace slt;

Script::Script()
{
    //memset(m_inputBuf, 0, sizeof(m_inputBuf));
}

Script::~Script()
{
    //cl_shutdown();
}

Script * _script = nullptr;

void Script::Create()
{
    if (_script == nullptr) {
        _script = new Script();
    }
}

void Script::Destory()
{
    if (_script != nullptr) {
        delete _script;
        _script = nullptr;
    }
}

void Script::init(int argc, char *argv[])
{
}

void Script::Strtrim(char *s)
{
    char* str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ') str_end--;
    *str_end = 0;
}

void Script::drawUi()
{
    if (_script->m_open) {
        ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
        ImGui::Begin("Console");

        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Close Console")) {
                _script->m_open = false;
            }
            ImGui::EndPopup();
        }

        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;

        if (ImGui::InputText("Input", _script->m_inputBuf, IM_ARRAYSIZE(_script->m_inputBuf), input_text_flags)) {
            char * s = _script->m_inputBuf;
            Strtrim(s);
            if (s[0]) {
            }
            strcpy(s, "");
            reclaim_focus = true;
        }

        ImGui::SetItemDefaultFocus();
        if (reclaim_focus) {
            ImGui::SetKeyboardFocusHere(-1);
        }

        ImGui::End();
    }
}

void Script::setDrawUi()
{
    _script->m_open = !_script->m_open;
}
