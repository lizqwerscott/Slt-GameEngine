#ifndef SCRIPT_H
#define SCRIPT_H

#include <ecl/ecl.h>
#include <vector>

#define DEFUN_NONE(name,fun) \
    {\
    void (*_run)() = fun; \
    ecl_def_c_function(c_string_to_object(name),\
            (cl_objectfn_fixed)_run,\
            0); \
    }

#define DEFUN(name,fun,args) \
    ecl_def_c_function(c_string_to_object(name),\
            (cl_objectfn_fixed)fun,\
            args)

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
    static cl_object lisp(const std::string &call);
public:
    static void signFunction(unsigned int id);
public:
    static std::string clToString(cl_object clStr);
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
